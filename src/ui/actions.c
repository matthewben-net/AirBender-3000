#include <lvgl.h>
#include <esp32_smartdisplay.h>
#include <stdio.h>  // For snprintf
#include "actions.h"
#include "vars.h"
#include "screens.h"
#include "ui.h"
#include "globals.h"

extern void sendStepperCommand(uint8_t command);  // Declare the C++ function

float brightness = 0.5;

void update_brightness_display() {
    // Update brightness label
    static char brightness_str[10];  
    snprintf(brightness_str, sizeof(brightness_str), "%d%%", (int)(brightness * 100));  
    set_var_eezvar_screen_brightness(brightness_str);
    // Update bar graph variable
    set_var_int_screen_brightness((int)(brightness * 100));  
}

void action_act_raise_stepper(lv_event_t *e) {
    sendStepperCommand(1);  // Send command for clockwise
}

void action_act_lower_stepper(lv_event_t *e) {
    sendStepperCommand(2);  // Send command for counterclockwise
}

void action_act_brightness_slider_changed(lv_event_t *e) {
    lv_obj_t * slider = lv_event_get_target(e);
    int32_t slider_value = lv_slider_get_value(slider);  // 0–100 range

    // Convert to float (0.0–1.0 brightness)
    float new_brightness = slider_value / 100.0f;

    // Enforce minimum brightness if you want (e.g., 10%)
    if (new_brightness < 0.1f) {
        new_brightness = 0.1f;
    }

    brightness = new_brightness;

    // Set the screen backlight
    smartdisplay_lcd_set_backlight(brightness);

    // Update the label and bar to reflect slider movement
    update_brightness_display();
}

void action_act_tare_load_cells(lv_event_t *e) {
    sendStepperCommand(3);  // Send command to tare the load cells
}

void action_act_calibrate_airspeed(lv_event_t *e) {
    sendStepperCommand(4);  // Send command to re-calibrate the pitot tube airspeed
}