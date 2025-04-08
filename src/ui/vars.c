#include <lvgl.h>
#include <string.h>
#include "vars.h"
#include "screens.h"
#include "ui.h"

// Global variable for brightness string
char eezvar_screen_brightness[100] = { 0 };

int32_t int_screen_brightness = 30;  // Initialize to 30% to match your default brightness

// Screen brightness variable stuff for the text label
const char *get_var_eezvar_screen_brightness() {
    return eezvar_screen_brightness;
}

void set_var_eezvar_screen_brightness(const char *value) {
    strncpy(eezvar_screen_brightness, value, sizeof(eezvar_screen_brightness) - 1);
    eezvar_screen_brightness[sizeof(eezvar_screen_brightness) - 1] = '\0';  // Ensure null termination
}
// Screen brightness variable stuff for the bar display
int32_t get_var_int_screen_brightness() {
    return int_screen_brightness;
}

void set_var_int_screen_brightness(int32_t value) {
    int_screen_brightness = value;
}

char string_mpu_angle_data[100] = { 0 };

const char *get_var_string_mpu_angle_data() {
    return string_mpu_angle_data;
}

// Angle string that I can use to display x.xx Degrees where x.xx is the angle number
void set_var_string_mpu_angle_data(const char *value) {
    strncpy(string_mpu_angle_data, value, sizeof(string_mpu_angle_data) / sizeof(char));
    string_mpu_angle_data[sizeof(string_mpu_angle_data) / sizeof(char) - 1] = 0;
}
