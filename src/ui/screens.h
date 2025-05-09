#ifndef EEZ_LVGL_UI_SCREENS_H
#define EEZ_LVGL_UI_SCREENS_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _objects_t {
    lv_obj_t *main;
    lv_obj_t *splash_screen;
    lv_obj_t *starting_splash_blank;
    lv_obj_t *ending_splash_blank;
    lv_obj_t *angle_bar;
    lv_obj_t *obj0;
    lv_obj_t *obj1;
    lv_obj_t *speed_panel;
    lv_obj_t *eez_airspeed_chart;
    lv_obj_t *lift_panel;
    lv_obj_t *lift_number;
    lv_obj_t *drag_panel;
    lv_obj_t *drag_number;
    lv_obj_t *angle_panel;
    lv_obj_t *string_mpu_angle;
    lv_obj_t *more_details_sbs_lift_chart;
    lv_obj_t *sbs_lift_string;
    lv_obj_t *sbs_lift_centerline;
    lv_obj_t *more_details_sbs_drag_chart;
    lv_obj_t *sbs_drag_string;
    lv_obj_t *more_details_full_lift_chart;
    lv_obj_t *more_details_full_lift_string;
    lv_obj_t *more_details_full_drag_chart;
    lv_obj_t *more_details_full_drag_string_1;
    lv_obj_t *screen_brightness_string;
    lv_obj_t *load_cell_tare_button;
    lv_obj_t *airspeed_calibrate_button;
    lv_obj_t *obj2;
} objects_t;

extern objects_t objects;

enum ScreensEnum {
    SCREEN_ID_MAIN = 1,
    SCREEN_ID_SPLASH_SCREEN = 2,
    SCREEN_ID_STARTING_SPLASH_BLANK = 3,
    SCREEN_ID_ENDING_SPLASH_BLANK = 4,
};

void create_screen_main();
void tick_screen_main();

void create_screen_splash_screen();
void tick_screen_splash_screen();

void create_screen_starting_splash_blank();
void tick_screen_starting_splash_blank();

void create_screen_ending_splash_blank();
void tick_screen_ending_splash_blank();

void tick_screen_by_id(enum ScreensEnum screenId);
void tick_screen(int screen_index);

void create_screens();


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_SCREENS_H*/