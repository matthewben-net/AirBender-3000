#ifndef EEZ_LVGL_UI_EVENTS_H
#define EEZ_LVGL_UI_EVENTS_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

extern void action_inc_brightness(lv_event_t * e);
extern void action_dec_brightness(lv_event_t * e);
extern void action_act_lower_stepper(lv_event_t * e);
extern void action_act_raise_stepper(lv_event_t * e);
extern void update_brightness_display();  // Add this line to declare the function

#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_EVENTS_H*/