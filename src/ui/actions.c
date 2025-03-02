#include <lvgl.h>
#include <esp32_smartdisplay.h>
#include <stdio.h>  // For snprintf
#include "actions.h"
#include "vars.h"
#include "screens.h"
#include "ui.h"
#include "globals.h"

float brightness = 0.3;

void update_brightness_display() {
    // Update brightness label
    static char brightness_str[10];  
    snprintf(brightness_str, sizeof(brightness_str), "%d%%", (int)(brightness * 100));  
    set_var_eezvar_screen_brightness(brightness_str);
    // Update bar graph variable
    set_var_int_screen_brightness((int)(brightness * 100));  
}

void action_inc_brightness(lv_event_t * e) {
    if (brightness < 1.0) {
        brightness += 0.1;
        if (brightness > 1.0) brightness = 1.0;  // Ensure max is 100%
        smartdisplay_lcd_set_backlight(brightness);  // Apply brightness
        update_brightness_display();  // Update UI elements
    }
}

void action_dec_brightness(lv_event_t * e) {
    if (brightness > 0.1) {
        brightness -= 0.1;
        if (brightness < 0.0) brightness = 0.1;  // Ensure min is 0%
        smartdisplay_lcd_set_backlight(brightness);  // Apply brightness
        update_brightness_display();  // Update UI elements
    }
}
