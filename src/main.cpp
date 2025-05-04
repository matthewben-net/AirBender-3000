#include <Arduino.h>
#include <esp32_smartdisplay.h>
#include <ui/ui.h>
#include "globals.h"
#include <ui/actions.h>
#include <Wire.h>
#include <ui/vars.h>
#include "mpu.h"  // Include your new MPU logic

#define ARDUINO_ADDRESS 8  
TwoWire myI2C = TwoWire(1);  // Use I2C bus 1

// Force chart series declarations
lv_chart_series_t *lift_series_sbs;
lv_chart_series_t *lift_series_full;
lv_chart_series_t *drag_series_sbs;
lv_chart_series_t *drag_series_full;

void setup() {
  //ESP32 smart screen initialization
  smartdisplay_init();
  ui_init();
  smartdisplay_lcd_set_backlight(brightness);
  auto display = lv_display_get_default();
  lv_display_set_rotation(display, LV_DISPLAY_ROTATION_90);
  // Set first screen brightness
  update_brightness_display();
  
  // Initialize a separate I2C bus on 21/22
  myI2C.begin(21, 22, 100000);
  mpu6050_init();
  
  Serial.begin(115200); // Start serial output for load cell debugging

  // initialize the various lvgl charts for the force datas
  // Lifts
  lift_series_sbs  = lv_chart_add_series(objects.more_details_sbs_lift_chart, lv_palette_main(LV_PALETTE_GREEN), LV_CHART_AXIS_PRIMARY_Y);
  lift_series_full = lv_chart_add_series(objects.more_details_full_lift_chart, lv_palette_main(LV_PALETTE_GREEN), LV_CHART_AXIS_PRIMARY_Y);
  lv_chart_set_range(objects.more_details_sbs_lift_chart, LV_CHART_AXIS_PRIMARY_Y, -10, 10);
  lv_chart_set_range(objects.more_details_full_lift_chart, LV_CHART_AXIS_PRIMARY_Y, -10, 10);
  // Drags
  drag_series_sbs  = lv_chart_add_series(objects.more_details_sbs_drag_chart, lv_palette_main(LV_PALETTE_BLUE), LV_CHART_AXIS_PRIMARY_Y);
  drag_series_full = lv_chart_add_series(objects.more_details_full_drag_chart, lv_palette_main(LV_PALETTE_BLUE), LV_CHART_AXIS_PRIMARY_Y);
}

extern "C" void sendStepperCommand(uint8_t command) {
  myI2C.beginTransmission(ARDUINO_ADDRESS);
  myI2C.write(command);
  myI2C.endTransmission();
}

auto lv_last_tick = millis();

void read_force_data() {
  const uint8_t bytesToRead = 8;  // 2 floats = 8 bytes
  uint8_t buffer[bytesToRead];

  myI2C.requestFrom(ARDUINO_ADDRESS, bytesToRead);
  size_t index = 0;
  while (myI2C.available() && index < bytesToRead) {
    buffer[index++] = myI2C.read();
  }

  // Only proceed if we received all 8 bytes
  if (index == bytesToRead) {
    float drag = 0.0f;
    float lift = 0.0f;

    memcpy(&drag, buffer, 4);
    memcpy(&lift, buffer + 4, 4);

    // Update UI variables
    set_var_float_drag_force(drag);
    set_var_float_lift_force(lift);

    char drag_str[32];
    char lift_str[32];
    snprintf(drag_str, sizeof(drag_str), "%.2f N", drag);
    snprintf(lift_str, sizeof(lift_str), "%.2f N", lift);

    set_var_string_drag_force_label(drag_str);
    set_var_string_lift_force_label(lift_str);
    
    // Serial debugging to print force values to console
    Serial.print("Parsed Drag: ");
    Serial.print(drag);
    Serial.print(" N, Lift: ");
    Serial.print(lift);
    Serial.println(" N");

    // Update the lvgl charts for forces
    lv_chart_set_next_value(objects.more_details_sbs_lift_chart, lift_series_sbs, lift);
    lv_chart_set_next_value(objects.more_details_full_lift_chart, lift_series_full, lift);
    
    lv_chart_set_next_value(objects.more_details_sbs_drag_chart, drag_series_sbs, drag);
    lv_chart_set_next_value(objects.more_details_full_drag_chart, drag_series_full, drag);
  }
}

void loop() {
  auto const now = millis();

  // Non-blocking timer for MPU6050
  static unsigned long lastMPUread = 0;
  const unsigned long mpuInterval = 400;  // in milliseconds
  if (now - lastMPUread >= mpuInterval) {
    read_mpu6050_angle();
    lastMPUread = now;
  }
  
  // Non-blocking timer for force data
  static unsigned long lastForceRead = 0;
  const unsigned long forceInterval = 500; // Adjust as needed
  if (now - lastForceRead >= forceInterval) {
    read_force_data();
  lastForceRead = now;
  }

  // Update the ticker
  lv_tick_inc(now - lv_last_tick);
  lv_last_tick = now;
  // Update the UI
  lv_timer_handler();
  ui_tick();
}