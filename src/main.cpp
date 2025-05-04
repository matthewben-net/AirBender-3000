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


void setup() {
  smartdisplay_init();
  ui_init();
  smartdisplay_lcd_set_backlight(brightness);
  auto display = lv_display_get_default();
  lv_display_set_rotation(display, LV_DISPLAY_ROTATION_90);
  // Update the display elements
  update_brightness_display();
  
  // Initialize a separate I2C bus on 21/22
  myI2C.begin(21, 22, 100000);
  mpu6050_init();
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