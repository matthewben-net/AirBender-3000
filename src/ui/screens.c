#include <string.h>

#include "screens.h"
#include "images.h"
#include "fonts.h"
#include "actions.h"
#include "vars.h"
#include "styles.h"
#include "ui.h"

#include <string.h>

objects_t objects;
lv_obj_t *tick_value_change_obj;

static void event_handler_cb_main_obj0(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
}

void create_screen_main() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.main = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 480, 320);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_tabview_create(parent_obj);
            lv_tabview_set_tab_bar_position(obj, LV_DIR_LEFT);
            lv_tabview_set_tab_bar_size(obj, 32);
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 480, 320);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_tabview_add_tab(parent_obj, "H");
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // Speed_Panel
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.speed_panel = obj;
                            lv_obj_set_pos(obj, 213, -6);
                            lv_obj_set_size(obj, 209, 145);
                        }
                        {
                            lv_obj_t *obj = lv_chart_create(parent_obj);
                            lv_obj_set_pos(obj, 228, 3);
                            lv_obj_set_size(obj, 180, 85);
                        }
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 258, 97);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_label_set_text(obj, "88 mph");
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_28, LV_PART_MAIN | LV_STATE_DEFAULT);
                        }
                        {
                            // Lift_Panel
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.lift_panel = obj;
                            lv_obj_set_pos(obj, -6, -6);
                            lv_obj_set_size(obj, 209, 145);
                        }
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 69, -4);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_label_set_text(obj, "Lift");
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_36, LV_PART_MAIN | LV_STATE_DEFAULT);
                        }
                        {
                            lv_obj_t *obj = lv_line_create(parent_obj);
                            static lv_point_precise_t line_points[] = {
                                { 0, 0 },
                                { 169, 0 }
                            };
                            lv_line_set_points(obj, line_points, 2);
                            lv_obj_set_pos(obj, 16, 40);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                        }
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 54, 71);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_label_set_text(obj, "420N");
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_32, LV_PART_MAIN | LV_STATE_DEFAULT);
                        }
                        {
                            // Drag_Panel
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.drag_panel = obj;
                            lv_obj_set_pos(obj, -6, 149);
                            lv_obj_set_size(obj, 209, 145);
                        }
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 55, 152);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_label_set_text(obj, "Drag");
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_36, LV_PART_MAIN | LV_STATE_DEFAULT);
                        }
                        {
                            lv_obj_t *obj = lv_line_create(parent_obj);
                            static lv_point_precise_t line_points[] = {
                                { 0, 0 },
                                { 169, 0 }
                            };
                            lv_line_set_points(obj, line_points, 2);
                            lv_obj_set_pos(obj, 16, 195);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                        }
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 54, 226);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_label_set_text(obj, "969N");
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_32, LV_PART_MAIN | LV_STATE_DEFAULT);
                        }
                        {
                            // Angle_Panel
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.angle_panel = obj;
                            lv_obj_set_pos(obj, 213, 149);
                            lv_obj_set_size(obj, 209, 145);
                        }
                        {
                            // Angle_Bar
                            lv_obj_t *obj = lv_bar_create(parent_obj);
                            objects.angle_bar = obj;
                            lv_obj_set_pos(obj, 230, 162);
                            lv_obj_set_size(obj, 169, 20);
                            lv_bar_set_range(obj, -100, 100);
                            lv_bar_set_mode(obj, LV_BAR_MODE_SYMMETRICAL);
                            lv_bar_set_value(obj, 25, LV_ANIM_ON);
                        }
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 247, 196);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_label_set_text(obj, "3 Degrees");
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_28, LV_PART_MAIN | LV_STATE_DEFAULT);
                        }
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            lv_obj_set_pos(obj, 230, 244);
                            lv_obj_set_size(obj, 72, 33);
                            lv_obj_add_event_cb(obj, action_act_lower_stepper, LV_EVENT_PRESSING, (void *)0);
                            lv_obj_set_style_radius(obj, 30, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    lv_obj_set_pos(obj, 0, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_label_set_text(obj, "Lower");
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                }
                            }
                        }
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            lv_obj_set_pos(obj, 327, 244);
                            lv_obj_set_size(obj, 72, 33);
                            lv_obj_add_event_cb(obj, action_act_raise_stepper, LV_EVENT_PRESSING, (void *)0);
                            lv_obj_set_style_radius(obj, 30, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    lv_obj_set_pos(obj, 0, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_label_set_text(obj, "Raise");
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                }
                            }
                        }
                    }
                }
                {
                    lv_obj_t *obj = lv_tabview_add_tab(parent_obj, "F");
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            lv_obj_set_pos(obj, -16, -16);
                            lv_obj_set_size(obj, 448, 320);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    lv_obj_t *obj = lv_chart_create(parent_obj);
                                    lv_obj_set_pos(obj, 10, 10);
                                    lv_obj_set_size(obj, 428, 300);
                                }
                            }
                        }
                    }
                }
                {
                    lv_obj_t *obj = lv_tabview_add_tab(parent_obj, "S");
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            lv_obj_set_pos(obj, -16, -16);
                            lv_obj_set_size(obj, 448, 320);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    lv_obj_t *obj = lv_obj_create(parent_obj);
                                    lv_obj_set_pos(obj, 10, 10);
                                    lv_obj_set_size(obj, 428, 300);
                                }
                                {
                                    lv_obj_t *obj = lv_bar_create(parent_obj);
                                    objects.obj0 = obj;
                                    lv_obj_set_pos(obj, 20, 90);
                                    lv_obj_set_size(obj, 408, 28);
                                    lv_obj_add_event_cb(obj, event_handler_cb_main_obj0, LV_EVENT_ALL, 0);
                                }
                                {
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    lv_obj_set_pos(obj, 61, 30);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_label_set_text(obj, "Screen Brightness");
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_36, LV_PART_MAIN | LV_STATE_DEFAULT);
                                }
                                {
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.obj1 = obj;
                                    lv_obj_set_pos(obj, 0, 17);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_label_set_text(obj, "");
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_22, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                }
                                {
                                    // btn_decrease_brightness
                                    lv_obj_t *obj = lv_btn_create(parent_obj);
                                    objects.btn_decrease_brightness = obj;
                                    lv_obj_set_pos(obj, 73, 218);
                                    lv_obj_set_size(obj, 130, 39);
                                    lv_obj_add_event_cb(obj, action_dec_brightness, LV_EVENT_PRESSING, (void *)0);
                                    lv_obj_set_style_radius(obj, 30, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            lv_obj_set_pos(obj, 0, 0);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_label_set_text(obj, "Decrease");
                                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);
                                        }
                                    }
                                }
                                {
                                    // btn_increase_brightness
                                    lv_obj_t *obj = lv_btn_create(parent_obj);
                                    objects.btn_increase_brightness = obj;
                                    lv_obj_set_pos(obj, 245, 218);
                                    lv_obj_set_size(obj, 130, 39);
                                    lv_obj_add_event_cb(obj, action_inc_brightness, LV_EVENT_PRESSING, (void *)0);
                                    lv_obj_set_style_radius(obj, 30, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            lv_obj_set_pos(obj, 0, 0);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_label_set_text(obj, "Increase");
                                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    
    tick_screen_main();
}

void tick_screen_main() {
    {
        int32_t new_val = get_var_int_screen_brightness();
        int32_t cur_val = lv_bar_get_value(objects.obj0);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj0;
            lv_bar_set_value(objects.obj0, new_val, LV_ANIM_ON);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = get_var_eezvar_screen_brightness();
        const char *cur_val = lv_label_get_text(objects.obj1);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj1;
            lv_label_set_text(objects.obj1, new_val);
            tick_value_change_obj = NULL;
        }
    }
}



typedef void (*tick_screen_func_t)();
tick_screen_func_t tick_screen_funcs[] = {
    tick_screen_main,
};
void tick_screen(int screen_index) {
    tick_screen_funcs[screen_index]();
}
void tick_screen_by_id(enum ScreensEnum screenId) {
    tick_screen_funcs[screenId - 1]();
}

void create_screens() {
    lv_disp_t *dispp = lv_disp_get_default();
    lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), true, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    
    create_screen_main();
}
