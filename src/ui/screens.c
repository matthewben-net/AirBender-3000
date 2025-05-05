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

static void event_handler_cb_main_angle_bar(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
}

static void event_handler_cb_main_obj0(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            int32_t value = lv_slider_get_value(ta);
            set_var_int_screen_brightness(value);
        }
    }
}

static void event_handler_cb_main_obj1(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            bool value = lv_obj_has_state(ta, LV_STATE_CHECKED);
            set_var_bool_graph_speed(value);
        }
    }
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
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLL_CHAIN_HOR);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_tabview_add_tab(parent_obj, "H");
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                    lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
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
                            // eez_airspeed_chart
                            lv_obj_t *obj = lv_chart_create(parent_obj);
                            objects.eez_airspeed_chart = obj;
                            lv_obj_set_pos(obj, 228, 3);
                            lv_obj_set_size(obj, 180, 85);
                        }
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.obj2 = obj;
                            lv_obj_set_pos(obj, 258, 97);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_label_set_text(obj, "");
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
                            // lift_number
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.lift_number = obj;
                            lv_obj_set_pos(obj, -109, -65);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_label_set_text(obj, "");
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_32, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
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
                            // drag_number
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.drag_number = obj;
                            lv_obj_set_pos(obj, -110, 93);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_label_set_text(obj, "");
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_32, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
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
                            lv_bar_set_range(obj, -30, 30);
                            lv_bar_set_mode(obj, LV_BAR_MODE_SYMMETRICAL);
                            lv_obj_add_event_cb(obj, event_handler_cb_main_angle_bar, LV_EVENT_ALL, 0);
                        }
                        {
                            // string_mpu_angle
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.string_mpu_angle = obj;
                            lv_obj_set_pos(obj, 110, 78);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_label_set_text(obj, "");
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_28, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
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
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLL_CHAIN_HOR);
                    lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            lv_obj_set_pos(obj, -16, -16);
                            lv_obj_set_size(obj, 438, 960);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLL_CHAIN_HOR);
                            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // MoreDetails_SBS_Lift_Chart
                                    lv_obj_t *obj = lv_chart_create(parent_obj);
                                    objects.more_details_sbs_lift_chart = obj;
                                    lv_obj_set_pos(obj, 10, 10);
                                    lv_obj_set_size(obj, 209, 243);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                                    lv_obj_add_state(obj, LV_STATE_CHECKED);
                                }
                                {
                                    lv_obj_t *obj = lv_line_create(parent_obj);
                                    static lv_point_precise_t line_points[] = {
                                        { 0, 0 },
                                        { 209, 0 }
                                    };
                                    lv_line_set_points(obj, line_points, 2);
                                    lv_obj_set_pos(obj, 10, 126);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                }
                                {
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    lv_obj_set_pos(obj, 30, 268);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_label_set_text(obj, "Lift:");
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);
                                }
                                {
                                    // SBS_Lift_String
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.sbs_lift_string = obj;
                                    lv_obj_set_pos(obj, 93, 268);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_label_set_text(obj, "");
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);
                                }
                                {
                                    // SBS_Lift_Centerline
                                    lv_obj_t *obj = lv_line_create(parent_obj);
                                    static lv_point_precise_t line_points[] = {
                                        { 0, 0 },
                                        { 190, 0 }
                                    };
                                    lv_line_set_points(obj, line_points, 2);
                                    objects.sbs_lift_centerline = obj;
                                    lv_obj_set_pos(obj, 20, 304);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                }
                                {
                                    // MoreDetails_SBS_Drag_Chart
                                    lv_obj_t *obj = lv_chart_create(parent_obj);
                                    objects.more_details_sbs_drag_chart = obj;
                                    lv_obj_set_pos(obj, 229, 10);
                                    lv_obj_set_size(obj, 209, 243);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                                    lv_obj_add_state(obj, LV_STATE_CHECKED);
                                }
                                {
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    lv_obj_set_pos(obj, 249, 268);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_label_set_text(obj, "Drag:");
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);
                                }
                                {
                                    // SBS_Drag_String
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.sbs_drag_string = obj;
                                    lv_obj_set_pos(obj, 330, 268);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_label_set_text(obj, "");
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);
                                }
                                {
                                    lv_obj_t *obj = lv_line_create(parent_obj);
                                    static lv_point_precise_t line_points[] = {
                                        { 0, 0 },
                                        { 190, 0 }
                                    };
                                    lv_line_set_points(obj, line_points, 2);
                                    lv_obj_set_pos(obj, 235, 304);
                                    lv_obj_set_size(obj, 230, LV_SIZE_CONTENT);
                                }
                                {
                                    // MoreDetails_Full_Lift_Chart
                                    lv_obj_t *obj = lv_chart_create(parent_obj);
                                    objects.more_details_full_lift_chart = obj;
                                    lv_obj_set_pos(obj, 9, 336);
                                    lv_obj_set_size(obj, 428, 243);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                                    lv_obj_add_state(obj, LV_STATE_CHECKED);
                                }
                                {
                                    lv_obj_t *obj = lv_line_create(parent_obj);
                                    static lv_point_precise_t line_points[] = {
                                        { 0, 0 },
                                        { 428, 0 }
                                    };
                                    lv_line_set_points(obj, line_points, 2);
                                    lv_obj_set_pos(obj, 9, 457);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                }
                                {
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    lv_obj_set_pos(obj, 147, 586);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_label_set_text(obj, "Lift:");
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_36, LV_PART_MAIN | LV_STATE_DEFAULT);
                                }
                                {
                                    // MoreDetails_Full_Lift_String
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.more_details_full_lift_string = obj;
                                    lv_obj_set_pos(obj, 224, 586);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_label_set_text(obj, "");
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_36, LV_PART_MAIN | LV_STATE_DEFAULT);
                                }
                                {
                                    lv_obj_t *obj = lv_line_create(parent_obj);
                                    static lv_point_precise_t line_points[] = {
                                        { 0, 0 },
                                        { 380, 0 }
                                    };
                                    lv_line_set_points(obj, line_points, 2);
                                    lv_obj_set_pos(obj, 30, 630);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                }
                                {
                                    // MoreDetails_Full_Drag_Chart
                                    lv_obj_t *obj = lv_chart_create(parent_obj);
                                    objects.more_details_full_drag_chart = obj;
                                    lv_obj_set_pos(obj, 12, 651);
                                    lv_obj_set_size(obj, 428, 243);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                                    lv_obj_add_state(obj, LV_STATE_CHECKED);
                                }
                                {
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    lv_obj_set_pos(obj, 147, 898);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_label_set_text(obj, "Drag:");
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_36, LV_PART_MAIN | LV_STATE_DEFAULT);
                                }
                                {
                                    lv_obj_t *obj = lv_line_create(parent_obj);
                                    static lv_point_precise_t line_points[] = {
                                        { 0, 0 },
                                        { 380, 0 }
                                    };
                                    lv_line_set_points(obj, line_points, 2);
                                    lv_obj_set_pos(obj, 30, 945);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                }
                                {
                                    // MoreDetails_Full_Drag_String
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.more_details_full_drag_string = obj;
                                    lv_obj_set_pos(obj, 260, 898);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_label_set_text(obj, "");
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_36, LV_PART_MAIN | LV_STATE_DEFAULT);
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
                                    lv_obj_t *obj = lv_slider_create(parent_obj);
                                    objects.obj0 = obj;
                                    lv_obj_set_pos(obj, 20, 69);
                                    lv_obj_set_size(obj, 404, 18);
                                    lv_obj_add_event_cb(obj, action_act_brightness_slider_changed, LV_EVENT_VALUE_CHANGED, (void *)0);
                                    lv_obj_add_event_cb(obj, event_handler_cb_main_obj0, LV_EVENT_ALL, 0);
                                }
                                {
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    lv_obj_set_pos(obj, 61, 22);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_label_set_text(obj, "Screen Brightness");
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_36, LV_PART_MAIN | LV_STATE_DEFAULT);
                                }
                                {
                                    // screen_brightness_string
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.screen_brightness_string = obj;
                                    lv_obj_set_pos(obj, -3, -50);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_label_set_text(obj, "");
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_22, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                }
                                {
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    lv_obj_set_pos(obj, 34, 122);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_label_set_text(obj, "Tare Load Cells");
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_22, LV_PART_MAIN | LV_STATE_DEFAULT);
                                }
                                {
                                    // load_cell_tare_button
                                    lv_obj_t *obj = lv_btn_create(parent_obj);
                                    objects.load_cell_tare_button = obj;
                                    lv_obj_set_pos(obj, 73, 155);
                                    lv_obj_set_size(obj, 82, 35);
                                    lv_obj_add_event_cb(obj, action_act_tare_load_cells, LV_EVENT_PRESSED, (void *)0);
                                    lv_obj_set_style_radius(obj, 30, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xffba0000), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_color(obj, lv_color_hex(0xff410000), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            lv_obj_set_pos(obj, 0, 0);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_label_set_text(obj, "Tare");
                                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                        }
                                    }
                                }
                                {
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    lv_obj_set_pos(obj, 271, 122);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_label_set_text(obj, "Graph Speed");
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_22, LV_PART_MAIN | LV_STATE_DEFAULT);
                                }
                                {
                                    lv_obj_t *obj = lv_switch_create(parent_obj);
                                    objects.obj1 = obj;
                                    lv_obj_set_pos(obj, 319, 153);
                                    lv_obj_set_size(obj, 50, 25);
                                    lv_obj_add_event_cb(obj, event_handler_cb_main_obj1, LV_EVENT_ALL, 0);
                                }
                                {
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    lv_obj_set_pos(obj, 375, 158);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_label_set_text(obj, "Fast :)");
                                }
                                {
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    lv_obj_set_pos(obj, 268, 158);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_label_set_text(obj, "Slow :(");
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
        const char *new_val = get_var_string_airspeed_label();
        const char *cur_val = lv_label_get_text(objects.obj2);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj2;
            lv_label_set_text(objects.obj2, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = get_var_string_lift_force_label();
        const char *cur_val = lv_label_get_text(objects.lift_number);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.lift_number;
            lv_label_set_text(objects.lift_number, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = get_var_string_drag_force_label();
        const char *cur_val = lv_label_get_text(objects.drag_number);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.drag_number;
            lv_label_set_text(objects.drag_number, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        int32_t new_val = get_var_float_mpu_angle_number();
        int32_t cur_val = lv_bar_get_value(objects.angle_bar);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.angle_bar;
            lv_bar_set_value(objects.angle_bar, new_val, LV_ANIM_ON);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = get_var_string_mpu_angle_data();
        const char *cur_val = lv_label_get_text(objects.string_mpu_angle);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.string_mpu_angle;
            lv_label_set_text(objects.string_mpu_angle, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = get_var_string_lift_force_label();
        const char *cur_val = lv_label_get_text(objects.sbs_lift_string);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.sbs_lift_string;
            lv_label_set_text(objects.sbs_lift_string, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = get_var_string_drag_force_label();
        const char *cur_val = lv_label_get_text(objects.sbs_drag_string);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.sbs_drag_string;
            lv_label_set_text(objects.sbs_drag_string, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = get_var_string_lift_force_label();
        const char *cur_val = lv_label_get_text(objects.more_details_full_lift_string);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.more_details_full_lift_string;
            lv_label_set_text(objects.more_details_full_lift_string, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = get_var_string_drag_force_label();
        const char *cur_val = lv_label_get_text(objects.more_details_full_drag_string);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.more_details_full_drag_string;
            lv_label_set_text(objects.more_details_full_drag_string, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        int32_t new_val = get_var_int_screen_brightness();
        int32_t cur_val = lv_slider_get_value(objects.obj0);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj0;
            lv_slider_set_value(objects.obj0, new_val, LV_ANIM_ON);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = get_var_eezvar_screen_brightness();
        const char *cur_val = lv_label_get_text(objects.screen_brightness_string);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.screen_brightness_string;
            lv_label_set_text(objects.screen_brightness_string, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = get_var_bool_graph_speed();
        bool cur_val = lv_obj_has_state(objects.obj1, LV_STATE_CHECKED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj1;
            if (new_val) lv_obj_add_state(objects.obj1, LV_STATE_CHECKED);
            else lv_obj_clear_state(objects.obj1, LV_STATE_CHECKED);
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
