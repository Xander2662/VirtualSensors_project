/**
 * @file main_menu.hpp
 * @brief Declaration of the MainMenu widget
 *
 * This header defines the MainMenu class which provides
 * a widget with a Start button and 6 pin selection buttons.
 *
 * @copyright 2025 MTA
 * @author Ondřej Wrubel
 */

#ifndef MAIN_MENU_HPP
#define MAIN_MENU_HPP

#include "lvgl.h"
#include <array>

class MainMenu {
public:
    static MainMenu& getInstance();

    void show();
    void hide();
    lv_obj_t* getWidget() const { return ui_Widget; }
    void update_pin_label_text(int pinIndex);


private:
    MainMenu(); 
    ~MainMenu() = default;

    MainMenu(const MainMenu&) = delete;
    MainMenu& operator=(const MainMenu&) = delete;

    lv_obj_t* ui_Widget;
    lv_obj_t* ui_btnStart;
    lv_obj_t* ui_ButtonStartLabel;
    std::array<lv_obj_t*, 6> pinContainers;
    std::array<lv_obj_t*, 6> pinLabels;

    static void start_btn_event_handler(lv_event_t* e);
    static void pin_btn_event_handler(lv_event_t* e);
    void build();
};

#endif

