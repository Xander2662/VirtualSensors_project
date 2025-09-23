/**
 * @file main_menu.hpp
 * @brief Declaration of the manager_GUI widget
 *
 * This header defines the manager_GUI class which provides
 * a widget with a Start button and 6 pin selection buttons.
 *
 * @copyright 2025 MTA
 * @author Ondřej Wrubel
 */

#ifndef MAIN_MENU_HPP
#define MAIN_MENU_HPP

#include "lvgl.h"
#include <array>

class manager_GUI {
public:
    // DEFINITION
    //static manager_GUI& getInstance();

    // MENU GUI
    void showMenu();
    void hideMenu();
    //lv_obj_t* getMenuWidget() const { return ui_MenuWidget; }

private:
    // DEFINITION
    manager_GUI(); 
    ~manager_GUI() = default;

    manager_GUI(const manager_GUI&) = delete;
    manager_GUI& operator=(const manager_GUI&) = delete;

    // MENU GUI
    lv_obj_t* ui_MenuWidget;
    lv_obj_t* ui_btnStart;
    lv_obj_t* ui_ButtonStartLabel;
    std::array<lv_obj_t*, 6> pinContainers;
    std::array<lv_obj_t*, 6> pinLabels;

    //MENU EVENT GUI
    void startSensors();
    void pinToSelection(int index);
    void buildMenu();
    void updatePinLabelText();

    // SENSOR GUI
    lv_obj_t *ui_SensorWidget;
    lv_obj_t *ui_SensorLabel;
    // VALUE_1
    lv_obj_t *ui_ContainerForValue_1;
    lv_obj_t *ui_VisualColorForValue_1;
    lv_obj_t *ui_LabelValueValue_1;
    lv_obj_t *ui_LabelDescValue_1;
    lv_obj_t *ui_LabelTypeValue_1;
    // VALUE_2
    lv_obj_t *ui_VisualColorForValue_2;
    lv_obj_t *ui_ContainerForValue_2;
    lv_obj_t *ui_LabelValueValue_2;
    lv_obj_t *ui_LabelDescValue_2;
    lv_obj_t *ui_LabelTypeValue_2;
    // CHART
    lv_obj_t *ui_Chart;
    lv_chart_series_t *ui_Chart_series_V1;
    lv_chart_series_t *ui_Chart_series_V2;

    // WIKI
    lv_obj_t *ui_SensorLabelDescription;
    lv_obj_t *ui_SensorImage;

    //SENSOR EVENT GUI
    void hideAllExceptFirst(bool isVisualisation = true);
    void nextSensor(bool isVisualisation);
    void prevSensor(bool isVisualisation);
    void confirmSensor();
    void goBackToMenu();

    

};

#endif

