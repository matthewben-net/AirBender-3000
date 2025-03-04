#include <Arduino.h>
#include <esp32_smartdisplay.h>
#include <ui/ui.h>
#include "globals.h"
#include <ui/actions.h>
#include <Wire.h>

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
  
}

extern "C" void sendStepperCommand(uint8_t command) {
  myI2C.beginTransmission(ARDUINO_ADDRESS);
  myI2C.write(command);
  myI2C.endTransmission();
}

auto lv_last_tick = millis();

void loop() {
  auto const now = millis();
  // Update the ticker
  lv_tick_inc(now - lv_last_tick);
  lv_last_tick = now;
  // Update the UI
  lv_timer_handler();
  ui_tick();
}