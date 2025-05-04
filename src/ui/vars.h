#ifndef EEZ_LVGL_UI_VARS_H
#define EEZ_LVGL_UI_VARS_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

// enum declarations



// Flow global variables

enum FlowGlobalVariables {
    FLOW_GLOBAL_VARIABLE_EEZVAR_SCREEN_BRIGHTNESS = 0,
    FLOW_GLOBAL_VARIABLE_INT_SCREEN_BRIGHTNESS = 1,
    FLOW_GLOBAL_VARIABLE_STRING_MPU_ANGLE_DATA = 2,
    FLOW_GLOBAL_VARIABLE_FLOAT_MPU_ANGLE_NUMBER = 3,
    FLOW_GLOBAL_VARIABLE_INT_MPU_ADDRESS_0_1_68_69 = 4,
    FLOW_GLOBAL_VARIABLE_STRING_MPU_ADDRESS_IN_UI = 5,
    FLOW_GLOBAL_VARIABLE_FLOAT_DRAG_FORCE = 6,
    FLOW_GLOBAL_VARIABLE_FLOAT_LIFT_FORCE = 7,
    FLOW_GLOBAL_VARIABLE_STRING_DRAG_FORCE_LABEL = 8,
    FLOW_GLOBAL_VARIABLE_STRING_LIFT_FORCE_LABEL = 9
};

// Native global variables

extern const char *get_var_eezvar_screen_brightness();
extern void set_var_eezvar_screen_brightness(const char *value);
extern int32_t get_var_int_screen_brightness();
extern void set_var_int_screen_brightness(int32_t value);
extern const char *get_var_string_mpu_angle_data();
extern void set_var_string_mpu_angle_data(const char *value);
extern float get_var_float_mpu_angle_number();
extern void set_var_float_mpu_angle_number(float value);
extern int32_t get_var_int_mpu_address_0_1_68_69();
extern void set_var_int_mpu_address_0_1_68_69(int32_t value);
extern const char *get_var_string_mpu_address_in_ui();
extern void set_var_string_mpu_address_in_ui(const char *value);
extern float get_var_float_drag_force();
extern void set_var_float_drag_force(float value);
extern float get_var_float_lift_force();
extern void set_var_float_lift_force(float value);
extern const char *get_var_string_drag_force_label();
extern void set_var_string_drag_force_label(const char *value);
extern const char *get_var_string_lift_force_label();
extern void set_var_string_lift_force_label(const char *value);


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_VARS_H*/