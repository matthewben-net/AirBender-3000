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
    FLOW_GLOBAL_VARIABLE_INT_SCREEN_BRIGHTNESS = 1
};

// Native global variables

extern const char *get_var_eezvar_screen_brightness();
extern void set_var_eezvar_screen_brightness(const char *value);
extern int32_t get_var_int_screen_brightness();
extern void set_var_int_screen_brightness(int32_t value);


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_VARS_H*/