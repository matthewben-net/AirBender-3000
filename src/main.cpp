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

// Chart series declarations
lv_chart_series_t *lift_series_sbs;
lv_chart_series_t *lift_series_full;
lv_chart_series_t *drag_series_sbs;
lv_chart_series_t *drag_series_full;
lv_chart_series_t *airspeed_series;

// Splash screen declarations
unsigned long splash_start_time = 0;
int splash_stage = 0;
bool splash_done = false;


void setup() {
  smartdisplay_init();
  ui_init();

  // Splash logic starts with the blank screen
  splash_start_time = millis();
  lv_scr_load(objects.starting_splash_blank);  // Start with initial blank screen
  smartdisplay_lcd_set_backlight(0.5);
  update_brightness_display();

  auto display = lv_display_get_default();
  lv_display_set_rotation(display, LV_DISPLAY_ROTATION_90);
  
  // Initialize a separate I2C bus on 21/22
  myI2C.begin(21, 22, 100000);
  mpu6050_init();
  
  Serial.begin(115200); // Start serial output for load cell debugging

  // initialize the various lvgl charts for the force and airspeed datas
  // Lifts
  lift_series_sbs = lv_chart_add_series(objects.more_details_sbs_lift_chart, lv_palette_main(LV_PALETTE_GREEN), LV_CHART_AXIS_PRIMARY_Y);
  lift_series_full = lv_chart_add_series(objects.more_details_full_lift_chart, lv_palette_main(LV_PALETTE_GREEN), LV_CHART_AXIS_PRIMARY_Y);
  lv_chart_set_range(objects.more_details_sbs_lift_chart, LV_CHART_AXIS_PRIMARY_Y, -10, 10);
  lv_chart_set_range(objects.more_details_full_lift_chart, LV_CHART_AXIS_PRIMARY_Y, -10, 10);
  // Drags
  drag_series_sbs  = lv_chart_add_series(objects.more_details_sbs_drag_chart, lv_palette_main(LV_PALETTE_BLUE), LV_CHART_AXIS_PRIMARY_Y);
  drag_series_full = lv_chart_add_series(objects.more_details_full_drag_chart, lv_palette_main(LV_PALETTE_BLUE), LV_CHART_AXIS_PRIMARY_Y);
  // SPEEDS
  airspeed_series= lv_chart_add_series(objects.eez_airspeed_chart, lv_palette_main(LV_PALETTE_RED), LV_CHART_AXIS_PRIMARY_Y);
  lv_chart_set_range(objects.eez_airspeed_chart, LV_CHART_AXIS_PRIMARY_Y, 0, 60);
}

extern "C" void sendStepperCommand(uint8_t command) {
  myI2C.beginTransmission(ARDUINO_ADDRESS);
  myI2C.write(command);
  myI2C.endTransmission();
}

auto lv_last_tick = millis();

void read_arduino_data() {
  const uint8_t bytesToRead = 12;  // 3 floats = 12 bytes
  uint8_t buffer[bytesToRead];

  myI2C.requestFrom(ARDUINO_ADDRESS, bytesToRead);
  size_t index = 0;
  while (myI2C.available() && index < bytesToRead) {
    buffer[index++] = myI2C.read();
  }

  if (index == bytesToRead) {
    float drag = 0.0f;
    float lift = 0.0f;
    float airspeed = 0.0f;

    memcpy(&drag, buffer, 4);
    memcpy(&lift, buffer + 4, 4);
    memcpy(&airspeed, buffer + 8, 4);

    // Update UI variables
    set_var_float_drag_force(drag);
    set_var_float_lift_force(lift);

    // Create and set string labels
    char drag_str[32];
    char lift_str[32];
    char airspeed_str[32];
    snprintf(drag_str, sizeof(drag_str), "%.2f N", drag);
    snprintf(lift_str, sizeof(lift_str), "%.2f N", lift);
    snprintf(airspeed_str, sizeof(airspeed_str), "%.2f m/s", airspeed);

    set_var_string_drag_force_label(drag_str);
    set_var_string_lift_force_label(lift_str);
    set_var_string_airspeed_label(airspeed_str);
    
    // Serial debug
    Serial.print("Drag: ");
    Serial.print(drag);
    Serial.print(" N, Lift: ");
    Serial.print(lift);
    Serial.print(" N, Airspeed: ");
    Serial.print(airspeed);
    Serial.println(" m/s");

    // Update charts based on toggle
    static int chart_update_counter = 0;
    chart_update_counter++;

    bool fast_mode = get_var_bool_graph_speed();

    // If fast mode OR (slow mode AND only every 2nd update)
    if (fast_mode || chart_update_counter % 2 == 0) {
      // lifts
      lv_chart_set_next_value(objects.more_details_sbs_lift_chart, lift_series_sbs, lift);
      lv_chart_set_next_value(objects.more_details_full_lift_chart, lift_series_full, lift);
      // drags
      lv_chart_set_next_value(objects.more_details_sbs_drag_chart, drag_series_sbs, drag);
      lv_chart_set_next_value(objects.more_details_full_drag_chart, drag_series_full, drag);
      // airspeed
      lv_chart_set_next_value(objects.eez_airspeed_chart, airspeed_series, airspeed);
    }
  }
}

void loop() {
  auto const now = millis();

  unsigned long elapsed = now - splash_start_time;

  if (!splash_done) {
    if (splash_stage == 0 && elapsed > 1000) {
      // Fade to splash screen after 1s on starting blank
      lv_scr_load_anim(objects.splash_screen, LV_SCR_LOAD_ANIM_FADE_IN, 1000, 0, false);
      splash_start_time = now;
      splash_stage = 1;
    } 
    else if (splash_stage == 1 && elapsed > 4500) {
      // Fade to ending blank screen after 3s on splash screen
      lv_scr_load_anim(objects.ending_splash_blank, LV_SCR_LOAD_ANIM_FADE_IN, 1500, 0, false);
      splash_start_time = now;
      splash_stage = 2;
    } 
    else if (splash_stage == 2 && elapsed > 1500) {
      // Fade to main screen after 1s on ending blank screen
      lv_scr_load_anim(objects.main, LV_SCR_LOAD_ANIM_FADE_IN, 1000, 0, false);
      splash_done = true;
    }
  }

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
    read_arduino_data();
  lastForceRead = now;
  }

  // Update the ticker
  lv_tick_inc(now - lv_last_tick);
  lv_last_tick = now;
  // Update the UI
  lv_timer_handler();
  ui_tick();
}