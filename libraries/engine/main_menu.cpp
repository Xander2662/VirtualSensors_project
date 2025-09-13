/**
 * @file main_menu.cpp
 * @brief Definition of the MainMenu widget
 *
 * This source defines the MainMenu widget with a Start button
 * and 6 pin containers for sensor assignment.
 *
 * @copyright 2025
 * @author Ondřej Wrubel
 */

#include "main_menu.hpp"
#include "manager.hpp"
#include <iostream> // for debug logs
#include "base_sensor.hpp"

MainMenu& MainMenu::getInstance() {
    static MainMenu instance;
    return instance;
}

MainMenu::MainMenu()
    : ui_Widget(nullptr), ui_btnStart(nullptr), ui_ButtonStartLabel(nullptr)
{
    build();
    hide(); // start hidden
}

void MainMenu::show()
{
    if (ui_Widget)
        lv_obj_clear_flag(ui_Widget, LV_OBJ_FLAG_HIDDEN);
}

void MainMenu::hide()
{
    if (ui_Widget)
        lv_obj_add_flag(ui_Widget, LV_OBJ_FLAG_HIDDEN);
}

void MainMenu::build()
{
    // Main container widget
    ui_Widget = lv_obj_create(lv_scr_act());
    lv_obj_remove_style_all(ui_Widget);
    lv_obj_set_size(ui_Widget, 760, 440);
    lv_obj_set_align(ui_Widget, LV_ALIGN_CENTER);
    lv_obj_set_style_radius(ui_Widget, 15, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Widget, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_Widget, 2, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Start button
    ui_btnStart = lv_btn_create(ui_Widget);
    lv_obj_set_size(ui_btnStart, 120, 50);
    lv_obj_set_align(ui_btnStart, LV_ALIGN_TOP_RIGHT);
    lv_obj_add_event_cb(ui_btnStart, start_btn_event_handler, LV_EVENT_CLICKED, this);

    ui_ButtonStartLabel = lv_label_create(ui_btnStart);
    lv_label_set_text(ui_ButtonStartLabel, "Start");
    lv_obj_center(ui_ButtonStartLabel);

    // Create 6 pin containers
    for (int i = 0; i < 6; ++i)
    {
        pinContainers[i] = lv_btn_create(ui_Widget);
        lv_obj_set_size(pinContainers[i], 180, 80);
        lv_obj_set_align(pinContainers[i], static_cast<lv_align_t>(LV_ALIGN_LEFT_MID + (i % 3)));
        lv_obj_set_y(pinContainers[i], (i / 3) ? 100 : -100);
        lv_obj_add_event_cb(pinContainers[i], pin_btn_event_handler, LV_EVENT_CLICKED, this);

        pinLabels[i] = lv_label_create(pinContainers[i]);
        lv_label_set_text_fmt(pinLabels[i], "Pin %d", i);
        lv_obj_center(pinLabels[i]);
    }

    // Title
    lv_obj_t *title = lv_label_create(ui_Widget);
    lv_label_set_text(title, "Main Menu");
    lv_obj_set_style_text_font(title, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_align(title, LV_ALIGN_TOP_MID, 0, 10);
}

void MainMenu::update_pin_label_text(int pinIndex) {
    BaseSensor* s = SensorManager::getInstance().getAssignedSensor(pinIndex);
    if (s) {
        lv_label_set_text_fmt(pinLabels[pinIndex], "%s", s->Type.c_str());
    } else {
        lv_label_set_text_fmt(pinLabels[pinIndex], "Pin %d", pinIndex);
    }
    lv_obj_center(pinLabels[pinIndex]);
}

void MainMenu::start_btn_event_handler(lv_event_t *e) {
    auto *self = static_cast<MainMenu *>(lv_event_get_user_data(e));
    if (!self) return;
    
    SensorManager& manager = SensorManager::getInstance();
    manager.sendPinsOnSerial();
    manager.setInitialized(true);
    manager.hideAllExceptFirst(true);
    
}

void MainMenu::pin_btn_event_handler(lv_event_t *e) {
    auto *self = static_cast<MainMenu *>(lv_event_get_user_data(e));
    if (!self) return;

    lv_obj_t *target = lv_event_get_target(e);
    for (int i = 0; i < 6; ++i) {
        if (self->pinContainers[i] == target) {
            SensorManager& manager = SensorManager::getInstance();
            manager.hideAllExceptFirst(false);
            manager.setActivePin(i);
            break;
        }
    }
}