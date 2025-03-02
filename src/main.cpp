#include <Arduino.h>
#include <esp32_smartdisplay.h>
#include <ui/ui.h>
#include "globals.h"
#include <ui/actions.h>

void setup() {
    smartdisplay_init();
    ui_init();
    smartdisplay_lcd_set_backlight(brightness);
    auto display = lv_display_get_default();
    lv_display_set_rotation(display, LV_DISPLAY_ROTATION_90);
      // Update the display elements
    update_brightness_display();
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