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
class manager_GUI
{
public:
    // DEFINITION
    static manager_GUI &getInstance();

    // MENU GUI
    void showMenu();
    void hideMenu();
    void updatePinLabelText();
    // lv_obj_t* getMenuWidget() const { return ui_MenuWidget; }

    // SENSOR GUI
    void drawCurrentSensor();
    void construct();
    void constructWiki();
    void goToFirstSensor(bool isVisualisation);

    void showSensorWiki();
    void hideSensorWiki();
    void showSensorVisualisation();
    void hideSensorVisualisation();

    /*void resetMenu()
    {
        lv_obj_del(ui_MenuWidget);
        ui_MenuWidget = nullptr;
    }*/

    /*void resetWidgetVis()
    {
        if (ui_SensorWidget && lv_obj_is_valid(ui_SensorWidget))
        {
            lv_obj_del(ui_SensorWidget);
        }
        ui_SensorWidget = nullptr;
        ui_SensorLabel = nullptr;
        ui_ContainerForValue_1 = nullptr;
        ui_VisualColorForValue_1 = nullptr;
        ui_LabelValueValue_1 = nullptr;
        ui_LabelDescValue_1 = nullptr;
        ui_LabelTypeValue_1 = nullptr;
        ui_Chart = nullptr;
        ui_Chart_series_V1 = nullptr;
    }

    void resetWidgetWiki()
    {
        if (ui_SensorWidgetWiki && lv_obj_is_valid(ui_SensorWidgetWiki))
        {
            lv_obj_del(ui_SensorWidgetWiki);
        }
        ui_SensorWidgetWiki = nullptr;
        ui_SensorLabel = nullptr; // careful: used in both wiki/vis
        ui_SensorLabelDescription = nullptr;
        ui_SensorImage = nullptr;
    }*/

private:
    // DEFINITION
    manager_GUI();
    ~manager_GUI() = default;

    manager_GUI(const manager_GUI &) = delete;
    manager_GUI &operator=(const manager_GUI &) = delete;

    // MENU GUI
    lv_obj_t *ui_MenuWidget;
    lv_obj_t *ui_btnStart;
    lv_obj_t *ui_ButtonStartLabel;
    std::array<lv_obj_t *, 6> pinContainers;
    std::array<lv_obj_t *, 6> pinLabels;

    // MENU EVENT GUI
    // static void startSensors();
    // static void pinToSelection(int index);
    void buildMenu();

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
    // this is something different as ui_Chart_series_1
    lv_chart_series_t *ui_Chart_series_V1;
    // lv_chart_series_t *ui_Chart_series_V2;

    // WIKI
    lv_obj_t *ui_SensorWidgetWiki;
    lv_obj_t *ui_SensorLabelWiki;
    lv_obj_t *ui_SensorLabelDescription;
    lv_obj_t *ui_SensorImage;

    // SENSOR EVENT GUI
    // void hideAllExceptFirst(bool isVisualisation = true);
    // void nextSensor(bool isVisualisation);
    // void prevSensor(bool isVisualisation);
    // void confirmSensor();
    // void goBackToMenu();
    lv_obj_t *ui_btnPrev;
    lv_obj_t *ui_btnPrevLabel;
    lv_obj_t *ui_btnNext;
    lv_obj_t *ui_btnNextLabel;
    lv_obj_t *ui_btnConfirm;
    lv_obj_t *ui_btnConfirmLabel;

    void addNavButtonsToWidget(lv_obj_t *parentWidget, bool isVisualisation = true);
    void addConfirmButtonToWidget(lv_obj_t *parentWidget);
    void addBackButtonToWidget(lv_obj_t *parentWidget);
};

#endif
