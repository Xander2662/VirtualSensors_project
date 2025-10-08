/**
 * @file main_menu.cpp
 * @brief Definition of the manager_GUI widget
 *
 * This source defines the manager_GUI widget with a Start button
 * and 6 pin containers for sensor assignment.
 *
 * @copyright 2025
 * @author Ondřej Wrubel
 */
#include <iostream> // for debug logs

#include "manager_GUI.hpp"
#include "manager.hpp"
#include "base_sensor.hpp"

/*********************
 *      DENITION
 *********************/

manager_GUI &manager_GUI::getInstance()
{
    static manager_GUI instance;
    return instance;
}

manager_GUI::manager_GUI()
    : ui_MenuWidget(nullptr), ui_btnStart(nullptr), ui_ButtonStartLabel(nullptr)
{
    buildMenu();
    hideMenu(); // start hidden
}

// inicialization of static lvgl objects declared in manager_GUI.hpp
/*lv_obj_t* manager_GUI::ui_SensorWidget = nullptr;
lv_obj_t* manager_GUI::ui_SensorLabel = nullptr;
lv_obj_t* manager_GUI::ui_ContainerForValue_1 = nullptr;
lv_obj_t* manager_GUI::ui_VisualColorForValue_1 = nullptr;
lv_obj_t* manager_GUI::ui_LabelValueValue_1 = nullptr;
lv_obj_t* manager_GUI::ui_LabelDescValue_1 = nullptr;
lv_obj_t* manager_GUI::ui_LabelTypeValue_1 = nullptr;
lv_obj_t* manager_GUI::ui_Chart = nullptr;
lv_chart_series_t* manager_GUI::ui_Chart_series_V1 = nullptr;

lv_obj_t* manager_GUI::ui_SensorWidgetWiki = nullptr;
lv_obj_t* manager_GUI::ui_SensorLabelDescription = nullptr;
lv_obj_t* manager_GUI::ui_SensorImage = nullptr;

lv_obj_t* manager_GUI::ui_btnPrev = nullptr;
lv_obj_t* manager_GUI::ui_btnPrevLabel = nullptr;
lv_obj_t* manager_GUI::ui_btnNext = nullptr;
lv_obj_t* manager_GUI::ui_btnNextLabel = nullptr;
lv_obj_t* manager_GUI::ui_btnConfirm = nullptr;
lv_obj_t* manager_GUI::ui_btnConfirmLabel = nullptr;*/

/*********************
 *      MENU GUI
 *********************/

// buildMenu should be used instead
void manager_GUI::showMenu()
{
    if (ui_MenuWidget)
        lv_obj_clear_flag(ui_MenuWidget, LV_OBJ_FLAG_HIDDEN);
}

// emptyMenu should be used instead
void manager_GUI::hideMenu()
{
    if (ui_MenuWidget)
        lv_obj_add_flag(ui_MenuWidget, LV_OBJ_FLAG_HIDDEN);
    // lv_obj_del(ui_MenuWidget);
}

// free function for lvgl callback
static void startSensors()
{
    SensorManager &manager = SensorManager::getInstance();
    manager.sendPinsOnSerial();
    manager.setInitialized(true);
    manager_GUI &manager_GUI = manager_GUI::getInstance();
    manager_GUI.hideMenu();
    manager_GUI.goToFirstSensor(true);
    // manager_GUI.construct();
    //  hideAllExceptFirst(true);
}

static void pinToSelection(int index)
{
    SensorManager &manager = SensorManager::getInstance();
    manager.setActivePin(index);
    manager_GUI &manager_GUI = manager_GUI::getInstance();
    manager_GUI.hideMenu();
    manager_GUI.goToFirstSensor(false);
    // manager_GUI.constructWiki();
    //  hideAllExceptFirst(false);
}

void manager_GUI::buildMenu()
{
    // Main container widget
    ui_MenuWidget = lv_obj_create(lv_scr_act());
    lv_obj_remove_style_all(ui_MenuWidget);
    lv_obj_set_size(ui_MenuWidget, 760, 440);
    lv_obj_set_align(ui_MenuWidget, LV_ALIGN_CENTER);
    lv_obj_set_style_radius(ui_MenuWidget, 15, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_MenuWidget, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_MenuWidget, 2, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Start button
    ui_btnStart = lv_btn_create(ui_MenuWidget);
    lv_obj_set_size(ui_btnStart, 120, 50);
    lv_obj_set_align(ui_btnStart, LV_ALIGN_TOP_RIGHT);
    lv_obj_add_event_cb(ui_btnStart, [](lv_event_t *e)
                        { startSensors(); }, LV_EVENT_CLICKED, nullptr);

    ui_ButtonStartLabel = lv_label_create(ui_btnStart);
    lv_label_set_text(ui_ButtonStartLabel, "Start");
    lv_obj_center(ui_ButtonStartLabel);

    static const lv_align_t align_map[3] = {
LV_ALIGN_LEFT_MID,
LV_ALIGN_CENTER,
LV_ALIGN_RIGHT_MID
    };
    // Create 6 pin containers
    for (int i = 0; i < 6; ++i)
    {
        pinContainers[i] = lv_btn_create(ui_MenuWidget);
        lv_obj_set_size(pinContainers[i], 180, 80);
        lv_obj_set_align(pinContainers[i], align_map[i%3]);
        lv_obj_set_y(pinContainers[i], (i < 3) ? -100 : 100);

        lv_obj_add_event_cb(pinContainers[i], [](lv_event_t *e)
                            {
            int index = (intptr_t)lv_event_get_user_data(e);
            pinToSelection(index); }, LV_EVENT_CLICKED, (void *)(intptr_t)i);

        pinLabels[i] = lv_label_create(pinContainers[i]);
        lv_label_set_text_fmt(pinLabels[i], "Pin %d", i);
        lv_obj_center(pinLabels[i]);
    }
    // Title
    lv_obj_t *title = lv_label_create(ui_MenuWidget);
    lv_label_set_text(title, "Main Menu");
    lv_obj_set_style_text_font(title, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_align(title, LV_ALIGN_TOP_MID, 0, 10);
}

void manager_GUI::updatePinLabelText()
{
    SensorManager &manager = SensorManager::getInstance();
    auto &pinMap = manager.getPinMap();
    for (int i = 0; i < 6; ++i)
    {
        if (pinMap[i])
        {
            lv_label_set_text_fmt(pinLabels[i], "%s", pinMap[i]->Type.c_str());
        }
        else
        {
            lv_label_set_text_fmt(pinLabels[i], "Pin %d", i);
        }
        lv_obj_center(pinLabels[i]);
    }
}

/***************************************************************
 *                    SENSOR GUI - Buttons
 ***************************************************************/

// DEPRECATED!!! | the isVisualisation makes sure that the proper version of construct is made
/*void manager_GUI::hideAllExceptFirst(bool isVisualisation)
{
    SensorManager &manager = SensorManager::getInstance();
    if(isVisualisation){
        auto *PinMap = manager.getPinMap();
    }else{
        auto *Sensors = manager.getSensors();
    }

    if (!isVisualisation)
    {
        for (auto *s : Sensors) // getSensors
        {
            constructSensor(s, false);
        }
        for (size_t i = 1; i < Sensors.size(); ++i)
        {
            Sensors[i]->hideSensor();
        }
        if (!Sensors.empty())
        {
            Sensors[0]->showSensor();
            manager.setCurrentIndex(0); // setCurrentIndex
        }
    }
    else
    {
        for (auto *s : PinMap) // getPinMap
        {
            constructSensor(s, true);
        }
        for (size_t i = 1; i < PinMap.size(); ++i)
        {
            if (PinMap[i])
                PinMap[i]->hideSensor();
        }
        if (PinMap[0])
        {
            PinMap[0]->showSensor();
            manager.setCurrentIndex(0); // setCurrentIndex
        }
    }
}*/

static void nextSensor(bool isVisualisation)
{
    SensorManager &manager = SensorManager::getInstance();
    auto &currentIndex = manager.getCurrentIndex();
    manager_GUI &manager_GUI = manager_GUI::getInstance();

    if (!isVisualisation)
    {
        auto &sensors = manager.getSensors();
        if (sensors.empty())
            return;
        currentIndex = (currentIndex + 1) % sensors.size();
        manager_GUI.constructWiki();
    }
    else
    {
        auto &pinMap = manager.getPinMap();
        size_t count = 0;
        for (auto *s : pinMap)
            if (s)
                count++;
        if (count == 0)
            return;

        // Find next valid pin
        do
        {
            currentIndex = (currentIndex + 1) % pinMap.size();
        } while (!pinMap[currentIndex]);
        manager_GUI.construct();
    }
}

static void prevSensor(bool isVisualisation)
{
    SensorManager &manager = SensorManager::getInstance();
    auto &currentIndex = manager.getCurrentIndex();
    manager_GUI &manager_GUI = manager_GUI::getInstance();

    if (!isVisualisation)
    {
        auto &sensors = manager.getSensors();
        if (sensors.empty())
            return;
        currentIndex = (currentIndex + sensors.size() - 1) % sensors.size();
        manager_GUI.constructWiki();
    }
    else
    {
        auto &pinMap = manager.getPinMap();
        size_t count = 0;
        for (auto *s : pinMap)
            if (s)
                count++;
        if (count == 0)
            return;

        // Find previous valid pin
        do
        {
            currentIndex = (currentIndex + pinMap.size() - 1) % pinMap.size();
        } while (!pinMap[currentIndex]);
        // TEMP
        logMessage("while loop done!");
        manager_GUI.construct();
    }
}

// Free function
static void goBackToMenu()
{
    SensorManager &manager = SensorManager::getInstance();
    auto &Sensors = manager.getSensors();
    auto &PinMap = manager.getPinMap();
    auto &currentIndex = manager.getCurrentIndex();
    manager_GUI &manager_GUI = manager_GUI::getInstance();
    // Since goToFirst was implemented this doesnt need to be checked
    // currentIndex = 0;
    manager.resetActivePin();
    manager.setInitialized(false);
    manager_GUI.hideSensorVisualisation();
    manager_GUI.hideSensorWiki();
    manager_GUI.showMenu();
}

// Free function
static void confirmSensor()
{
    SensorManager &manager = SensorManager::getInstance();
    auto &Sensors = manager.getSensors();
    auto &currentIndex = manager.getCurrentIndex();
    manager_GUI &manager_GUI = manager_GUI::getInstance();
    manager.assignSensorToPin(Sensors[currentIndex]);
    manager_GUI.updatePinLabelText();
    manager_GUI.hideSensorWiki();
    manager.resetActivePin();
    manager.sendPinsOnSerial();
    manager_GUI.showMenu();
}

/** @brief There are 2 versions, for version 1, theres the visualisation so isVisualisation is true, for version 0, theres the wiki*/
void manager_GUI::addNavButtonsToWidget(lv_obj_t *parentWidget, bool isVisualisation)
{
    ui_btnPrev = lv_btn_create(parentWidget);
    lv_obj_set_width(ui_btnPrev, 80);
    lv_obj_set_height(ui_btnPrev, 40);
    if (isVisualisation == true)
    { // Visualisation
        lv_obj_set_x(ui_btnPrev, 35);
        lv_obj_set_y(ui_btnPrev, -40);
    }
    else
    { // Wiki
        lv_obj_set_x(ui_btnPrev, 40);
        lv_obj_set_y(ui_btnPrev, -20);
    }
    lv_obj_set_align(ui_btnPrev, LV_ALIGN_BOTTOM_LEFT);
    lv_obj_add_flag(ui_btnPrev, LV_OBJ_FLAG_EVENT_BUBBLE); /// Flags
    lv_obj_clear_flag(ui_btnPrev, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE |
                                      LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
                                      LV_OBJ_FLAG_SCROLL_CHAIN);
    lv_obj_add_event_cb(ui_btnPrev, [](lv_event_t *e)
                        {
    bool isVis = reinterpret_cast<intptr_t>(lv_event_get_user_data(e));
    prevSensor(isVis); }, LV_EVENT_CLICKED, reinterpret_cast<void *>(isVisualisation));
    ui_btnPrevLabel = lv_label_create(ui_btnPrev);
    lv_label_set_text(ui_btnPrevLabel, "Prev");
    lv_obj_set_width(ui_btnPrevLabel, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_btnPrevLabel, LV_SIZE_CONTENT); /// 1
    lv_obj_set_align(ui_btnPrevLabel, LV_ALIGN_CENTER);

    ui_btnNext = lv_btn_create(parentWidget);
    lv_obj_set_width(ui_btnNext, 80);
    lv_obj_set_height(ui_btnNext, 40);
    if (isVisualisation == true)
    { // Visualisation
        lv_obj_set_x(ui_btnNext, 183);
        lv_obj_set_y(ui_btnNext, -40);
    }
    else
    {
        // Wiki
        lv_obj_set_x(ui_btnNext, 183);
        lv_obj_set_y(ui_btnNext, -20);
    }
    lv_obj_set_align(ui_btnNext, LV_ALIGN_BOTTOM_LEFT);
    lv_obj_add_flag(ui_btnNext, LV_OBJ_FLAG_EVENT_BUBBLE); /// Flags
    lv_obj_clear_flag(ui_btnNext, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE |
                                      LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
                                      LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
    lv_obj_add_event_cb(ui_btnNext, [](lv_event_t *e)
                        {
    bool isVis = reinterpret_cast<intptr_t>(lv_event_get_user_data(e));
    nextSensor(isVis); }, LV_EVENT_CLICKED, reinterpret_cast<void *>(isVisualisation));
    ui_btnNextLabel = lv_label_create(ui_btnNext);
    lv_label_set_text(ui_btnNextLabel, "Next");
    lv_obj_set_width(ui_btnNextLabel, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_btnNextLabel, LV_SIZE_CONTENT); /// 1
    lv_obj_set_align(ui_btnNextLabel, LV_ALIGN_CENTER);
}

void manager_GUI::addConfirmButtonToWidget(lv_obj_t *parentWidget)
{
    ui_btnConfirm = lv_btn_create(parentWidget);
    lv_obj_set_width(ui_btnConfirm, 80);
    lv_obj_set_height(ui_btnConfirm, 40);
    lv_obj_set_x(ui_btnConfirm, -50);
    lv_obj_set_y(ui_btnConfirm, -20);
    lv_obj_set_align(ui_btnConfirm, LV_ALIGN_BOTTOM_RIGHT);
    lv_obj_add_flag(ui_btnConfirm, LV_OBJ_FLAG_EVENT_BUBBLE); /// Flags
    lv_obj_clear_flag(ui_btnConfirm, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE |
                                         LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
                                         LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
    lv_obj_add_event_cb(ui_btnConfirm, [](lv_event_t *e)
                        { confirmSensor(); }, LV_EVENT_CLICKED, nullptr);
    ui_btnConfirmLabel = lv_label_create(ui_btnConfirm);
    lv_obj_set_width(ui_btnConfirmLabel, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_btnConfirmLabel, LV_SIZE_CONTENT); /// 1
    lv_obj_set_align(ui_btnConfirmLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_btnConfirmLabel, "Confirm");
}

void manager_GUI::addBackButtonToWidget(lv_obj_t *parentWidget)
{
    lv_obj_t *ButtonBackGroup = lv_obj_create(parentWidget);
    lv_obj_remove_style_all(ButtonBackGroup);
    lv_obj_set_width(ButtonBackGroup, 100);
    lv_obj_set_height(ButtonBackGroup, 40);
    lv_obj_clear_flag(ButtonBackGroup, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE); /// Flags

    lv_obj_t *ButtonBackCornerBottomLeft = lv_obj_create(ButtonBackGroup);
    lv_obj_remove_style_all(ButtonBackCornerBottomLeft);
    lv_obj_set_width(ButtonBackCornerBottomLeft, 20);
    lv_obj_set_height(ButtonBackCornerBottomLeft, 20);
    lv_obj_set_align(ButtonBackCornerBottomLeft, LV_ALIGN_BOTTOM_LEFT);
    lv_obj_clear_flag(ButtonBackCornerBottomLeft, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_obj_set_style_bg_color(ButtonBackCornerBottomLeft, lv_color_hex(0x009BFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ButtonBackCornerBottomLeft, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ButtonBackCornerBottomLeft, false, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *ButtonBackCornerTopRight = lv_obj_create(ButtonBackGroup);
    lv_obj_remove_style_all(ButtonBackCornerTopRight);
    lv_obj_set_width(ButtonBackCornerTopRight, 20);
    lv_obj_set_height(ButtonBackCornerTopRight, 20);
    lv_obj_set_align(ButtonBackCornerTopRight, LV_ALIGN_TOP_RIGHT);
    lv_obj_clear_flag(ButtonBackCornerTopRight, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_obj_set_style_bg_color(ButtonBackCornerTopRight, lv_color_hex(0x009BFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ButtonBackCornerTopRight, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ButtonBackCornerTopRight, false, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *btnBack = lv_btn_create(ButtonBackGroup);
    lv_obj_set_width(btnBack, 100);
    lv_obj_set_height(btnBack, 40);
    lv_obj_add_flag(btnBack, LV_OBJ_FLAG_EVENT_BUBBLE); /// Flags
    lv_obj_clear_flag(btnBack, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE |
                                   LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
                                   LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
    lv_obj_add_event_cb(btnBack, [](lv_event_t *e)
                        { goBackToMenu(); }, LV_EVENT_CLICKED, nullptr);
    lv_obj_set_style_clip_corner(btnBack, false, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *ButtonBackLabel = lv_label_create(btnBack);
    lv_obj_set_width(ButtonBackLabel, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ButtonBackLabel, LV_SIZE_CONTENT); /// 1
    lv_obj_set_align(ButtonBackLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ButtonBackLabel, "Back");
    lv_obj_set_style_text_font(ButtonBackLabel, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
}

/***************************************************************
 *                    SENSOR GUI - Sensors
 ***************************************************************/

void manager_GUI::showSensorWiki()
{
    if (ui_SensorWidgetWiki)
        lv_obj_clear_flag(ui_SensorWidgetWiki, LV_OBJ_FLAG_HIDDEN);
}

void manager_GUI::hideSensorWiki()
{
    if (ui_SensorWidgetWiki)
        lv_obj_add_flag(ui_SensorWidgetWiki, LV_OBJ_FLAG_HIDDEN);
}

void manager_GUI::showSensorVisualisation()
{
    if (ui_SensorWidget)
        lv_obj_clear_flag(ui_SensorWidget, LV_OBJ_FLAG_HIDDEN);
}
void manager_GUI::hideSensorVisualisation()
{
    if (ui_SensorWidget)
        lv_obj_add_flag(ui_SensorWidget, LV_OBJ_FLAG_HIDDEN);
}

void manager_GUI::constructWiki()
{
    if (!ui_SensorWidgetWiki || !lv_obj_is_valid(ui_SensorWidgetWiki))
    {
        // Container
        ui_SensorWidgetWiki = lv_obj_create(lv_scr_act());
        lv_obj_remove_style_all(ui_SensorWidgetWiki);
        lv_obj_set_width(ui_SensorWidgetWiki, 760);
        lv_obj_set_height(ui_SensorWidgetWiki, 440);
        lv_obj_set_align(ui_SensorWidgetWiki, LV_ALIGN_CENTER);
        lv_obj_clear_flag(ui_SensorWidgetWiki, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE |
                                                   LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC |
                                                   LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
        lv_obj_set_style_radius(ui_SensorWidgetWiki, 15, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(ui_SensorWidgetWiki, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_opa(ui_SensorWidgetWiki, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_border_color(ui_SensorWidgetWiki, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_border_opa(ui_SensorWidgetWiki, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_border_width(ui_SensorWidgetWiki, 2, LV_PART_MAIN | LV_STATE_DEFAULT);

        // Title
        ui_SensorLabelWiki = lv_label_create(ui_SensorWidgetWiki);
        lv_label_set_text(ui_SensorLabelWiki, "Sensor Label");
        lv_obj_set_width(ui_SensorLabelWiki, LV_SIZE_CONTENT);
        lv_obj_set_height(ui_SensorLabelWiki, LV_SIZE_CONTENT);
        lv_obj_set_x(ui_SensorLabelWiki, 0);
        lv_obj_set_y(ui_SensorLabelWiki, -185);
        lv_obj_set_align(ui_SensorLabelWiki, LV_ALIGN_CENTER);
        lv_obj_clear_flag(ui_SensorLabelWiki, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE |
                                              LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
                                              LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
        lv_obj_set_style_text_color(ui_SensorLabelWiki, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_opa(ui_SensorLabelWiki, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_font(ui_SensorLabelWiki, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);

        ui_SensorLabelDescription = lv_label_create(ui_SensorWidgetWiki);
        lv_obj_set_width(ui_SensorLabelDescription, LV_SIZE_CONTENT);  /// 1
        lv_obj_set_height(ui_SensorLabelDescription, LV_SIZE_CONTENT); /// 1
        lv_obj_set_x(ui_SensorLabelDescription, 25);
        lv_obj_set_y(ui_SensorLabelDescription, 100);
        lv_label_set_text(ui_SensorLabelDescription, "Description");
        lv_obj_clear_flag(ui_SensorLabelDescription,
                          LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE |
                              LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
                              LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
        lv_obj_set_style_text_color(ui_SensorLabelDescription, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_opa(ui_SensorLabelDescription, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

        addNavButtonsToWidget(ui_SensorWidgetWiki, false);
        addConfirmButtonToWidget(ui_SensorWidgetWiki);
        addBackButtonToWidget(ui_SensorWidgetWiki);
    }

    SensorManager &manager = SensorManager::getInstance();
    auto *sensorCurrent = manager.getSensors()[manager.getCurrentIndex()];
    lv_label_set_text(ui_SensorLabelWiki, sensorCurrent->Type.c_str());
    lv_label_set_text(ui_SensorLabelDescription, sensorCurrent->Description.c_str());
    manager.showCurrentSensorInfo(false);
    showSensorWiki();
}

void manager_GUI::construct(/*bool hasTwoUnits*/)
{
    if (!ui_SensorWidget || !lv_obj_is_valid(ui_SensorWidget))
    {
        /*  if(hasTwoUnits){
          // Container
          ui_SensorWidget = lv_obj_create(lv_scr_act());
          lv_obj_remove_style_all(ui_SensorWidget);
          lv_obj_set_width(ui_SensorWidget, 760);
          lv_obj_set_height(ui_SensorWidget, 440);
          lv_obj_set_align(ui_SensorWidget, LV_ALIGN_CENTER);
          lv_obj_clear_flag(ui_SensorWidget, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE |
                                           LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC |
                                           LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
          lv_obj_set_style_radius(ui_SensorWidget, 15, LV_PART_MAIN | LV_STATE_DEFAULT);
          lv_obj_set_style_bg_color(ui_SensorWidget, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
          lv_obj_set_style_bg_opa(ui_SensorWidget, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
          lv_obj_set_style_border_color(ui_SensorWidget, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
          lv_obj_set_style_border_opa(ui_SensorWidget, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
          lv_obj_set_style_border_width(ui_SensorWidget, 2, LV_PART_MAIN | LV_STATE_DEFAULT);

          // Title
          ui_Label = lv_label_create(ui_SensorWidget);
          lv_label_set_text(ui_Label, "Sensor Label");
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

          ui_ContainerForValue_2 = lv_obj_create(ui_SensorWidget);
          lv_obj_remove_style_all(ui_ContainerForValue_2);
          lv_obj_set_width(ui_ContainerForValue_2, 230);
          lv_obj_set_height(ui_ContainerForValue_2, 118);
          lv_obj_set_x(ui_ContainerForValue_2, -230);
          lv_obj_set_y(ui_ContainerForValue_2, 55);
          lv_obj_set_align(ui_ContainerForValue_2, LV_ALIGN_CENTER);
          lv_obj_clear_flag(ui_ContainerForValue_2,
                            LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE |
                                LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
                                LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
          lv_obj_set_style_radius(ui_ContainerForValue_2, 15, LV_PART_MAIN | LV_STATE_DEFAULT);
          lv_obj_set_style_bg_color(ui_ContainerForValue_2, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
          lv_obj_set_style_bg_opa(ui_ContainerForValue_2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
          lv_obj_set_style_border_color(ui_ContainerForValue_2, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
          lv_obj_set_style_border_opa(ui_ContainerForValue_2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
          lv_obj_set_style_border_width(ui_ContainerForValue_2, 2, LV_PART_MAIN | LV_STATE_DEFAULT);

          ui_VisualColorForValue_2 = lv_obj_create(ui_ContainerForValue_2);
          lv_obj_remove_style_all(ui_VisualColorForValue_2);
          lv_obj_set_width(ui_VisualColorForValue_2, 20);
          lv_obj_set_height(ui_VisualColorForValue_2, 20);
          lv_obj_set_x(ui_VisualColorForValue_2, -10);
          lv_obj_set_y(ui_VisualColorForValue_2, 10);
          lv_obj_set_align(ui_VisualColorForValue_2, LV_ALIGN_TOP_RIGHT);
          lv_obj_clear_flag(ui_VisualColorForValue_2, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE); /// Flags
          lv_obj_set_style_radius(ui_VisualColorForValue_2, 1000, LV_PART_MAIN | LV_STATE_DEFAULT);
          lv_obj_set_style_bg_color(ui_VisualColorForValue_2, lv_color_hex(0x37F006), LV_PART_MAIN | LV_STATE_DEFAULT);
          lv_obj_set_style_bg_opa(ui_VisualColorForValue_2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

          ui_LabelDescValue_2 = lv_label_create(ui_ContainerForValue_2);
          lv_obj_set_width(ui_LabelDescValue_2, LV_SIZE_CONTENT);  /// 1
          lv_obj_set_height(ui_LabelDescValue_2, LV_SIZE_CONTENT); /// 1
          lv_obj_set_x(ui_LabelDescValue_2, 0);
          lv_obj_set_y(ui_LabelDescValue_2, 32);
          lv_obj_set_align(ui_LabelDescValue_2, LV_ALIGN_CENTER);
          lv_label_set_text(ui_LabelDescValue_2, "[unit]");
          lv_obj_clear_flag(ui_LabelDescValue_2,
                            LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE |
                                LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
                                LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
          lv_obj_set_style_text_color(ui_LabelDescValue_2, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
          lv_obj_set_style_text_opa(ui_LabelDescValue_2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
          lv_obj_set_style_text_font(ui_LabelDescValue_2, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);

          ui_LabelValueValue_2 = lv_label_create(ui_ContainerForValue_2);
          lv_obj_set_width(ui_LabelValueValue_2, LV_SIZE_CONTENT);  /// 1
          lv_obj_set_height(ui_LabelValueValue_2, LV_SIZE_CONTENT); /// 1
          lv_obj_set_x(ui_LabelValueValue_2, 0);
          lv_obj_set_y(ui_LabelValueValue_2, 15);
          lv_obj_set_align(ui_LabelValueValue_2, LV_ALIGN_CENTER);
          lv_label_set_text(ui_LabelValueValue_2, "0");
          lv_obj_clear_flag(ui_LabelValueValue_2,
                            LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE |
                                LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
                                LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
          lv_obj_set_style_text_color(ui_LabelValueValue_2, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
          lv_obj_set_style_text_opa(ui_LabelValueValue_2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
          lv_obj_set_style_text_font(ui_LabelValueValue_2, &lv_font_montserrat_40, LV_PART_MAIN | LV_STATE_DEFAULT);

          ui_LabelTypeValue_2 = lv_label_create(ui_ContainerForValue_2);
          lv_obj_set_width(ui_LabelTypeValue_2, LV_SIZE_CONTENT);  /// 1
          lv_obj_set_height(ui_LabelTypeValue_2, LV_SIZE_CONTENT); /// 1
          lv_obj_set_x(ui_LabelTypeValue_2, 15);
          lv_obj_set_y(ui_LabelTypeValue_2, 10);
          lv_label_set_text(ui_LabelTypeValue_2, "Type");
          lv_obj_set_style_text_color(ui_LabelTypeValue_2, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
          lv_obj_set_style_text_opa(ui_LabelTypeValue_2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

          ui_ContainerForValue_1 = lv_obj_create(ui_SensorWidget);
          lv_obj_remove_style_all(ui_ContainerForValue_1);
          lv_obj_set_width(ui_ContainerForValue_1, 230);
          lv_obj_set_height(ui_ContainerForValue_1, 118);
          lv_obj_set_x(ui_ContainerForValue_1, -230);
          lv_obj_set_y(ui_ContainerForValue_1, -85);
          lv_obj_set_align(ui_ContainerForValue_1, LV_ALIGN_CENTER);
          lv_obj_clear_flag(ui_ContainerForValue_1,
                            LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE |
                                LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
                                LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
          lv_obj_set_style_radius(ui_ContainerForValue_1, 15, LV_PART_MAIN | LV_STATE_DEFAULT);
          lv_obj_set_style_border_color(ui_ContainerForValue_1, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
          lv_obj_set_style_border_opa(ui_ContainerForValue_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
          lv_obj_set_style_border_width(ui_ContainerForValue_1, 2, LV_PART_MAIN | LV_STATE_DEFAULT);

          ui_VisualColorForValue_1 = lv_obj_create(ui_ContainerForValue_1);
          lv_obj_remove_style_all(ui_VisualColorForValue_1);
          lv_obj_set_width(ui_VisualColorForValue_1, 20);
          lv_obj_set_height(ui_VisualColorForValue_1, 20);
          lv_obj_set_x(ui_VisualColorForValue_1, -10);
          lv_obj_set_y(ui_VisualColorForValue_1, 10);
          lv_obj_set_align(ui_VisualColorForValue_1, LV_ALIGN_TOP_RIGHT);
          lv_obj_clear_flag(ui_VisualColorForValue_1, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE); /// Flags
          lv_obj_set_style_radius(ui_VisualColorForValue_1, 1000, LV_PART_MAIN | LV_STATE_DEFAULT);
          lv_obj_set_style_bg_color(ui_VisualColorForValue_1, lv_color_hex(0x009BFF), LV_PART_MAIN | LV_STATE_DEFAULT);
          lv_obj_set_style_bg_opa(ui_VisualColorForValue_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

          ui_LabelValueValue_1 = lv_label_create(ui_ContainerForValue_1);
          lv_obj_set_width(ui_LabelValueValue_1, LV_SIZE_CONTENT);  /// 1
          lv_obj_set_height(ui_LabelValueValue_1, LV_SIZE_CONTENT); /// 1
          lv_obj_set_x(ui_LabelValueValue_1, 0);
          lv_obj_set_y(ui_LabelValueValue_1, -5);
          lv_obj_set_align(ui_LabelValueValue_1, LV_ALIGN_CENTER);
          lv_label_set_text(ui_LabelValueValue_1, "0");
          lv_obj_clear_flag(ui_LabelValueValue_1,
                            LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE |
                                LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
                                LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
          lv_obj_set_style_text_color(ui_LabelValueValue_1, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
          lv_obj_set_style_text_opa(ui_LabelValueValue_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
          lv_obj_set_style_text_font(ui_LabelValueValue_1, &lv_font_montserrat_40, LV_PART_MAIN | LV_STATE_DEFAULT);

          ui_LabelDescValue_1 = lv_label_create(ui_ContainerForValue_1);
          lv_obj_set_width(ui_LabelDescValue_1, LV_SIZE_CONTENT);  /// 1
          lv_obj_set_height(ui_LabelDescValue_1, LV_SIZE_CONTENT); /// 1
          lv_obj_set_x(ui_LabelDescValue_1, 0);
          lv_obj_set_y(ui_LabelDescValue_1, 30);
          lv_obj_set_align(ui_LabelDescValue_1, LV_ALIGN_CENTER);
          lv_label_set_text(ui_LabelDescValue_1, "[°C]");
          lv_obj_clear_flag(ui_LabelDescValue_1,
                            LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE |
                                LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
                                LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
          lv_obj_set_style_text_color(ui_LabelDescValue_1, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
          lv_obj_set_style_text_opa(ui_LabelDescValue_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
          lv_obj_set_style_text_font(ui_LabelDescValue_1, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);

          ui_LabelTypeValue_1 = lv_label_create(ui_ContainerForValue_1);
          lv_obj_set_width(ui_LabelTypeValue_1, LV_SIZE_CONTENT);  /// 1
          lv_obj_set_height(ui_LabelTypeValue_1, LV_SIZE_CONTENT); /// 1
          lv_obj_set_x(ui_LabelTypeValue_1, 15);
          lv_obj_set_y(ui_LabelTypeValue_1, 10);
          lv_label_set_text(ui_LabelTypeValue_1, "Teplota");
          lv_obj_set_style_text_color(ui_LabelTypeValue_1, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
          lv_obj_set_style_text_opa(ui_LabelTypeValue_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

          // Navigation
          addNavButtonsToWidget(ui_SensorWidget);
          addBackButtonToWidget(ui_SensorWidget);

          // Chart
          ui_Chart = lv_chart_create(ui_SensorWidget);
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
          lv_obj_set_style_text_opa(ui_Chart, 255, LV_PART_TICKS | LV_STATE_DEFAULT);
  */
        ui_SensorWidget = lv_obj_create(lv_scr_act());
        lv_obj_remove_style_all(ui_SensorWidget);
        lv_obj_set_width(ui_SensorWidget, 760);
        lv_obj_set_height(ui_SensorWidget, 440);
        lv_obj_set_align(ui_SensorWidget, LV_ALIGN_CENTER);
        lv_obj_clear_flag(ui_SensorWidget, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE |
                                               LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC |
                                               LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
        lv_obj_set_style_radius(ui_SensorWidget, 15, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(ui_SensorWidget, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_opa(ui_SensorWidget, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_border_color(ui_SensorWidget, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_border_opa(ui_SensorWidget, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_border_width(ui_SensorWidget, 2, LV_PART_MAIN | LV_STATE_DEFAULT);

        ui_SensorLabel = lv_label_create(ui_SensorWidget);
        lv_obj_set_width(ui_SensorLabel, LV_SIZE_CONTENT);  /// 1
        lv_obj_set_height(ui_SensorLabel, LV_SIZE_CONTENT); /// 1
        lv_obj_set_x(ui_SensorLabel, 0);
        lv_obj_set_y(ui_SensorLabel, -185);
        lv_obj_set_align(ui_SensorLabel, LV_ALIGN_CENTER);
        lv_obj_clear_flag(ui_SensorLabel, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE |
                                              LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
                                              LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
        lv_obj_set_style_text_color(ui_SensorLabel, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_opa(ui_SensorLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_font(ui_SensorLabel, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);

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
                              LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
        lv_obj_set_style_radius(ui_ContainerForValue_1, 15, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(ui_ContainerForValue_1, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_opa(ui_ContainerForValue_1, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_border_color(ui_ContainerForValue_1, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_border_opa(ui_ContainerForValue_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_border_width(ui_ContainerForValue_1, 2, LV_PART_MAIN | LV_STATE_DEFAULT);

        ui_VisualColorForValue_1 = lv_obj_create(ui_ContainerForValue_1);
        lv_obj_remove_style_all(ui_VisualColorForValue_1);
        lv_obj_set_width(ui_VisualColorForValue_1, 20);
        lv_obj_set_height(ui_VisualColorForValue_1, 20);
        lv_obj_set_x(ui_VisualColorForValue_1, -10);
        lv_obj_set_y(ui_VisualColorForValue_1, 10);
        lv_obj_set_align(ui_VisualColorForValue_1, LV_ALIGN_TOP_RIGHT);
        lv_obj_clear_flag(ui_VisualColorForValue_1, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE); /// Flags
        lv_obj_set_style_radius(ui_VisualColorForValue_1, 1000, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(ui_VisualColorForValue_1, lv_color_hex(0xFFAF00), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_opa(ui_VisualColorForValue_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

        ui_LabelValueValue_1 = lv_label_create(ui_ContainerForValue_1);
        lv_obj_set_width(ui_LabelValueValue_1, LV_SIZE_CONTENT);  /// 1
        lv_obj_set_height(ui_LabelValueValue_1, LV_SIZE_CONTENT); /// 1
        lv_obj_set_x(ui_LabelValueValue_1, 0);
        lv_obj_set_y(ui_LabelValueValue_1, -5);
        lv_obj_set_align(ui_LabelValueValue_1, LV_ALIGN_CENTER);
        lv_obj_clear_flag(ui_LabelValueValue_1,
                          LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE |
                              LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
                              LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
        lv_obj_set_style_text_color(ui_LabelValueValue_1, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_opa(ui_LabelValueValue_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_font(ui_LabelValueValue_1, &lv_font_montserrat_40, LV_PART_MAIN | LV_STATE_DEFAULT);

        ui_LabelDescValue_1 = lv_label_create(ui_ContainerForValue_1);
        lv_obj_set_width(ui_LabelDescValue_1, LV_SIZE_CONTENT);  /// 1
        lv_obj_set_height(ui_LabelDescValue_1, LV_SIZE_CONTENT); /// 1
        lv_obj_set_x(ui_LabelDescValue_1, 0);
        lv_obj_set_y(ui_LabelDescValue_1, 30);
        lv_obj_set_align(ui_LabelDescValue_1, LV_ALIGN_CENTER);
        lv_obj_clear_flag(ui_LabelDescValue_1,
                          LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE |
                              LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
                              LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
        lv_obj_set_style_text_color(ui_LabelDescValue_1, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_opa(ui_LabelDescValue_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_font(ui_LabelDescValue_1, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);

        // true because its visualisation for sensors
        addNavButtonsToWidget(ui_SensorWidget, true);
        addBackButtonToWidget(ui_SensorWidget);

        ui_Chart = lv_chart_create(ui_SensorWidget);
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

        ui_Chart_series_V1 = lv_chart_add_series(ui_Chart, lv_color_hex(0xFFAF00),
                                                 LV_CHART_AXIS_PRIMARY_Y);
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

    SensorManager &manager = SensorManager::getInstance();
    // TEMP
    logMessage("getting ready to take sensorCurrent!");
    auto *sensorCurrent = manager.getAssignedSensor(manager.getCurrentIndex());
    // TEMP
    logMessage("sensorCurrent got taken from manager!");
    lv_label_set_text(ui_SensorLabel, sensorCurrent->Type.c_str());
    lv_label_set_text(ui_LabelValueValue_1, "0");
    // Need to add [UNIT] take.
    lv_label_set_text(ui_LabelDescValue_1, "[Unit]");
    // manager.showCurrentSensorInfo(true);
    showSensorVisualisation();
}

// Only one sensor will be drawn at a Time
void manager_GUI::drawCurrentSensor()
{
    SensorManager &manager = SensorManager::getInstance();
    auto *sensorCurrent = manager.getAssignedSensor(manager.getCurrentIndex());
    //TEMP
    // manager.showCurrentSensorInfo(true);

    if (!(sensorCurrent->getRedrawPending()))
    {
        return;
    }
    //TEMP
    logMessage("RedrawPending: %d\n", sensorCurrent->getRedrawPending());

    auto Values = sensorCurrent->getValuesKeys();
    for (auto &Key : Values)
    {
        //TEMP
        logMessage("RedrawPending: %d\n",sensorCurrent->getRedrawPending());

        std::string value = sensorCurrent->getValue<std::string>(Key.c_str());
        lv_label_set_text(ui_LabelValueValue_1, value.c_str());
        static lv_coord_t ui_Chart_hist[HISTORY_CAP];
        sensorCurrent->getHistory<float>(Key.c_str(), ui_Chart_hist);
        //TEMP
        logMessage("value string: %s\n", Key.c_str());

        lv_coord_t min_val = ui_Chart_hist[0];
        lv_coord_t max_val = ui_Chart_hist[0];
        long sum = 0;
        for (int i = 0; i < HISTORY_CAP; i++)
        {
            lv_coord_t j = ui_Chart_hist[i];
            //TEMP
            logMessage("%d. history : %d\n", i, j);
            if (j < min_val)
                min_val = j;
            if (j > max_val)
                max_val = j;
            sum += j;
        }
        float avg = (float)sum / HISTORY_CAP;

        lv_coord_t delta = max_val - min_val;
        lv_coord_t y_min = min_val;
        lv_coord_t y_max = max_val + delta / 10 + 100;
        y_max = y_max - y_max % 100;

        lv_chart_set_ext_y_array(ui_Chart, ui_Chart_series_V1, ui_Chart_hist);
        lv_chart_set_range(ui_Chart, LV_CHART_AXIS_PRIMARY_Y, 0, y_max);
        lv_chart_refresh(ui_Chart);
    }

    sensorCurrent->setRedrawPending(false); // Reset flag to redraw sensor.
}

void manager_GUI::goToFirstSensor(bool isVisualisation)
{
    SensorManager &manager = SensorManager::getInstance();
    auto &currentIndex = manager.getCurrentIndex();

    if (!isVisualisation)
    {
        auto &sensors = manager.getSensors();
        if (sensors.empty())
            return;

        // první existující senzor
        currentIndex = 0;
        constructWiki();
    }
    else
    {
        auto &pinMap = manager.getPinMap();
        if (pinMap.empty())
            return;

        // najít první NOTNUll pointer
        size_t i = 0;
        while (i < pinMap.size() && !pinMap[i])
            i++;
        if (i == pinMap.size())
            return; // žádný senzor není

        currentIndex = i;
        construct();
    }
}

// THINGS THAT NEED TO BE MULTIPLE
/*
    VALUE OF SENSOR CONTAINERS
    ui_Chart_series_V1
    ui_Chart_buff
*/