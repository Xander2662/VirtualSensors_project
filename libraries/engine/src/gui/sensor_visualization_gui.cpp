/**
 * @file sensor_visualization_gui.cpp
 * @brief Implementation of the SensorVisualizationGui class
 *
 * This source file implements the SensorVisualizationGui functionality for
 * active sensor visualization, data display, and navigation.
 *
 * @copyright 2025 MTA
 * @author Ing. Jiri Konecny, Ondřej Wrubel
 */

#include "sensor_visualization_gui.hpp"
#include "../helpers.hpp"
#include "gui_callbacks.hpp"

SensorVisualizationGui::SensorVisualizationGui(SensorManager &manager) : sensorManager(manager) {
    // Initialize all GUI pointers to nullptr
    ui_SensorWidget = nullptr;
    ui_SensorLabel = nullptr;
    ui_ContainerForValue_1 = nullptr;
    ui_VisualColorForValue_1 = nullptr;
    ui_LabelValueValue_1 = nullptr;
    ui_LabelDescValue_1 = nullptr;
    ui_LabelTypeValue_1 = nullptr;
    ui_VisualColorForValue_2 = nullptr;
    ui_ContainerForValue_2 = nullptr;
    ui_LabelValueValue_2 = nullptr;
    ui_LabelDescValue_2 = nullptr;
    ui_LabelTypeValue_2 = nullptr;
    ui_Chart = nullptr;
    ui_Chart_series_V1 = nullptr;
    ui_Chart_series_V2 = nullptr;
    ui_SensorWidgetWiki = nullptr;
    ui_SensorLabelWiki = nullptr;
    ui_SensorLabelDescription = nullptr;
    ui_SensorImage = nullptr;
    ui_btnPrev = nullptr;
    ui_btnPrevLabel = nullptr;
    ui_btnNext = nullptr;
    ui_btnNextLabel = nullptr;
    ui_btnConfirm = nullptr;
    ui_btnConfirmLabel = nullptr;
    ui_btnSync = nullptr;
    ui_btnSyncLabel = nullptr;
    ui_btnBack = nullptr;
    ui_btnBackLabel = nullptr;
}

void SensorVisualizationGui::init() {
    if (initialized) return;
    
    try {
        logMessage("Initializing SensorVisualizationGui...\n");
        constructVisualization();
        constructWiki();
        initialized = true;
        logMessage("SensorVisualizationGui initialization completed!\n");
    }
    catch (const std::exception &e) {
        logMessage("SensorVisualizationGui initialization failed: %s\n", e.what());
        initialized = false;
    }
}

void SensorVisualizationGui::constructVisualization() {
    logMessage("\t>constructing sensor visualization...\n");
    
    // Main sensor widget container
    ui_SensorWidget = lv_obj_create(lv_scr_act());
    lv_obj_remove_style_all(ui_SensorWidget);
    lv_obj_set_width(ui_SensorWidget, 760);
    lv_obj_set_height(ui_SensorWidget, 440);
    lv_obj_set_align(ui_SensorWidget, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_SensorWidget, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE |
                                          LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC |
                                          LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN);
    lv_obj_set_style_radius(ui_SensorWidget, 15, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_SensorWidget, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_SensorWidget, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_SensorWidget, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_SensorWidget, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_SensorWidget, 2, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Sensor title label
    ui_SensorLabel = lv_label_create(ui_SensorWidget);
    lv_obj_set_width(ui_SensorLabel, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_SensorLabel, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_SensorLabel, 0);
    lv_obj_set_y(ui_SensorLabel, -185);
    lv_obj_set_align(ui_SensorLabel, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_SensorLabel, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE |
                                         LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
                                         LV_OBJ_FLAG_SCROLL_CHAIN);
    lv_obj_set_style_text_color(ui_SensorLabel, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_SensorLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_SensorLabel, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);
    
    // Value container 1
    ui_ContainerForValue_1 = lv_obj_create(ui_SensorWidget);
    lv_obj_remove_style_all(ui_ContainerForValue_1);
    lv_obj_set_width(ui_ContainerForValue_1, 230);
    lv_obj_set_height(ui_ContainerForValue_1, 118);
    lv_obj_set_x(ui_ContainerForValue_1, -230);
    lv_obj_set_y(ui_ContainerForValue_1, 55);
    lv_obj_set_align(ui_ContainerForValue_1, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_ContainerForValue_1,
                      LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE |
                          LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
                          LV_OBJ_FLAG_SCROLL_CHAIN);
    lv_obj_set_style_radius(ui_ContainerForValue_1, 15, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_ContainerForValue_1, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ContainerForValue_1, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_ContainerForValue_1, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_ContainerForValue_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_ContainerForValue_1, 2, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Color indicator for value 1
    ui_VisualColorForValue_1 = lv_obj_create(ui_ContainerForValue_1);
    lv_obj_remove_style_all(ui_VisualColorForValue_1);
    lv_obj_set_width(ui_VisualColorForValue_1, 20);
    lv_obj_set_height(ui_VisualColorForValue_1, 20);
    lv_obj_set_x(ui_VisualColorForValue_1, -10);
    lv_obj_set_y(ui_VisualColorForValue_1, 10);
    lv_obj_set_align(ui_VisualColorForValue_1, LV_ALIGN_TOP_RIGHT);
    lv_obj_clear_flag(ui_VisualColorForValue_1, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_radius(ui_VisualColorForValue_1, 1000, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_VisualColorForValue_1, lv_color_hex(0x009BFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_VisualColorForValue_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Value label for value 1
    ui_LabelValueValue_1 = lv_label_create(ui_ContainerForValue_1);
    lv_obj_set_width(ui_LabelValueValue_1, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_LabelValueValue_1, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_LabelValueValue_1, 0);
    lv_obj_set_y(ui_LabelValueValue_1, -5);
    lv_obj_set_align(ui_LabelValueValue_1, LV_ALIGN_CENTER);
    lv_label_set_text(ui_LabelValueValue_1, "0");
    lv_obj_clear_flag(ui_LabelValueValue_1,
                      LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE |
                          LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
                          LV_OBJ_FLAG_SCROLL_CHAIN);
    lv_obj_set_style_text_color(ui_LabelValueValue_1, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LabelValueValue_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LabelValueValue_1, &lv_font_montserrat_40, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Description label for value 1
    ui_LabelDescValue_1 = lv_label_create(ui_ContainerForValue_1);
    lv_obj_set_width(ui_LabelDescValue_1, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_LabelDescValue_1, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_LabelDescValue_1, 0);
    lv_obj_set_y(ui_LabelDescValue_1, 30);
    lv_obj_set_align(ui_LabelDescValue_1, LV_ALIGN_CENTER);
    lv_label_set_text(ui_LabelDescValue_1, "[°C]");
    lv_obj_clear_flag(ui_LabelDescValue_1,
                      LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE |
                          LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
                          LV_OBJ_FLAG_SCROLL_CHAIN);
    lv_obj_set_style_text_color(ui_LabelDescValue_1, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LabelDescValue_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LabelDescValue_1, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Type label for value 1
    ui_LabelTypeValue_1 = lv_label_create(ui_ContainerForValue_1);
    lv_obj_set_width(ui_LabelTypeValue_1, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_LabelTypeValue_1, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_LabelTypeValue_1, 15);
    lv_obj_set_y(ui_LabelTypeValue_1, 10);
    lv_label_set_text(ui_LabelTypeValue_1, "Value");
    lv_obj_set_style_text_color(ui_LabelTypeValue_1, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LabelTypeValue_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    
    // Value container 2 (for sensors with multiple values like DHT11)
    ui_ContainerForValue_2 = lv_obj_create(ui_SensorWidget);
    lv_obj_remove_style_all(ui_ContainerForValue_2);
    lv_obj_set_width(ui_ContainerForValue_2, 230);
    lv_obj_set_height(ui_ContainerForValue_2, 118);
    lv_obj_set_x(ui_ContainerForValue_2, -230);
    lv_obj_set_y(ui_ContainerForValue_2, -85);
    lv_obj_set_align(ui_ContainerForValue_2, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_ContainerForValue_2,
                      LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE |
                          LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
                          LV_OBJ_FLAG_SCROLL_CHAIN);
    lv_obj_set_style_radius(ui_ContainerForValue_2, 15, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_ContainerForValue_2, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ContainerForValue_2, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_ContainerForValue_2, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_ContainerForValue_2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_ContainerForValue_2, 2, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Color indicator for value 2
    ui_VisualColorForValue_2 = lv_obj_create(ui_ContainerForValue_2);
    lv_obj_remove_style_all(ui_VisualColorForValue_2);
    lv_obj_set_width(ui_VisualColorForValue_2, 20);
    lv_obj_set_height(ui_VisualColorForValue_2, 20);
    lv_obj_set_x(ui_VisualColorForValue_2, -10);
    lv_obj_set_y(ui_VisualColorForValue_2, 10);
    lv_obj_set_align(ui_VisualColorForValue_2, LV_ALIGN_TOP_RIGHT);
    lv_obj_clear_flag(ui_VisualColorForValue_2, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_radius(ui_VisualColorForValue_2, 1000, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_VisualColorForValue_2, lv_color_hex(0xFF6B35), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_VisualColorForValue_2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Value label for value 2
    ui_LabelValueValue_2 = lv_label_create(ui_ContainerForValue_2);
    lv_obj_set_width(ui_LabelValueValue_2, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_LabelValueValue_2, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_LabelValueValue_2, 0);
    lv_obj_set_y(ui_LabelValueValue_2, -5);
    lv_obj_set_align(ui_LabelValueValue_2, LV_ALIGN_CENTER);
    lv_label_set_text(ui_LabelValueValue_2, "0");
    lv_obj_clear_flag(ui_LabelValueValue_2,
                      LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE |
                          LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
                          LV_OBJ_FLAG_SCROLL_CHAIN);
    lv_obj_set_style_text_color(ui_LabelValueValue_2, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LabelValueValue_2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LabelValueValue_2, &lv_font_montserrat_40, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Description label for value 2
    ui_LabelDescValue_2 = lv_label_create(ui_ContainerForValue_2);
    lv_obj_set_width(ui_LabelDescValue_2, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_LabelDescValue_2, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_LabelDescValue_2, 0);
    lv_obj_set_y(ui_LabelDescValue_2, 30);
    lv_obj_set_align(ui_LabelDescValue_2, LV_ALIGN_CENTER);
    lv_label_set_text(ui_LabelDescValue_2, "[%]");
    lv_obj_clear_flag(ui_LabelDescValue_2,
                      LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE |
                          LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
                          LV_OBJ_FLAG_SCROLL_CHAIN);
    lv_obj_set_style_text_color(ui_LabelDescValue_2, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LabelDescValue_2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LabelDescValue_2, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Type label for value 2
    ui_LabelTypeValue_2 = lv_label_create(ui_ContainerForValue_2);
    lv_obj_set_width(ui_LabelTypeValue_2, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_LabelTypeValue_2, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_LabelTypeValue_2, 15);
    lv_obj_set_y(ui_LabelTypeValue_2, 10);
    lv_label_set_text(ui_LabelTypeValue_2, "Value2");
    lv_obj_set_style_text_color(ui_LabelTypeValue_2, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LabelTypeValue_2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    
    // Initially hide second value container
    lv_obj_add_flag(ui_ContainerForValue_2, LV_OBJ_FLAG_HIDDEN);
    
    // Create chart for sensor history
    ui_Chart = lv_chart_create(ui_SensorWidget);
    lv_obj_set_width(ui_Chart, 410);
    lv_obj_set_height(ui_Chart, 280);
    lv_obj_set_x(ui_Chart, 150);
    lv_obj_set_y(ui_Chart, 20);
    lv_obj_set_align(ui_Chart, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_Chart, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE |
                                    LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE);
    lv_chart_set_type(ui_Chart, LV_CHART_TYPE_LINE);
    lv_chart_set_div_line_count(ui_Chart, 9, 10);
    lv_chart_set_axis_tick(ui_Chart, LV_CHART_AXIS_PRIMARY_X, 10, 0, 10, 1, true, 50);
    lv_chart_set_axis_tick(ui_Chart, LV_CHART_AXIS_PRIMARY_Y, 10, 5, 5, 2, true, 50);

    // Chart series for value 1
    ui_Chart_series_V1 = lv_chart_add_series(ui_Chart, lv_color_hex(0x009BFF), LV_CHART_AXIS_PRIMARY_Y);
    
    // Chart series for value 2 (different color)
    ui_Chart_series_V2 = lv_chart_add_series(ui_Chart, lv_color_hex(0xFF6B35), LV_CHART_AXIS_PRIMARY_Y);
    
    // Chart styling
    lv_obj_set_style_bg_color(ui_Chart, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Chart, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_Chart, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_Chart, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_Chart, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_line_color(ui_Chart, lv_color_hex(0x000000), LV_PART_TICKS | LV_STATE_DEFAULT);
    lv_obj_set_style_line_opa(ui_Chart, 255, LV_PART_TICKS | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui_Chart, lv_color_hex(0x000000), LV_PART_TICKS | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Chart, 255, LV_PART_TICKS | LV_STATE_DEFAULT);
    
    // Add navigation and control buttons
    addNavButtonsToWidget(ui_SensorWidget, true);
    addControlButtonsToWidget(ui_SensorWidget);
    
    logMessage("\t>sensor visualization constructed!\n");
}

void SensorVisualizationGui::constructWiki() {
    logMessage("\t>constructing sensor wiki...\n");
    
    // Main wiki widget container
    ui_SensorWidgetWiki = lv_obj_create(lv_scr_act());
    lv_obj_remove_style_all(ui_SensorWidgetWiki);
    lv_obj_set_width(ui_SensorWidgetWiki, 760);
    lv_obj_set_height(ui_SensorWidgetWiki, 440);
    lv_obj_set_align(ui_SensorWidgetWiki, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_SensorWidgetWiki, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE |
                                              LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC |
                                              LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN);
    lv_obj_set_style_radius(ui_SensorWidgetWiki, 15, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_SensorWidgetWiki, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_SensorWidgetWiki, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_SensorWidgetWiki, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_SensorWidgetWiki, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_SensorWidgetWiki, 2, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Wiki sensor title label
    ui_SensorLabelWiki = lv_label_create(ui_SensorWidgetWiki);
    lv_obj_set_width(ui_SensorLabelWiki, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_SensorLabelWiki, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_SensorLabelWiki, 0);
    lv_obj_set_y(ui_SensorLabelWiki, -185);
    lv_obj_set_align(ui_SensorLabelWiki, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_SensorLabelWiki, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE |
                                             LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
                                             LV_OBJ_FLAG_SCROLL_CHAIN);
    lv_obj_set_style_text_color(ui_SensorLabelWiki, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_SensorLabelWiki, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_SensorLabelWiki, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Sensor description label
    ui_SensorLabelDescription = lv_label_create(ui_SensorWidgetWiki);
    lv_obj_set_width(ui_SensorLabelDescription, 500);
    lv_obj_set_height(ui_SensorLabelDescription, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_SensorLabelDescription, 0);
    lv_obj_set_y(ui_SensorLabelDescription, -50);
    lv_obj_set_align(ui_SensorLabelDescription, LV_ALIGN_CENTER);
    lv_label_set_long_mode(ui_SensorLabelDescription, LV_LABEL_LONG_WRAP);
    lv_label_set_text(ui_SensorLabelDescription, "Sensor description will be displayed here...");
    lv_obj_clear_flag(ui_SensorLabelDescription, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE |
                                                    LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
                                                    LV_OBJ_FLAG_SCROLL_CHAIN);
    lv_obj_set_style_text_color(ui_SensorLabelDescription, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_SensorLabelDescription, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_SensorLabelDescription, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Sensor image placeholder
    ui_SensorImage = lv_obj_create(ui_SensorWidgetWiki);
    lv_obj_remove_style_all(ui_SensorImage);
    lv_obj_set_width(ui_SensorImage, 200);
    lv_obj_set_height(ui_SensorImage, 150);
    lv_obj_set_x(ui_SensorImage, 0);
    lv_obj_set_y(ui_SensorImage, 50);
    lv_obj_set_align(ui_SensorImage, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_SensorImage, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_radius(ui_SensorImage, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_SensorImage, lv_color_hex(0xE0E0E0), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_SensorImage, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_SensorImage, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_SensorImage, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_SensorImage, 1, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Image placeholder label
    lv_obj_t *imagePlaceholder = lv_label_create(ui_SensorImage);
    lv_label_set_text(imagePlaceholder, "Sensor Image");
    lv_obj_center(imagePlaceholder);
    lv_obj_set_style_text_color(imagePlaceholder, lv_color_hex(0x808080), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    // Add navigation buttons for wiki
    addNavButtonsToWidget(ui_SensorWidgetWiki, false);
    addControlButtonsToWidget(ui_SensorWidgetWiki);
    
    logMessage("\t>sensor wiki constructed!\n");
}

void SensorVisualizationGui::addNavButtonsToWidget(lv_obj_t *parentWidget, bool isVisualisation) {
    if (!parentWidget) return;
    
    // Previous button
    ui_btnPrev = lv_btn_create(parentWidget);
    lv_obj_set_width(ui_btnPrev, 80);
    lv_obj_set_height(ui_btnPrev, 40);
    lv_obj_set_x(ui_btnPrev, -320);
    lv_obj_set_y(ui_btnPrev, 170);
    lv_obj_set_align(ui_btnPrev, LV_ALIGN_CENTER);
    lv_obj_add_event_cb(ui_btnPrev, [](lv_event_t *e) {
        auto self = static_cast<SensorVisualizationGui*>(lv_event_get_user_data(e));
        self->goToPreviousSensor();
    }, LV_EVENT_CLICKED, this);
    
    ui_btnPrevLabel = lv_label_create(ui_btnPrev);
    lv_label_set_text(ui_btnPrevLabel, "Prev");
    lv_obj_center(ui_btnPrevLabel);
    lv_obj_set_style_text_font(ui_btnPrevLabel, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
    
    // Next button  
    ui_btnNext = lv_btn_create(parentWidget);
    lv_obj_set_width(ui_btnNext, 80);
    lv_obj_set_height(ui_btnNext, 40);
    lv_obj_set_x(ui_btnNext, -230);
    lv_obj_set_y(ui_btnNext, 170);
    lv_obj_set_align(ui_btnNext, LV_ALIGN_CENTER);
    lv_obj_add_event_cb(ui_btnNext, [](lv_event_t *e) {
        auto self = static_cast<SensorVisualizationGui*>(lv_event_get_user_data(e));
        self->goToNextSensor();
    }, LV_EVENT_CLICKED, this);
    
    ui_btnNextLabel = lv_label_create(ui_btnNext);
    lv_label_set_text(ui_btnNextLabel, "Next");
    lv_obj_center(ui_btnNextLabel);
    lv_obj_set_style_text_font(ui_btnNextLabel, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
    
    // Confirm button (for wiki mode)
    ui_btnConfirm = lv_btn_create(parentWidget);
    lv_obj_set_width(ui_btnConfirm, 80);
    lv_obj_set_height(ui_btnConfirm, 40);
    lv_obj_set_x(ui_btnConfirm, -140);
    lv_obj_set_y(ui_btnConfirm, 170);
    lv_obj_set_align(ui_btnConfirm, LV_ALIGN_CENTER);
    lv_obj_add_event_cb(ui_btnConfirm, [](lv_event_t *e) {
        auto self = static_cast<SensorVisualizationGui*>(lv_event_get_user_data(e));
        self->showVisualization(); // Switch to visualization when confirmed
    }, LV_EVENT_CLICKED, this);
    
    ui_btnConfirmLabel = lv_label_create(ui_btnConfirm);
    lv_label_set_text(ui_btnConfirmLabel, "OK");
    lv_obj_center(ui_btnConfirmLabel);
    lv_obj_set_style_text_font(ui_btnConfirmLabel, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
    
    logMessage("Navigation buttons added to widget\n");
}

void SensorVisualizationGui::addControlButtonsToWidget(lv_obj_t *parentWidget) {
    if (!parentWidget) return;
    
    // Sync button for refreshing sensor data
    ui_btnSync = lv_btn_create(parentWidget);
    lv_obj_set_width(ui_btnSync, 80);
    lv_obj_set_height(ui_btnSync, 40);
    lv_obj_set_x(ui_btnSync, 200);
    lv_obj_set_y(ui_btnSync, 170);
    lv_obj_set_align(ui_btnSync, LV_ALIGN_CENTER);
    lv_obj_add_event_cb(ui_btnSync, [](lv_event_t *e) {
        auto self = static_cast<SensorVisualizationGui*>(lv_event_get_user_data(e));
        self->syncCurrentSensor();
    }, LV_EVENT_CLICKED, this);
    
    ui_btnSyncLabel = lv_label_create(ui_btnSync);
    lv_label_set_text(ui_btnSyncLabel, "Sync");
    lv_obj_center(ui_btnSyncLabel);
    lv_obj_set_style_text_font(ui_btnSyncLabel, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
    
    // Back button for returning to menu
    ui_btnBack = lv_btn_create(parentWidget);
    lv_obj_set_width(ui_btnBack, 80);
    lv_obj_set_height(ui_btnBack, 40);
    lv_obj_set_x(ui_btnBack, 290);
    lv_obj_set_y(ui_btnBack, 170);
    lv_obj_set_align(ui_btnBack, LV_ALIGN_CENTER);
    lv_obj_add_event_cb(ui_btnBack, [](lv_event_t *e) {
        auto self = static_cast<SensorVisualizationGui*>(lv_event_get_user_data(e));
        logMessage("Back button pressed - returning to menu\n");
        switchToMenu();
    }, LV_EVENT_CLICKED, this);
    
    ui_btnBackLabel = lv_label_create(ui_btnBack);
    lv_label_set_text(ui_btnBackLabel, "Back");
    lv_obj_center(ui_btnBackLabel);
    lv_obj_set_style_text_font(ui_btnBackLabel, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
    
    logMessage("Control buttons added to widget\n");
}

void SensorVisualizationGui::drawCurrentSensor() {
    BaseSensor* currentSensor = getCurrentSensor();
    if (!currentSensor) {
        logMessage("No current sensor to draw\n");
        return;
    }
    
    logMessage("Drawing sensor: %s\n", currentSensor->UID.c_str());
    
    updateSensorDataDisplay();
    updateChart();
}

void SensorVisualizationGui::updateSensorDataDisplay() {
    BaseSensor* currentSensor = getCurrentSensor();
    if (!currentSensor) return;
    
    // Update sensor name
    if (ui_SensorLabel) {
        lv_label_set_text(ui_SensorLabel, currentSensor->UID.c_str());
    }
    
    // Update wiki labels too
    if (ui_SensorLabelWiki) {
        lv_label_set_text(ui_SensorLabelWiki, currentSensor->UID.c_str());
    }
    if (ui_SensorLabelDescription) {
        lv_label_set_text(ui_SensorLabelDescription, currentSensor->Description.c_str());
    }
    
    // Get all sensor values
    auto values = currentSensor->getValues();
    auto valueKeys = currentSensor->getValuesKeys();
    
    if (valueKeys.empty()) {
        logMessage("No values available for sensor: %s\n", currentSensor->UID.c_str());
        return;
    }
    
    // Update Value 1 (primary value)
    if (valueKeys.size() >= 1 && ui_LabelValueValue_1 && ui_LabelDescValue_1 && ui_LabelTypeValue_1) {
        const std::string& key1 = valueKeys[0];
        try {
            std::string value1 = currentSensor->getValue<std::string>(key1);
            std::string units1 = currentSensor->getValueUnits(key1);
            
            lv_label_set_text(ui_LabelValueValue_1, value1.c_str());
            lv_label_set_text(ui_LabelDescValue_1, units1.empty() ? "[units]" : ("[" + units1 + "]").c_str());
            lv_label_set_text(ui_LabelTypeValue_1, key1.c_str());
        }
        catch (const std::exception& e) {
            logMessage("Error updating value 1: %s\n", e.what());
        }
    }
    
    // Update Value 2 (secondary value, if available)
    if (valueKeys.size() >= 2 && ui_LabelValueValue_2 && ui_LabelDescValue_2 && ui_LabelTypeValue_2) {
        const std::string& key2 = valueKeys[1];
        try {
            std::string value2 = currentSensor->getValue<std::string>(key2);
            std::string units2 = currentSensor->getValueUnits(key2);
            
            lv_label_set_text(ui_LabelValueValue_2, value2.c_str());
            lv_label_set_text(ui_LabelDescValue_2, units2.empty() ? "[units]" : ("[" + units2 + "]").c_str());
            lv_label_set_text(ui_LabelTypeValue_2, key2.c_str());
            
            // Make second container visible
            if (ui_ContainerForValue_2) {
                lv_obj_clear_flag(ui_ContainerForValue_2, LV_OBJ_FLAG_HIDDEN);
            }
        }
        catch (const std::exception& e) {
            logMessage("Error updating value 2: %s\n", e.what());
        }
    } else {
        // Hide second value container if not needed
        if (ui_ContainerForValue_2) {
            lv_obj_add_flag(ui_ContainerForValue_2, LV_OBJ_FLAG_HIDDEN);
        }
    }
    
    logMessage("Updated sensor data display for: %s\n", currentSensor->UID.c_str());
}

void SensorVisualizationGui::updateChart() {
    BaseSensor* currentSensor = getCurrentSensor();
    if (!currentSensor || !ui_Chart || !ui_Chart_series_V1) return;
    
    // Get sensor value keys
    auto valueKeys = currentSensor->getValuesKeys();
    if (valueKeys.empty()) {
        logMessage("No values available for chart update: %s\n", currentSensor->UID.c_str());
        return;
    }
    
    // Use the first value for chart display
    const std::string& primaryKey = valueKeys[0];
    
    try {
        // Build sensor history for the primary value
        lv_coord_t history[HISTORY_CAP];
        
        // Try different data types based on sensor parameter type
        auto values = currentSensor->getValues();
        auto it = values.find(primaryKey);
        if (it == values.end()) {
            logMessage("Primary key not found in values: %s\n", primaryKey.c_str());
            return;
        }
        
        // Determine data type and build history accordingly
        SensorDataType dataType = it->second.DType;
        
        switch (dataType) {
            case SensorDataType::INT:
                buildSensorHistory<int>(currentSensor, primaryKey, history);
                break;
            case SensorDataType::FLOAT:
                buildSensorHistory<float>(currentSensor, primaryKey, history);
                break;
            case SensorDataType::DOUBLE:
                buildSensorHistory<double>(currentSensor, primaryKey, history);
                break;
            case SensorDataType::STRING:
                // For string values, try to convert to int first
                try {
                    buildSensorHistory<int>(currentSensor, primaryKey, history);
                } catch (...) {
                    // If int conversion fails, try float
                    try {
                        buildSensorHistory<float>(currentSensor, primaryKey, history);
                    } catch (...) {
                        logMessage("Cannot convert string values to numeric for chart: %s\n", primaryKey.c_str());
                        return;
                    }
                }
                break;
            default:
                logMessage("Unsupported data type for chart: %s\n", primaryKey.c_str());
                return;
        }
        
        // Clear existing chart data for both series
        lv_chart_set_all_value(ui_Chart, ui_Chart_series_V1, LV_CHART_POINT_NONE);
        lv_chart_set_all_value(ui_Chart, ui_Chart_series_V2, LV_CHART_POINT_NONE);
        
        // Add new data points to first series
        for (int i = 0; i < HISTORY_CAP; i++) {
            lv_chart_set_next_value(ui_Chart, ui_Chart_series_V1, history[i]);
        }
        
        // Handle second value if available
        if (valueKeys.size() >= 2 && ui_Chart_series_V2) {
            const std::string& secondaryKey = valueKeys[1];
            lv_coord_t history2[HISTORY_CAP];
            
            try {
                auto it2 = values.find(secondaryKey);
                if (it2 != values.end()) {
                    SensorDataType dataType2 = it2->second.DType;
                    
                    switch (dataType2) {
                        case SensorDataType::INT:
                            buildSensorHistory<int>(currentSensor, secondaryKey, history2);
                            break;
                        case SensorDataType::FLOAT:
                            buildSensorHistory<float>(currentSensor, secondaryKey, history2);
                            break;
                        case SensorDataType::DOUBLE:
                            buildSensorHistory<double>(currentSensor, secondaryKey, history2);
                            break;
                        case SensorDataType::STRING:
                            try {
                                buildSensorHistory<int>(currentSensor, secondaryKey, history2);
                            } catch (...) {
                                try {
                                    buildSensorHistory<float>(currentSensor, secondaryKey, history2);
                                } catch (...) {
                                    logMessage("Cannot convert secondary string values to numeric: %s\n", secondaryKey.c_str());
                                    goto skip_second_series;
                                }
                            }
                            break;
                        default:
                            goto skip_second_series;
                    }
                    
                    // Add second series data
                    for (int i = 0; i < HISTORY_CAP; i++) {
                        lv_chart_set_next_value(ui_Chart, ui_Chart_series_V2, history2[i]);
                    }
                    
                    logMessage("Updated chart with two series: %s, %s\n", primaryKey.c_str(), secondaryKey.c_str());
                }
                
                skip_second_series:;
                
            } catch (const std::exception& e) {
                logMessage("Error updating second chart series: %s\n", e.what());
            }
        }
        
        // Refresh chart display
        lv_chart_refresh(ui_Chart);
        
        logMessage("Updated chart for sensor: %s (primary key: %s)\n", currentSensor->UID.c_str(), primaryKey.c_str());
        
    } catch (const std::exception& e) {
        logMessage("Error updating chart: %s\n", e.what());
    }
}

void SensorVisualizationGui::goToPreviousSensor() {
    const auto& sensors = sensorManager.getSensors();
    
    if (sensors.empty()) {
        logMessage("No sensors available for navigation\n");
        return;
    }
    
    size_t newIndex = sensorManager.previousSensor();
    
    logMessage("Navigated to previous sensor (index: %zu)\n", newIndex);
    updateSensorDataDisplay();
    updateChart();
}

void SensorVisualizationGui::goToNextSensor() {
    const auto& sensors = sensorManager.getSensors();
    
    if (sensors.empty()) {
        logMessage("No sensors available for navigation\n");
        return;
    }
    
    size_t newIndex = sensorManager.nextSensor();
    
    logMessage("Navigated to next sensor (index: %zu)\n", newIndex);
    updateSensorDataDisplay();
    updateChart();
}

void SensorVisualizationGui::goToFirstSensor(bool showWikiTrigger) {
    size_t& currentIndex = sensorManager.getCurrentIndex();
    const auto& sensors = sensorManager.getSensors();
    
    if (sensors.empty()) {
        logMessage("No sensors available\n");
        return;
    }
    
    currentIndex = 0;
    logMessage("Navigated to first sensor\n");
    
    if (showWikiTrigger) {
        showWiki();
    } else {
        showVisualization();
    }
}

bool SensorVisualizationGui::syncCurrentSensor() {
    BaseSensor* currentSensor = getCurrentSensor();
    if (!currentSensor) {
        logMessage("No current sensor to sync\n");
        return false;
    }
    
    logMessage("Syncing sensor: %s\n", currentSensor->UID.c_str());
    
    bool success = sensorManager.sync(currentSensor->UID);
    if (success) {
        updateSensorDataDisplay(); // Refresh display with new data
        updateChart();
        logMessage("Sensor sync successful: %s\n", currentSensor->UID.c_str());
    } else {
        logMessage("Sensor sync failed: %s\n", currentSensor->UID.c_str());
    }
    
    return success;
}

void SensorVisualizationGui::showVisualization() {
    if (!initialized || !ui_SensorWidget) return;
    
    hideWiki(); // Hide wiki if it's showing
    lv_obj_clear_flag(ui_SensorWidget, LV_OBJ_FLAG_HIDDEN);
    
    // Refresh the display with current sensor data
    updateSensorDataDisplay();
    updateChart();
    
    logMessage("Showing sensor visualization\n");
}

void SensorVisualizationGui::hideVisualization() {
    if (!initialized || !ui_SensorWidget) return;
    
    lv_obj_add_flag(ui_SensorWidget, LV_OBJ_FLAG_HIDDEN);
    logMessage("Hiding sensor visualization\n");
}

void SensorVisualizationGui::showWiki() {
    if (!initialized || !ui_SensorWidgetWiki) return;
    
    hideVisualization(); // Hide visualization if it's showing
    lv_obj_clear_flag(ui_SensorWidgetWiki, LV_OBJ_FLAG_HIDDEN);
    
    // Refresh the wiki display with current sensor data
    updateSensorDataDisplay(); // This also updates wiki labels
    
    logMessage("Showing sensor wiki\n");
}

void SensorVisualizationGui::hideWiki() {
    if (!initialized || !ui_SensorWidgetWiki) return;
    
    lv_obj_add_flag(ui_SensorWidgetWiki, LV_OBJ_FLAG_HIDDEN);
    logMessage("Hiding sensor wiki\n");
}

BaseSensor* SensorVisualizationGui::getCurrentSensor() {
    return sensorManager.getCurrentSensor();
}