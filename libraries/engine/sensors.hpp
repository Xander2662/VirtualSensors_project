/**
 * @file sensors.hpp
 * @brief Declaration and implementation of sensor classes for sensor management using built-in exceptions.
 *
 * These sensors are derived from the BaseSensor class and provide specific implementations for ADC, Joystick, DHT11, LinearHallAndDigital, PhotoResistor, and LinearHall sensors.
 *
 * @copyright 2025 MTA
 * @author Ing. Jiri Konecny
 *
 */
#ifndef SENSORS_HPP
#define SENSORS_HPP
/*********************
 *      INCLUDES
 *********************/
#include "base_sensor.hpp" ///< BaseSensor class.

/**************************************************************************/
// SENSORS
/**************************************************************************/

/**
 * @class DHT11
 * @brief DHT11 sensor class derived from BaseSensor.
 *
 * Represents a DHT11 as a temperature and humidity sensor. Implements initialization, configuration,
 * updating, and printing specific to DHT11 sensors.
 */
class DHT11 : public BaseSensor
{
protected:
    lv_obj_t *ui_Widget;
    lv_obj_t *ui_Label;
    // TEMPERATURE
    lv_obj_t *ui_ContainerForTemperature;
    lv_obj_t *ui_VisualColorForTemperature;
    lv_obj_t *ui_LabelValueTemperature;
    lv_obj_t *ui_LabelDescTemperature;
    lv_obj_t *ui_LabelTypeTemperature;
    // HUMIDITY
    lv_obj_t *ui_VisualColorForHumidity;
    lv_obj_t *ui_ContainerForHumidity;
    lv_obj_t *ui_LabelValueHumidity;
    lv_obj_t *ui_LabelDescHumidity;
    lv_obj_t *ui_LabelTypeHumidity;
    // CHART
    lv_obj_t *ui_Chart;
    lv_chart_series_t *ui_Chart_series_T;
    lv_chart_series_t *ui_Chart_series_H;

    // WIKI
    lv_obj_t *ui_LabelDescription;
    lv_obj_t *ui_ImageSensor;

public:
    DHT11(std::string uid) : BaseSensor(uid) { init(); }
    virtual ~DHT11() {}

    virtual void init() override
    {
        Type = "DHT11";
        Description = "DHT11 Temperature & Humidity sensor";
        Error = nullptr;

        addConfigParameter("resolution", {"3", "digits", DataType::INT, 0});
        addValueParameter("Temperature", {"0", "°C", DataType::INT, 0});
        addValueParameter("Humidity", {"0", "%", DataType::INT, 0});
    }

    virtual void construct() override {}  
    /*virtual void constructWiki() override
    {
        // Container
        ui_Widget = lv_obj_create(lv_scr_act());
        lv_obj_remove_style_all(ui_Widget);
        lv_obj_set_width(ui_Widget, 760);
        lv_obj_set_height(ui_Widget, 440);
        lv_obj_set_align(ui_Widget, LV_ALIGN_CENTER);
        lv_obj_clear_flag(ui_Widget, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE |
                                         LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC |
                                         LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
        lv_obj_set_style_radius(ui_Widget, 15, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(ui_Widget, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_opa(ui_Widget, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_border_color(ui_Widget, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_border_opa(ui_Widget, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_border_width(ui_Widget, 2, LV_PART_MAIN | LV_STATE_DEFAULT);

        // Title
        ui_Label = lv_label_create(ui_Widget);
        lv_label_set_text(ui_Label, Type.c_str());
        lv_obj_set_width(ui_Label, LV_SIZE_CONTENT);
        lv_obj_set_height(ui_Label, LV_SIZE_CONTENT);
        lv_obj_set_x(ui_Label, 0);
        lv_obj_set_y(ui_Label, -185);
        lv_obj_set_align(ui_Label, LV_ALIGN_CENTER);
        lv_obj_clear_flag(ui_Label, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE |
                                        LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
                                        LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
        lv_obj_set_style_text_color(ui_Label, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_opa(ui_Label, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_font(ui_Label, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);

        ui_LabelDescription = lv_label_create(ui_Widget);
        lv_obj_set_width(ui_LabelDescription, LV_SIZE_CONTENT);  /// 1
        lv_obj_set_height(ui_LabelDescription, LV_SIZE_CONTENT); /// 1
        lv_obj_set_x(ui_LabelDescription, 25);
        lv_obj_set_y(ui_LabelDescription, 100);
        lv_label_set_text(ui_LabelDescription, Description.c_str());
        lv_obj_clear_flag(ui_LabelDescription,
                          LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE |
                              LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
                              LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
        lv_obj_set_style_text_color(ui_LabelDescription, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_opa(ui_LabelDescription, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

        addNavButtonsToWidget(ui_Widget, false);
        addConfirmButtonToWidget(ui_Widget);
        addBackButtonToWidget(ui_Widget);*/
    //}

    /*virtual void construct() override
    {
         // Container
         ui_Widget = lv_obj_create(lv_scr_act());
         lv_obj_remove_style_all(ui_Widget);
         lv_obj_set_width(ui_Widget, 760);
         lv_obj_set_height(ui_Widget, 440);
         lv_obj_set_align(ui_Widget, LV_ALIGN_CENTER);
         lv_obj_clear_flag(ui_Widget, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE |
                                          LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC |
                                          LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
         lv_obj_set_style_radius(ui_Widget, 15, LV_PART_MAIN | LV_STATE_DEFAULT);
         lv_obj_set_style_bg_color(ui_Widget, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
         lv_obj_set_style_bg_opa(ui_Widget, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
         lv_obj_set_style_border_color(ui_Widget, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
         lv_obj_set_style_border_opa(ui_Widget, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
         lv_obj_set_style_border_width(ui_Widget, 2, LV_PART_MAIN | LV_STATE_DEFAULT);

         // Title
         ui_Label = lv_label_create(ui_Widget);
         lv_label_set_text(ui_Label, Type.c_str());
         lv_obj_set_width(ui_Label, LV_SIZE_CONTENT);
         lv_obj_set_height(ui_Label, LV_SIZE_CONTENT);
         lv_obj_set_x(ui_Label, 0);
         lv_obj_set_y(ui_Label, -185);
         lv_obj_set_align(ui_Label, LV_ALIGN_CENTER);
         lv_obj_clear_flag(ui_Label, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE |
                                         LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
                                         LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
         lv_obj_set_style_text_color(ui_Label, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
         lv_obj_set_style_text_opa(ui_Label, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
         lv_obj_set_style_text_font(ui_Label, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);

         ui_ContainerForHumidity = lv_obj_create(ui_Widget);
         lv_obj_remove_style_all(ui_ContainerForHumidity);
         lv_obj_set_width(ui_ContainerForHumidity, 230);
         lv_obj_set_height(ui_ContainerForHumidity, 118);
         lv_obj_set_x(ui_ContainerForHumidity, -230);
         lv_obj_set_y(ui_ContainerForHumidity, 55);
         lv_obj_set_align(ui_ContainerForHumidity, LV_ALIGN_CENTER);
         lv_obj_clear_flag(ui_ContainerForHumidity,
                           LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE |
                               LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
                               LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
         lv_obj_set_style_radius(ui_ContainerForHumidity, 15, LV_PART_MAIN | LV_STATE_DEFAULT);
         lv_obj_set_style_bg_color(ui_ContainerForHumidity, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
         lv_obj_set_style_bg_opa(ui_ContainerForHumidity, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
         lv_obj_set_style_border_color(ui_ContainerForHumidity, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
         lv_obj_set_style_border_opa(ui_ContainerForHumidity, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
         lv_obj_set_style_border_width(ui_ContainerForHumidity, 2, LV_PART_MAIN | LV_STATE_DEFAULT);

         ui_VisualColorForHumidity = lv_obj_create(ui_ContainerForHumidity);
         lv_obj_remove_style_all(ui_VisualColorForHumidity);
         lv_obj_set_width(ui_VisualColorForHumidity, 20);
         lv_obj_set_height(ui_VisualColorForHumidity, 20);
         lv_obj_set_x(ui_VisualColorForHumidity, -10);
         lv_obj_set_y(ui_VisualColorForHumidity, 10);
         lv_obj_set_align(ui_VisualColorForHumidity, LV_ALIGN_TOP_RIGHT);
         lv_obj_clear_flag(ui_VisualColorForHumidity, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE); /// Flags
         lv_obj_set_style_radius(ui_VisualColorForHumidity, 1000, LV_PART_MAIN | LV_STATE_DEFAULT);
         lv_obj_set_style_bg_color(ui_VisualColorForHumidity, lv_color_hex(0x37F006), LV_PART_MAIN | LV_STATE_DEFAULT);
         lv_obj_set_style_bg_opa(ui_VisualColorForHumidity, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

         ui_LabelDescHumidity = lv_label_create(ui_ContainerForHumidity);
         lv_obj_set_width(ui_LabelDescHumidity, LV_SIZE_CONTENT);  /// 1
         lv_obj_set_height(ui_LabelDescHumidity, LV_SIZE_CONTENT); /// 1
         lv_obj_set_x(ui_LabelDescHumidity, 0);
         lv_obj_set_y(ui_LabelDescHumidity, 32);
         lv_obj_set_align(ui_LabelDescHumidity, LV_ALIGN_CENTER);
         lv_label_set_text(ui_LabelDescHumidity, "[%]");
         lv_obj_clear_flag(ui_LabelDescHumidity,
                           LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE |
                               LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
                               LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
         lv_obj_set_style_text_color(ui_LabelDescHumidity, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
         lv_obj_set_style_text_opa(ui_LabelDescHumidity, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
         lv_obj_set_style_text_font(ui_LabelDescHumidity, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);

         ui_LabelValueHumidity = lv_label_create(ui_ContainerForHumidity);
         lv_obj_set_width(ui_LabelValueHumidity, LV_SIZE_CONTENT);  /// 1
         lv_obj_set_height(ui_LabelValueHumidity, LV_SIZE_CONTENT); /// 1
         lv_obj_set_x(ui_LabelValueHumidity, 0);
         lv_obj_set_y(ui_LabelValueHumidity, 15);
         lv_obj_set_align(ui_LabelValueHumidity, LV_ALIGN_CENTER);
         lv_label_set_text(ui_LabelValueHumidity, "0");
         lv_obj_clear_flag(ui_LabelValueHumidity,
                           LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE |
                               LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
                               LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
         lv_obj_set_style_text_color(ui_LabelValueHumidity, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
         lv_obj_set_style_text_opa(ui_LabelValueHumidity, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
         lv_obj_set_style_text_font(ui_LabelValueHumidity, &lv_font_montserrat_40, LV_PART_MAIN | LV_STATE_DEFAULT);

         ui_LabelTypeHumidity = lv_label_create(ui_ContainerForHumidity);
         lv_obj_set_width(ui_LabelTypeHumidity, LV_SIZE_CONTENT);  /// 1
         lv_obj_set_height(ui_LabelTypeHumidity, LV_SIZE_CONTENT); /// 1
         lv_obj_set_x(ui_LabelTypeHumidity, 15);
         lv_obj_set_y(ui_LabelTypeHumidity, 10);
         lv_label_set_text(ui_LabelTypeHumidity, "Vlhkost");
         lv_obj_set_style_text_color(ui_LabelTypeHumidity, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
         lv_obj_set_style_text_opa(ui_LabelTypeHumidity, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

         ui_ContainerForTemperature = lv_obj_create(ui_Widget);
         lv_obj_remove_style_all(ui_ContainerForTemperature);
         lv_obj_set_width(ui_ContainerForTemperature, 230);
         lv_obj_set_height(ui_ContainerForTemperature, 118);
         lv_obj_set_x(ui_ContainerForTemperature, -230);
         lv_obj_set_y(ui_ContainerForTemperature, -85);
         lv_obj_set_align(ui_ContainerForTemperature, LV_ALIGN_CENTER);
         lv_obj_clear_flag(ui_ContainerForTemperature,
                           LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE |
                               LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
                               LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
         lv_obj_set_style_radius(ui_ContainerForTemperature, 15, LV_PART_MAIN | LV_STATE_DEFAULT);
         lv_obj_set_style_border_color(ui_ContainerForTemperature, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
         lv_obj_set_style_border_opa(ui_ContainerForTemperature, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
         lv_obj_set_style_border_width(ui_ContainerForTemperature, 2, LV_PART_MAIN | LV_STATE_DEFAULT);

         ui_VisualColorForTemperature = lv_obj_create(ui_ContainerForTemperature);
         lv_obj_remove_style_all(ui_VisualColorForTemperature);
         lv_obj_set_width(ui_VisualColorForTemperature, 20);
         lv_obj_set_height(ui_VisualColorForTemperature, 20);
         lv_obj_set_x(ui_VisualColorForTemperature, -10);
         lv_obj_set_y(ui_VisualColorForTemperature, 10);
         lv_obj_set_align(ui_VisualColorForTemperature, LV_ALIGN_TOP_RIGHT);
         lv_obj_clear_flag(ui_VisualColorForTemperature, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE); /// Flags
         lv_obj_set_style_radius(ui_VisualColorForTemperature, 1000, LV_PART_MAIN | LV_STATE_DEFAULT);
         lv_obj_set_style_bg_color(ui_VisualColorForTemperature, lv_color_hex(0x009BFF), LV_PART_MAIN | LV_STATE_DEFAULT);
         lv_obj_set_style_bg_opa(ui_VisualColorForTemperature, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

         ui_LabelValueTemperature = lv_label_create(ui_ContainerForTemperature);
         lv_obj_set_width(ui_LabelValueTemperature, LV_SIZE_CONTENT);  /// 1
         lv_obj_set_height(ui_LabelValueTemperature, LV_SIZE_CONTENT); /// 1
         lv_obj_set_x(ui_LabelValueTemperature, 0);
         lv_obj_set_y(ui_LabelValueTemperature, -5);
         lv_obj_set_align(ui_LabelValueTemperature, LV_ALIGN_CENTER);
         lv_label_set_text(ui_LabelValueTemperature, "0");
         lv_obj_clear_flag(ui_LabelValueTemperature,
                           LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE |
                               LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
                               LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
         lv_obj_set_style_text_color(ui_LabelValueTemperature, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
         lv_obj_set_style_text_opa(ui_LabelValueTemperature, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
         lv_obj_set_style_text_font(ui_LabelValueTemperature, &lv_font_montserrat_40, LV_PART_MAIN | LV_STATE_DEFAULT);

         ui_LabelDescTemperature = lv_label_create(ui_ContainerForTemperature);
         lv_obj_set_width(ui_LabelDescTemperature, LV_SIZE_CONTENT);  /// 1
         lv_obj_set_height(ui_LabelDescTemperature, LV_SIZE_CONTENT); /// 1
         lv_obj_set_x(ui_LabelDescTemperature, 0);
         lv_obj_set_y(ui_LabelDescTemperature, 30);
         lv_obj_set_align(ui_LabelDescTemperature, LV_ALIGN_CENTER);
         lv_label_set_text(ui_LabelDescTemperature, "[°C]");
         lv_obj_clear_flag(ui_LabelDescTemperature,
                           LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE |
                               LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
                               LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
         lv_obj_set_style_text_color(ui_LabelDescTemperature, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
         lv_obj_set_style_text_opa(ui_LabelDescTemperature, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
         lv_obj_set_style_text_font(ui_LabelDescTemperature, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);

         ui_LabelTypeTemperature = lv_label_create(ui_ContainerForTemperature);
         lv_obj_set_width(ui_LabelTypeTemperature, LV_SIZE_CONTENT);  /// 1
         lv_obj_set_height(ui_LabelTypeTemperature, LV_SIZE_CONTENT); /// 1
         lv_obj_set_x(ui_LabelTypeTemperature, 15);
         lv_obj_set_y(ui_LabelTypeTemperature, 10);
         lv_label_set_text(ui_LabelTypeTemperature, "Teplota");
         lv_obj_set_style_text_color(ui_LabelTypeTemperature, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
         lv_obj_set_style_text_opa(ui_LabelTypeTemperature, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

         // Navigation
         addNavButtonsToWidget(ui_Widget);
         addBackButtonToWidget(ui_Widget);

         // Chart
         ui_Chart = lv_chart_create(ui_Widget);
         lv_obj_set_width(ui_Chart, 410);
         lv_obj_set_height(ui_Chart, 280);
         lv_obj_set_x(ui_Chart, 150);
         lv_obj_set_y(ui_Chart, 20);
         lv_obj_set_align(ui_Chart, LV_ALIGN_CENTER);
         lv_obj_clear_flag(ui_Chart, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE |
                                         LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE); /// Flags
         lv_chart_set_type(ui_Chart, LV_CHART_TYPE_LINE);
         lv_chart_set_div_line_count(ui_Chart, 9, 10);
         lv_chart_set_axis_tick(ui_Chart, LV_CHART_AXIS_PRIMARY_X, 10, 0, 10, 1, true, 50);
         lv_chart_set_axis_tick(ui_Chart, LV_CHART_AXIS_PRIMARY_Y, 10, 5, 5, 2, true, 50);

         ui_Chart_series_T = lv_chart_add_series(ui_Chart, lv_color_hex(0x009BFF), LV_CHART_AXIS_PRIMARY_Y);
         ui_Chart_series_H = lv_chart_add_series(ui_Chart, lv_color_hex(0x37F006), LV_CHART_AXIS_PRIMARY_Y);
         static lv_coord_t bufT[HISTORY_CAP];
         static lv_coord_t bufH[HISTORY_CAP];
         lv_chart_set_ext_y_array(ui_Chart, ui_Chart_series_T, bufT);
         lv_chart_set_ext_y_array(ui_Chart, ui_Chart_series_H, bufH);
         lv_obj_set_style_bg_color(ui_Chart, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
         lv_obj_set_style_bg_opa(ui_Chart, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
         lv_obj_set_style_border_color(ui_Chart, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
         lv_obj_set_style_border_opa(ui_Chart, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
         lv_obj_set_style_border_width(ui_Chart, 2, LV_PART_MAIN | LV_STATE_DEFAULT);

         lv_obj_set_style_line_color(ui_Chart, lv_color_hex(0x000000), LV_PART_TICKS | LV_STATE_DEFAULT);
         lv_obj_set_style_line_opa(ui_Chart, 255, LV_PART_TICKS | LV_STATE_DEFAULT);
         lv_obj_set_style_text_color(ui_Chart, lv_color_hex(0x000000), LV_PART_TICKS | LV_STATE_DEFAULT);
         lv_obj_set_style_text_opa(ui_Chart, 255, LV_PART_TICKS | LV_STATE_DEFAULT);*/
    //}

    /*virtual void draw() override
    {
        if (!redrawPenging)
            return;
        std::string t = getValue<std::string>("Temperature");
        std::string h = getValue<std::string>("Humidity");
        lv_label_set_text(ui_LabelValueTemperature, t.c_str());
        lv_label_set_text(ui_LabelValueHumidity, h.c_str());

        static lv_coord_t histT[HISTORY_CAP];
        static lv_coord_t histH[HISTORY_CAP];
        getHistory<float>("Temperature", histT);
        getHistory<float>("Humidity", histH);
        lv_chart_set_ext_y_array(ui_Chart, ui_Chart_series_T, histT);
        lv_chart_set_ext_y_array(ui_Chart, ui_Chart_series_H, histH);
        redrawPenging = false;*/
    //}

    // void show() override { lv_obj_clear_flag(ui_Widget, LV_OBJ_FLAG_HIDDEN); }
    // void hide() override { lv_obj_add_flag(ui_Widget, LV_OBJ_FLAG_HIDDEN); }
};

/**************************************************************************/

/**
 * @class PhotoResistor
 * @brief PhotoResistor sensor class derived from BaseSensor.
 *
 * Represents a PhotoResistor which measures lux in users environment. Implements initialization, configuration,
 * updating, and printing specific to PhotoResistor sensors.
 */
class PhotoResistor : public BaseSensor
{
protected:
    lv_obj_t *ui_Widget;
    lv_obj_t *ui_Label;
    // VALUE
    lv_obj_t *ui_ContainerForSingleValue;
    lv_obj_t *ui_VisualColorForSingleValue;
    lv_obj_t *ui_Value_Lux;
    lv_obj_t *ui_LabelSingleValueDesc;
    // CHART
    lv_obj_t *ui_Chart;
    lv_chart_series_t *ui_Chart_series_1;
    // WIKI
    lv_obj_t *ui_LabelDescription;
    lv_obj_t *ui_ImageSensor;

public:
    /**
     * @brief Constructs a new PhotoResistor object.
     *
     * Initializes default values and sets the sensor type and description.
     *
     * @param uid The unique sensor identifier.
     */
    PhotoResistor(std::string uid) : BaseSensor(uid)
    {
        init();
    }

    /**
     * @brief Virtual destructor.
     */
    virtual ~PhotoResistor() {}
    /**
     * @brief Initializes the sensor.
     *
     * Additional initialization code can be added here.
     *
     * @throws Exception if initialization fails.
     */
    virtual void init() override
    {
        // Additional initialization for sensor can be added here.
        Type = "PhotoResistor";
        Description = "Returns Lux of a measured environment, which users is in";
        Error = nullptr;

        try
        {
            // Default configs
            addConfigParameter("resolution", {"5", "digits", DataType::INT, 0});
            // Default values
            addValueParameter("Lux", {"0", "Lux", DataType::INT, 0});
        }
        catch (const std::exception &e)
        {
            throw;
        }
    }

    virtual void construct() override {}  
    /**
     * @brief Draw sensor.
     *
     * This function draws the sensor.
     */
    /*virtual void draw() override
    {
        if (!redrawPenging)
        {
            return;
        }

        std::string t = getValue<std::string>("Lux");
        lv_label_set_text(ui_Value_Lux, t.c_str());

        static lv_coord_t history[HISTORY_CAP];
        getHistory<float>("Lux", history);

        lv_coord_t min_val = history[0];
        lv_coord_t max_val = history[0];
        long sum = 0;
        for (int i = 0; i < HISTORY_CAP; i++)
        {
            lv_coord_t v = history[i];
            if (v < min_val)
                min_val = v;
            if (v > max_val)
                max_val = v;
            sum += v;
        }
        float avg = (float)sum / HISTORY_CAP;

        lv_coord_t delta = max_val - min_val;
        lv_coord_t y_min = min_val;
        lv_coord_t y_max = max_val + delta / 10 + 100;
        y_max = y_max - y_max % 100;

        lv_chart_set_ext_y_array(ui_Chart, ui_Chart_series_1, history);
        lv_chart_set_range(ui_Chart, LV_CHART_AXIS_PRIMARY_Y, 0, y_max);
        lv_chart_refresh(ui_Chart);

        redrawPenging = false; // Reset flag to redraw sensor.
    }*/

    /*virtual void constructWiki() override
    {
        // Container
        ui_Widget = lv_obj_create(lv_scr_act());
        lv_obj_remove_style_all(ui_Widget);
        lv_obj_set_width(ui_Widget, 760);
        lv_obj_set_height(ui_Widget, 440);
        lv_obj_set_align(ui_Widget, LV_ALIGN_CENTER);
        lv_obj_clear_flag(ui_Widget, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE |
                                         LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC |
                                         LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
        lv_obj_set_style_radius(ui_Widget, 15, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(ui_Widget, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_opa(ui_Widget, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_border_color(ui_Widget, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_border_opa(ui_Widget, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_border_width(ui_Widget, 2, LV_PART_MAIN | LV_STATE_DEFAULT);

        // Title
        ui_Label = lv_label_create(ui_Widget);
        lv_label_set_text(ui_Label, Type.c_str());
        lv_obj_set_width(ui_Label, LV_SIZE_CONTENT);
        lv_obj_set_height(ui_Label, LV_SIZE_CONTENT);
        lv_obj_set_x(ui_Label, 0);
        lv_obj_set_y(ui_Label, -185);
        lv_obj_set_align(ui_Label, LV_ALIGN_CENTER);
        lv_obj_clear_flag(ui_Label, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE |
                                        LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
                                        LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
        lv_obj_set_style_text_color(ui_Label, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_opa(ui_Label, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_font(ui_Label, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);

        ui_LabelDescription = lv_label_create(ui_Widget);
        lv_obj_set_width(ui_LabelDescription, LV_SIZE_CONTENT);  /// 1
        lv_obj_set_height(ui_LabelDescription, LV_SIZE_CONTENT); /// 1
        lv_obj_set_x(ui_LabelDescription, 25);
        lv_obj_set_y(ui_LabelDescription, 100);
        lv_label_set_text(ui_LabelDescription, Description.c_str());
        lv_obj_clear_flag(ui_LabelDescription,
                          LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE |
                              LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
                              LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
        lv_obj_set_style_text_color(ui_LabelDescription, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_opa(ui_LabelDescription, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

        addNavButtonsToWidget(ui_Widget, false);
        addConfirmButtonToWidget(ui_Widget);
        addBackButtonToWidget(ui_Widget);
    }*/

    /**
     * @brief Construct UI elements.
     *
     * This function constructs the sensor-specific GUI.
     */
    /*virtual void construct() override
    {
        // Construct sensor UI

        ui_Widget = lv_obj_create(lv_scr_act());
        lv_obj_remove_style_all(ui_Widget);
        lv_obj_set_width(ui_Widget, 760);
        lv_obj_set_height(ui_Widget, 440);
        lv_obj_set_align(ui_Widget, LV_ALIGN_CENTER);
        lv_obj_clear_flag(ui_Widget, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE |
                                         LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC |
                                         LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
        lv_obj_set_style_radius(ui_Widget, 15, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(ui_Widget, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_opa(ui_Widget, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_border_color(ui_Widget, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_border_opa(ui_Widget, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_border_width(ui_Widget, 2, LV_PART_MAIN | LV_STATE_DEFAULT);

        ui_Label = lv_label_create(ui_Widget);
        lv_obj_set_width(ui_Label, LV_SIZE_CONTENT);  /// 1
        lv_obj_set_height(ui_Label, LV_SIZE_CONTENT); /// 1
        lv_obj_set_x(ui_Label, 0);
        lv_obj_set_y(ui_Label, -185);
        lv_obj_set_align(ui_Label, LV_ALIGN_CENTER);
        lv_label_set_text(ui_Label, Type.c_str());
        lv_obj_clear_flag(ui_Label, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE |
                                        LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
                                        LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
        lv_obj_set_style_text_color(ui_Label, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_opa(ui_Label, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_font(ui_Label, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);

        ui_ContainerForSingleValue = lv_obj_create(ui_Widget);
        lv_obj_remove_style_all(ui_ContainerForSingleValue);
        lv_obj_set_width(ui_ContainerForSingleValue, 230);
        lv_obj_set_height(ui_ContainerForSingleValue, 118);
        lv_obj_set_x(ui_ContainerForSingleValue, -230);
        lv_obj_set_y(ui_ContainerForSingleValue, 55);
        lv_obj_set_align(ui_ContainerForSingleValue, LV_ALIGN_CENTER);
        lv_obj_clear_flag(ui_ContainerForSingleValue,
                          LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE |
                              LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
                              LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
        lv_obj_set_style_radius(ui_ContainerForSingleValue, 15, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(ui_ContainerForSingleValue, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_opa(ui_ContainerForSingleValue, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_border_color(ui_ContainerForSingleValue, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_border_opa(ui_ContainerForSingleValue, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_border_width(ui_ContainerForSingleValue, 2, LV_PART_MAIN | LV_STATE_DEFAULT);

        ui_VisualColorForSingleValue = lv_obj_create(ui_ContainerForSingleValue);
        lv_obj_remove_style_all(ui_VisualColorForSingleValue);
        lv_obj_set_width(ui_VisualColorForSingleValue, 20);
        lv_obj_set_height(ui_VisualColorForSingleValue, 20);
        lv_obj_set_x(ui_VisualColorForSingleValue, -10);
        lv_obj_set_y(ui_VisualColorForSingleValue, 10);
        lv_obj_set_align(ui_VisualColorForSingleValue, LV_ALIGN_TOP_RIGHT);
        lv_obj_clear_flag(ui_VisualColorForSingleValue, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE); /// Flags
        lv_obj_set_style_radius(ui_VisualColorForSingleValue, 1000, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(ui_VisualColorForSingleValue, lv_color_hex(0xFFAF00), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_opa(ui_VisualColorForSingleValue, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

        ui_Value_Lux = lv_label_create(ui_ContainerForSingleValue);
        lv_obj_set_width(ui_Value_Lux, LV_SIZE_CONTENT);  /// 1
        lv_obj_set_height(ui_Value_Lux, LV_SIZE_CONTENT); /// 1
        lv_obj_set_x(ui_Value_Lux, 0);
        lv_obj_set_y(ui_Value_Lux, -5);
        lv_obj_set_align(ui_Value_Lux, LV_ALIGN_CENTER);
        lv_label_set_text(ui_Value_Lux, "0");
        lv_obj_clear_flag(ui_Value_Lux,
                          LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE |
                              LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
                              LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
        lv_obj_set_style_text_color(ui_Value_Lux, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_opa(ui_Value_Lux, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_font(ui_Value_Lux, &lv_font_montserrat_40, LV_PART_MAIN | LV_STATE_DEFAULT);

        ui_LabelSingleValueDesc = lv_label_create(ui_ContainerForSingleValue);
        lv_obj_set_width(ui_LabelSingleValueDesc, LV_SIZE_CONTENT);  /// 1
        lv_obj_set_height(ui_LabelSingleValueDesc, LV_SIZE_CONTENT); /// 1
        lv_obj_set_x(ui_LabelSingleValueDesc, 0);
        lv_obj_set_y(ui_LabelSingleValueDesc, 30);
        lv_obj_set_align(ui_LabelSingleValueDesc, LV_ALIGN_CENTER);
        lv_label_set_text(ui_LabelSingleValueDesc, "[Lux]");
        lv_obj_clear_flag(ui_LabelSingleValueDesc,
                          LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE |
                              LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
                              LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
        lv_obj_set_style_text_color(ui_LabelSingleValueDesc, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_opa(ui_LabelSingleValueDesc, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_font(ui_LabelSingleValueDesc, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);

        addNavButtonsToWidget(ui_Widget);
        addBackButtonToWidget(ui_Widget);

        ui_Chart = lv_chart_create(ui_Widget);
        lv_obj_set_width(ui_Chart, 410);
        lv_obj_set_height(ui_Chart, 280);
        lv_obj_set_x(ui_Chart, 150);
        lv_obj_set_y(ui_Chart, 20);
        lv_obj_set_align(ui_Chart, LV_ALIGN_CENTER);
        lv_obj_clear_flag(ui_Chart, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE |
                                        LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE); /// Flags
        lv_chart_set_type(ui_Chart, LV_CHART_TYPE_LINE);
        lv_chart_set_div_line_count(ui_Chart, 9, 10);
        lv_chart_set_axis_tick(ui_Chart, LV_CHART_AXIS_PRIMARY_X, 10, 0, 10, 1, true, 50);
        lv_chart_set_axis_tick(ui_Chart, LV_CHART_AXIS_PRIMARY_Y, 10, 5, 5, 2, true, 50);

        ui_Chart_series_1 = lv_chart_add_series(ui_Chart, lv_color_hex(0xFFAF00),
                                                LV_CHART_AXIS_PRIMARY_Y);
        lv_coord_t ui_Chart_series_Lux[HISTORY_CAP];
        lv_chart_set_ext_y_array(ui_Chart, ui_Chart_series_1, ui_Chart_series_Lux);
        lv_obj_set_style_bg_color(ui_Chart, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_opa(ui_Chart, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_border_color(ui_Chart, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_border_opa(ui_Chart, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_border_width(ui_Chart, 2, LV_PART_MAIN | LV_STATE_DEFAULT);

        lv_obj_set_style_line_color(ui_Chart, lv_color_hex(0x000000), LV_PART_TICKS | LV_STATE_DEFAULT);
        lv_obj_set_style_line_opa(ui_Chart, 255, LV_PART_TICKS | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(ui_Chart, lv_color_hex(0x000000), LV_PART_TICKS | LV_STATE_DEFAULT);
        lv_obj_set_style_text_opa(ui_Chart, 255, LV_PART_TICKS | LV_STATE_DEFAULT);
    }

    //void show() override { lv_obj_clear_flag(ui_Widget, LV_OBJ_FLAG_HIDDEN); }
    //void hide() override { lv_obj_add_flag(ui_Widget, LV_OBJ_FLAG_HIDDEN); }*/
};

/**************************************************************************/

/**
 * @class LinearHall
 * @brief LinearHall sensor class derived from BaseSensor.
 *
 * Represents a Linear Hall sensor, which returns strenght of a magnet in gauss. Implements initialization, configuration,
 * updating, and printing specific to LinearHall sensors.
 */
class LinearHall : public BaseSensor
{
protected:
    lv_obj_t *ui_Widget;
    lv_obj_t *ui_Label;
    // VALUE
    lv_obj_t *ui_ContainerForSingleValue;
    lv_obj_t *ui_VisualColorForSingleValue;
    lv_obj_t *ui_Value_MT;
    lv_obj_t *ui_LabelSingleValueDesc;
    // CHART
    lv_obj_t *ui_Chart;
    lv_chart_series_t *ui_Chart_series_1;

public:
    /**
     * @brief Constructs a new LinearHall object.
     *
     * Initializes default values and sets the sensor type and description.
     *
     * @param uid The unique sensor identifier.
     */
    LinearHall(std::string uid) : BaseSensor(uid)
    {
        init();
    }

    /**
     * @brief Virtual destructor.
     */
    virtual ~LinearHall() {}

    /**
     * @brief Initializes the sensor.
     *
     * Additional initialization code can be added here.
     *
     * @throws Exception if initialization fails.
     */
    virtual void init() override
    {
        // Additional initialization for sensor can be added here.
        Type = "LinearHall";
        Description = "Returns milliTesla of a measured magnet";
        Error = nullptr;

        try
        {
            // Default configs
            addConfigParameter("precision", {"2", "decimals", DataType::INT, 0});
            // Default values
            addValueParameter("milliTesla", {"0", "milliTesla", DataType::FLOAT, 0});
        }
        catch (const std::exception &e)
        {
            throw;
        }
    }

    virtual void construct() override {}  
    /**
     * @brief Draw sensor.
     *
     * This function draws the sensor.
     */
    /*virtual void draw() override
    {
        if (!redrawPenging)
        {
            return;
        }

        // Draw sensor

        // Call draw function here
        std::string t = getValue<std::string>("milliTesla");
        lv_label_set_text(ui_Value_MT, t.c_str());

        static lv_coord_t ui_Chart_series_milliTesla[HISTORY_CAP];
        getHistory<float>("milliTesla", ui_Chart_series_milliTesla);
        lv_chart_set_ext_y_array(ui_Chart, ui_Chart_series_1, ui_Chart_series_milliTesla);

        redrawPenging = false; // Reset flag to redraw sensor.
    }*/
    /**
     * @brief Construct UI elements.
     *
     * This function constructs the sensor-specific GUI.
     */
    /*virtual void construct() override
    {
        // Construct sensor UI

        ui_Widget = lv_obj_create(lv_scr_act());
        lv_obj_remove_style_all(ui_Widget);
        lv_obj_set_width(ui_Widget, 760);
        lv_obj_set_height(ui_Widget, 440);
        lv_obj_set_align(ui_Widget, LV_ALIGN_CENTER);
        lv_obj_clear_flag(ui_Widget, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE |
                                         LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC |
                                         LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
        lv_obj_set_style_radius(ui_Widget, 15, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(ui_Widget, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_opa(ui_Widget, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_border_color(ui_Widget, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_border_opa(ui_Widget, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_border_width(ui_Widget, 2, LV_PART_MAIN | LV_STATE_DEFAULT);

        ui_Label = lv_label_create(ui_Widget);
        lv_label_set_text(ui_Label, Type.c_str());
        lv_obj_set_width(ui_Label, LV_SIZE_CONTENT);  /// 1
        lv_obj_set_height(ui_Label, LV_SIZE_CONTENT); /// 1
        lv_obj_set_x(ui_Label, 0);
        lv_obj_set_y(ui_Label, -185);
        lv_obj_set_align(ui_Label, LV_ALIGN_CENTER);
        lv_obj_clear_flag(ui_Label, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE |
                                        LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
                                        LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
        lv_obj_set_style_text_color(ui_Label, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_opa(ui_Label, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_font(ui_Label, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);

        ui_ContainerForSingleValue = lv_obj_create(ui_Widget);
        lv_obj_remove_style_all(ui_ContainerForSingleValue);
        lv_obj_set_width(ui_ContainerForSingleValue, 230);
        lv_obj_set_height(ui_ContainerForSingleValue, 118);
        lv_obj_set_x(ui_ContainerForSingleValue, -230);
        lv_obj_set_y(ui_ContainerForSingleValue, 55);
        lv_obj_set_align(ui_ContainerForSingleValue, LV_ALIGN_CENTER);
        lv_obj_clear_flag(ui_ContainerForSingleValue,
                          LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE |
                              LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
                              LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
        lv_obj_set_style_radius(ui_ContainerForSingleValue, 15, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(ui_ContainerForSingleValue, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_opa(ui_ContainerForSingleValue, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_border_color(ui_ContainerForSingleValue, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_border_opa(ui_ContainerForSingleValue, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_border_width(ui_ContainerForSingleValue, 2, LV_PART_MAIN | LV_STATE_DEFAULT);

        ui_VisualColorForSingleValue = lv_obj_create(ui_ContainerForSingleValue);
        lv_obj_remove_style_all(ui_VisualColorForSingleValue);
        lv_obj_set_width(ui_VisualColorForSingleValue, 20);
        lv_obj_set_height(ui_VisualColorForSingleValue, 20);
        lv_obj_set_x(ui_VisualColorForSingleValue, -10);
        lv_obj_set_y(ui_VisualColorForSingleValue, 10);
        lv_obj_set_align(ui_VisualColorForSingleValue, LV_ALIGN_TOP_RIGHT);
        lv_obj_clear_flag(ui_VisualColorForSingleValue, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE); /// Flags
        lv_obj_set_style_radius(ui_VisualColorForSingleValue, 1000, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(ui_VisualColorForSingleValue, lv_color_hex(0xFFAF00), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_opa(ui_VisualColorForSingleValue, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

        ui_Value_MT = lv_label_create(ui_ContainerForSingleValue);
        lv_obj_set_width(ui_Value_MT, LV_SIZE_CONTENT);  /// 1
        lv_obj_set_height(ui_Value_MT, LV_SIZE_CONTENT); /// 1
        lv_obj_set_x(ui_Value_MT, 0);
        lv_obj_set_y(ui_Value_MT, -5);
        lv_obj_set_align(ui_Value_MT, LV_ALIGN_CENTER);
        lv_label_set_text(ui_Value_MT, "0");
        lv_obj_clear_flag(ui_Value_MT,
                          LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE |
                              LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
                              LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
        lv_obj_set_style_text_color(ui_Value_MT, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_opa(ui_Value_MT, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_font(ui_Value_MT, &lv_font_montserrat_40, LV_PART_MAIN | LV_STATE_DEFAULT);

        ui_LabelSingleValueDesc = lv_label_create(ui_ContainerForSingleValue);
        lv_obj_set_width(ui_LabelSingleValueDesc, LV_SIZE_CONTENT);  /// 1
        lv_obj_set_height(ui_LabelSingleValueDesc, LV_SIZE_CONTENT); /// 1
        lv_obj_set_x(ui_LabelSingleValueDesc, 0);
        lv_obj_set_y(ui_LabelSingleValueDesc, 30);
        lv_obj_set_align(ui_LabelSingleValueDesc, LV_ALIGN_CENTER);
        lv_label_set_text(ui_LabelSingleValueDesc, "[mT]");
        lv_obj_clear_flag(ui_LabelSingleValueDesc,
                          LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE |
                              LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
                              LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
        lv_obj_set_style_text_color(ui_LabelSingleValueDesc, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_opa(ui_LabelSingleValueDesc, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_font(ui_LabelSingleValueDesc, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);

        addNavButtonsToWidget(ui_Widget);

        ui_Chart = lv_chart_create(ui_Widget);
        lv_obj_set_width(ui_Chart, 410);
        lv_obj_set_height(ui_Chart, 280);
        lv_obj_set_x(ui_Chart, 150);
        lv_obj_set_y(ui_Chart, 20);
        lv_obj_set_align(ui_Chart, LV_ALIGN_CENTER);
        lv_obj_clear_flag(ui_Chart, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE |
                                        LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE); /// Flags
        lv_chart_set_type(ui_Chart, LV_CHART_TYPE_LINE);
        lv_chart_set_div_line_count(ui_Chart, 9, 10);
        lv_chart_set_axis_tick(ui_Chart, LV_CHART_AXIS_PRIMARY_X, 10, 0, 10, 1, true, 50);
        lv_chart_set_axis_tick(ui_Chart, LV_CHART_AXIS_PRIMARY_Y, 10, 5, 5, 2, true, 50);
        lv_chart_set_range(ui_Chart, LV_CHART_AXIS_PRIMARY_Y, -100, 100);
        ui_Chart_series_1 = lv_chart_add_series(ui_Chart, lv_color_hex(0xFFAF00), LV_CHART_AXIS_PRIMARY_Y);
        lv_coord_t ui_Chart_series_milliTesla[HISTORY_CAP];
        lv_chart_set_ext_y_array(ui_Chart, ui_Chart_series_1, ui_Chart_series_milliTesla);
        lv_obj_set_style_bg_color(ui_Chart, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_opa(ui_Chart, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_border_color(ui_Chart, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_border_opa(ui_Chart, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_border_width(ui_Chart, 2, LV_PART_MAIN | LV_STATE_DEFAULT);

        lv_obj_set_style_line_color(ui_Chart, lv_color_hex(0x000000), LV_PART_TICKS | LV_STATE_DEFAULT);
        lv_obj_set_style_line_opa(ui_Chart, 255, LV_PART_TICKS | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(ui_Chart, lv_color_hex(0x000000), LV_PART_TICKS | LV_STATE_DEFAULT);
        lv_obj_set_style_text_opa(ui_Chart, 255, LV_PART_TICKS | LV_STATE_DEFAULT);
    }

    //void show() override { lv_obj_clear_flag(ui_Widget, LV_OBJ_FLAG_HIDDEN); }
    //void hide() override { lv_obj_add_flag(ui_Widget, LV_OBJ_FLAG_HIDDEN); }*/
};

/**************************************************************************/
#endif // SENSORS_HPP