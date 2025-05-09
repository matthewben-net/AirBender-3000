#include <lvgl.h>
#include "mpu.h"
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

// Angle float used to set the angle bar graph
float float_mpu_angle_number;

float get_var_float_mpu_angle_number() {
    return float_mpu_angle_number;
}

void set_var_float_mpu_angle_number(float value) {
    float_mpu_angle_number = value;
}

// Load Cell force floats
float float_drag_force;
float float_lift_force;

float get_var_float_drag_force() {
    return float_drag_force;
}

void set_var_float_drag_force(float value) {
    float_drag_force = value;
}


float get_var_float_lift_force() {
    return float_lift_force;
}

void set_var_float_lift_force(float value) {
    float_lift_force = value;
}

// Load cell force strings for labels

char string_drag_force_label[100] = { 0 };

const char *get_var_string_drag_force_label() {
    return string_drag_force_label;
}

void set_var_string_drag_force_label(const char *value) {
    strncpy(string_drag_force_label, value, sizeof(string_drag_force_label) / sizeof(char));
    string_drag_force_label[sizeof(string_drag_force_label) / sizeof(char) - 1] = 0;
}

char string_lift_force_label[100] = { 0 };

const char *get_var_string_lift_force_label() {
    return string_lift_force_label;
}

void set_var_string_lift_force_label(const char *value) {
    strncpy(string_lift_force_label, value, sizeof(string_lift_force_label) / sizeof(char));
    string_lift_force_label[sizeof(string_lift_force_label) / sizeof(char) - 1] = 0;
}

char string_airspeed_label[100] = { 0 };

const char *get_var_string_airspeed_label() {
    return string_airspeed_label;
}

void set_var_string_airspeed_label(const char *value) {
    strncpy(string_airspeed_label, value, sizeof(string_airspeed_label) / sizeof(char));
    string_airspeed_label[sizeof(string_airspeed_label) / sizeof(char) - 1] = 0;
}

bool bool_graph_speed;

bool get_var_bool_graph_speed() {
    return bool_graph_speed;
}

void set_var_bool_graph_speed(bool value) {
    bool_graph_speed = value;
}
