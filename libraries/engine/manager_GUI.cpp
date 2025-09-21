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

/*manager_GUI& manager_GUI::getInstance() {
    static manager_GUI instance;
    return instance;
}*/

manager_GUI::manager_GUI()
    : ui_MenuWidget(nullptr), ui_btnStart(nullptr), ui_ButtonStartLabel(nullptr)
{
    buildMenu();
    hideMenu(); // start hidden
}

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

    // Create 6 pin containers
    for (int i = 0; i < 6; ++i)
    {
        pinContainers[i] = lv_btn_create(ui_MenuWidget);
        lv_obj_set_size(pinContainers[i], 180, 80);
        lv_obj_set_align(pinContainers[i], static_cast<lv_align_t>(LV_ALIGN_LEFT_MID + (i % 3)));
        lv_obj_set_y(pinContainers[i], (i / 3) ? 100 : -100);

        lv_obj_add_event_cb(pinContainers[i], [i](lv_event_t *e)
                            { pin_btn(i); }, LV_EVENT_CLICKED, nullptr);

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

void manager_GUI::updatePinLabelText(int pinIndex)
{
    BaseSensor *s = SensorManager::getInstance().getAssignedSensor(pinIndex);
    if (s)
    {
        lv_label_set_text_fmt(pinLabels[pinIndex], "%s", s->Type.c_str());
    }
    else
    {
        lv_label_set_text_fmt(pinLabels[pinIndex], "Pin %d", pinIndex);
    }
    lv_obj_center(pinLabels[pinIndex]);
}

void manager_GUI::startSensors()
{
    SensorManager &manager = SensorManager::getInstance();
    manager.sendPinsOnSerial();
    manager.setInitialized(true);
    hideAllExceptFirst(true);
}

void manager_GUI::pinToSelection(int index)
{
    SensorManager &manager = SensorManager::getInstance();
    manager.setActivePin(index);
    hideAllExceptFirst(false);
}

/***************************************************************
 *                    SENSOR GUI - Buttons
 ***************************************************************/

// the isVisualisation makes sure that the proper version of construct is made
void manager_GUI::hideAllExceptFirst(bool isVisualisation)
{
    if (!isVisualisation)
    {
        for (auto *s : Sensors)
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
            currentIndex = 0;
        }
    }
    else
    {
        for (auto *s : PinMap)
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
            currentIndex = 0;
        }
    }
}
void manager_GUI::nextSensor(bool isVisualisation)
{
    if (isVisualisation)
    {
        if (Sensors.empty())
            return;
        Sensors[currentIndex]->hideSensor();
        currentIndex = (currentIndex + 1) % Sensors.size();
        Sensors[currentIndex]->showSensor();
    }
    else
    {
        if (PinMap.empty())
            return;
        size_t count = 0;
        for (auto *s : PinMap)
            if (s)
                count++;
        if (count == 0)
            return;

        // Find next valid pin
        PinMap[currentIndex]->hideSensor();
        do
        {
            currentIndex = (currentIndex + 1) % PinMap.size();
        } while (!PinMap[currentIndex]);
        PinMap[currentIndex]->showSensor();
    }
}

void manager_GUI::prevSensor(bool isVisualisation)
{
    if (isVisualisation)
    {
        if (Sensors.empty())
            return;
        Sensors[currentIndex]->hideSensor();
        currentIndex = (currentIndex + Sensors.size() - 1) % Sensors.size();
        Sensors[currentIndex]->showSensor();
    }
    else
    {
        if (PinMap.empty())
            return;
        size_t count = 0;
        for (auto *s : PinMap)
            if (s)
                count++;
        if (count == 0)
            return;

        // Find previous valid pin
        PinMap[currentIndex]->hideSensor();
        do
        {
            currentIndex = (currentIndex + PinMap.size() - 1) % PinMap.size();
        } while (!PinMap[currentIndex]);
        PinMap[currentIndex]->showSensor();
    }
}

void manager_GUI::confirmSensor()
{
    if (Sensors.empty())
        return;
    assignSensorToPin(Sensors[currentIndex]);
    sendPinsOnSerial();
    update_pin_label_text(activePin);
    goBackToMenu();
}

void manager_GUI::goBackToMenu()
{
    if (Sensors.empty())
    {
        return;
    }

    Sensors[currentIndex]->hideSensor();
    PinMap[currentIndex]->hideSensor();

    currentIndex = 0;
    activePin = NUM_PINS;
    initialized = false;

    showMenu();
}

/** @brief There are 2 versions, for version 1, theres the visualisation so isVisualisation is true, for version 0, theres the wiki*/
void addNavButtonsToWidget(lv_obj_t *parentWidget, bool isVisualisation = true)
{
    lv_obj_t *btnPrev = lv_btn_create(parentWidget);
    lv_obj_set_width(btnPrev, 80);
    lv_obj_set_height(btnPrev, 40);
    if (isVisualisation == true)
    { // Visualisation
        lv_obj_set_x(btnPrev, 35);
        lv_obj_set_y(btnPrev, -40);
    }
    else
    { // Wiki
        lv_obj_set_x(btnPrev, 40);
        lv_obj_set_y(btnPrev, -20);
    }
    lv_obj_set_align(btnPrev, LV_ALIGN_BOTTOM_LEFT);
    lv_obj_add_flag(btnPrev, LV_OBJ_FLAG_EVENT_BUBBLE); /// Flags
    lv_obj_clear_flag(btnPrev, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE |
                                   LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
                                   LV_OBJ_FLAG_SCROLL_CHAIN);
    lv_obj_add_event_cb(btnPrev, [](lv_event_t *e)
                        { prevSensor(); }, LV_EVENT_CLICKED, &isVisualisation);
    lv_obj_t *ButtonLabelPrev = lv_label_create(btnPrev);
    lv_label_set_text(ButtonLabelPrev, "Prev");
    lv_obj_set_width(ButtonLabelPrev, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ButtonLabelPrev, LV_SIZE_CONTENT); /// 1
    lv_obj_set_align(ButtonLabelPrev, LV_ALIGN_CENTER);

    lv_obj_t *btnNext = lv_btn_create(parentWidget);
    lv_obj_set_width(btnNext, 80);
    lv_obj_set_height(btnNext, 40);
    if (isVisualisation == true)
    { // Visualisation
        lv_obj_set_x(btnNext, 183);
        lv_obj_set_y(btnNext, -40);
    }
    else
    {
        // Wiki
        lv_obj_set_x(btnNext, -110);
        lv_obj_set_y(btnNext, -20);
    }
    lv_obj_set_align(btnNext, LV_ALIGN_BOTTOM_LEFT);
    lv_obj_add_flag(btnNext, LV_OBJ_FLAG_EVENT_BUBBLE); /// Flags
    lv_obj_clear_flag(btnNext, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE |
                                   LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
                                   LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
    lv_obj_add_event_cb(btnNext, [](lv_event_t *e)
                        { nextSensor(); }, LV_EVENT_CLICKED, &isVisualisation);
    lv_obj_t *ButtonLabelNext = lv_label_create(btnNext);
    lv_label_set_text(ButtonLabelNext, "Next");
    lv_obj_set_width(ButtonLabelNext, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ButtonLabelNext, LV_SIZE_CONTENT); /// 1
    lv_obj_set_align(ButtonLabelNext, LV_ALIGN_CENTER);
}

void addConfirmButtonToWidget(lv_obj_t *parentWidget)
{
    lv_obj_t *btnConfirm = lv_btn_create(parentWidget);
    lv_obj_set_width(btnConfirm, 80);
    lv_obj_set_height(btnConfirm, 40);
    lv_obj_set_x(btnConfirm, -50);
    lv_obj_set_y(btnConfirm, -20);
    lv_obj_set_align(btnConfirm, LV_ALIGN_BOTTOM_RIGHT);
    lv_obj_add_flag(btnConfirm, LV_OBJ_FLAG_EVENT_BUBBLE); /// Flags
    lv_obj_clear_flag(btnConfirm, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE |
                                      LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
                                      LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
    lv_obj_add_event_cb(btnConfirm, [](lv_event_t *e)
                        { confirmSensor(); }, LV_EVENT_CLICKED, nullptr);
    lv_obj_t *ButtonConfirmLabel = lv_label_create(btnConfirm);
    lv_obj_set_width(ButtonConfirmLabel, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ButtonConfirmLabel, LV_SIZE_CONTENT); /// 1
    lv_obj_set_align(ButtonConfirmLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ButtonConfirmLabel, "Confirm");
}

void addBackButtonToWidget(lv_obj_t *parentWidget)
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
