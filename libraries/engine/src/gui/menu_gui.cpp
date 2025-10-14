/**
 * @file menu_gui.cpp
 * @brief Implementation of the MenuGui class
 *
 * This source file implements the MenuGui functionality for
 * menu visualization and sensor-to-pin assignment operations.
 *
 * @copyright 2025 MTA
 * @author Ing. Jiri Konecny, Ondřej Wrubel
 */

#include "menu_gui.hpp"
#include "../helpers.hpp"
#include "gui_callbacks.hpp"

MenuGui::MenuGui(SensorManager &manager) : sensorManager(manager), activePinIndex(-1) {
    // Initialize all GUI pointers to nullptr
    ui_MenuWidget = nullptr;
    ui_ButtonStartGroup = nullptr;
    ui_ButtonStartCornerTopLeft = nullptr;
    ui_ButtonStartCornerBottomRight = nullptr;
    ui_btnStart = nullptr;
    ui_ButtonStartLabel = nullptr;
    
    pinContainers.fill(nullptr);
    pinLabels.fill(nullptr);
}

void MenuGui::init() {
    if (initialized) return;
    
    try {
        logMessage("Initializing MenuGui...\n");
        buildMenu();
        updatePinLabels();
        initialized = true;
        logMessage("MenuGui initialization completed!\n");
    }
    catch (const std::exception &e) {
        logMessage("MenuGui initialization failed: %s\n", e.what());
        initialized = false;
    }
}

void MenuGui::buildMenu() {
    logMessage("\t>building menu...\n");
    
    // Main container widget
    ui_MenuWidget = lv_obj_create(lv_scr_act());
    lv_obj_remove_style_all(ui_MenuWidget);
    lv_obj_set_size(ui_MenuWidget, 760, 440);
    lv_obj_set_align(ui_MenuWidget, LV_ALIGN_CENTER);
    lv_obj_set_style_radius(ui_MenuWidget, 15, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_MenuWidget, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_MenuWidget, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_MenuWidget, 2, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Start button group
    ui_ButtonStartGroup = lv_obj_create(ui_MenuWidget);
    lv_obj_remove_style_all(ui_ButtonStartGroup);
    lv_obj_set_width(ui_ButtonStartGroup, 100);
    lv_obj_set_height(ui_ButtonStartGroup, 45);
    lv_obj_set_align(ui_ButtonStartGroup, LV_ALIGN_TOP_RIGHT);
    lv_obj_clear_flag(ui_ButtonStartGroup, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);

    // Start button decorative corners
    ui_ButtonStartCornerTopLeft = lv_obj_create(ui_ButtonStartGroup);
    lv_obj_remove_style_all(ui_ButtonStartCornerTopLeft);
    lv_obj_set_width(ui_ButtonStartCornerTopLeft, 20);
    lv_obj_set_height(ui_ButtonStartCornerTopLeft, 20);
    lv_obj_clear_flag(ui_ButtonStartCornerTopLeft, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(ui_ButtonStartCornerTopLeft, lv_color_hex(0x009BFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ButtonStartCornerTopLeft, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui_ButtonStartCornerTopLeft, false, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_ButtonStartCornerBottomRight = lv_obj_create(ui_ButtonStartGroup);
    lv_obj_remove_style_all(ui_ButtonStartCornerBottomRight);
    lv_obj_set_width(ui_ButtonStartCornerBottomRight, 20);
    lv_obj_set_height(ui_ButtonStartCornerBottomRight, 20);
    lv_obj_set_align(ui_ButtonStartCornerBottomRight, LV_ALIGN_BOTTOM_RIGHT);
    lv_obj_clear_flag(ui_ButtonStartCornerBottomRight, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(ui_ButtonStartCornerBottomRight, lv_color_hex(0x009BFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ButtonStartCornerBottomRight, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui_ButtonStartCornerBottomRight, false, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Start button
    ui_btnStart = lv_btn_create(ui_ButtonStartGroup);
    lv_obj_set_width(ui_btnStart, 100);
    lv_obj_set_height(ui_btnStart, 45);
    lv_obj_add_flag(ui_btnStart, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_obj_clear_flag(ui_btnStart, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE |
                      LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
                      LV_OBJ_FLAG_SCROLL_CHAIN);
    lv_obj_set_style_clip_corner(ui_btnStart, false, LV_PART_MAIN | LV_STATE_DEFAULT);
    
    // Start button event handler
    lv_obj_add_event_cb(ui_btnStart, [](lv_event_t *e) {
        auto self = static_cast<MenuGui*>(lv_event_get_user_data(e));
        self->handleStartButtonClick();
    }, LV_EVENT_CLICKED, this);

    // Start button label
    ui_ButtonStartLabel = lv_label_create(ui_btnStart);
    lv_obj_set_width(ui_ButtonStartLabel, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_ButtonStartLabel, LV_SIZE_CONTENT);
    lv_obj_set_align(ui_ButtonStartLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_ButtonStartLabel, "Start");
    lv_obj_set_style_text_font(ui_ButtonStartLabel, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Pin container alignment positions
    static const lv_align_t align_map[3] = {
        LV_ALIGN_LEFT_MID,
        LV_ALIGN_CENTER,
        LV_ALIGN_RIGHT_MID
    };
    
    // Create pin containers
    for (int i = 0; i < NUM_PINS; ++i) {
        pinContainers[i] = lv_btn_create(ui_MenuWidget);
        lv_obj_set_size(pinContainers[i], 180, 80);
        lv_obj_set_align(pinContainers[i], align_map[i % 3]);
        lv_obj_set_y(pinContainers[i], (i < 3) ? -100 : 100);

        // Pin container event handler
        lv_obj_add_event_cb(pinContainers[i], [](lv_event_t *e) {
            auto self = static_cast<MenuGui*>(lv_event_get_user_data(e));
            int index = (intptr_t)lv_obj_get_user_data(lv_event_get_target(e));
            self->handlePinClick(index);
        }, LV_EVENT_CLICKED, this);

        // Store pin index as user data
        lv_obj_set_user_data(pinContainers[i], (void*)(intptr_t)i);

        // Pin labels
        pinLabels[i] = lv_label_create(pinContainers[i]);
        lv_label_set_text_fmt(pinLabels[i], "Pin %d", i + 1);
        lv_obj_center(pinLabels[i]);
    }
    
    // Title
    lv_obj_t *title = lv_label_create(ui_MenuWidget);
    lv_label_set_text(title, "Assign Sensors to Pins");
    lv_obj_set_style_text_font(title, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_align(title, LV_ALIGN_TOP_MID, 0, 10);
    
    logMessage("\t>menu built successfully!\n");
}

void MenuGui::showMenu() {
    if (!initialized || !ui_MenuWidget) return;
    
    lv_obj_clear_flag(ui_MenuWidget, LV_OBJ_FLAG_HIDDEN);
    updatePinLabels();
    updatePinVisualStates();
    logMessage("Showing menu GUI\n");
}

void MenuGui::hideMenu() {
    if (!initialized || !ui_MenuWidget) return;
    
    lv_obj_add_flag(ui_MenuWidget, LV_OBJ_FLAG_HIDDEN);
    logMessage("Hiding menu GUI\n");
}

void MenuGui::updatePinLabels() {
    for (int i = 0; i < NUM_PINS; i++) {
        if (!pinLabels[i]) continue;
        
        BaseSensor* sensor = sensorManager.getAssignedSensor(i);
        if (sensor) {
            lv_label_set_text(pinLabels[i], sensor->UID.c_str());
        } else {
            lv_label_set_text_fmt(pinLabels[i], "Pin %d", i + 1);
        }
    }
}

void MenuGui::updatePinVisualStates() {
    for (int i = 0; i < NUM_PINS; i++) {
        if (!pinContainers[i]) continue;
        
        bool isAssigned = isPinAssigned(i);
        bool isActive = (i == activePinIndex);
        
        // Set background color based on state
        if (isActive) {
            // Active pin - highlighted
            lv_obj_set_style_bg_color(pinContainers[i], lv_color_hex(0x009BFF), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(pinContainers[i], 255, LV_PART_MAIN | LV_STATE_DEFAULT);
        } else if (isAssigned) {
            // Assigned but not active - green
            lv_obj_set_style_bg_color(pinContainers[i], lv_color_hex(0x37F006), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(pinContainers[i], 200, LV_PART_MAIN | LV_STATE_DEFAULT);
        } else {
            // Not assigned - default gray
            lv_obj_set_style_bg_color(pinContainers[i], lv_color_hex(0xE0E0E0), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(pinContainers[i], 255, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        
        // Set text color for better contrast
        if (isActive) {
            lv_obj_set_style_text_color(pinLabels[i], lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
        } else {
            lv_obj_set_style_text_color(pinLabels[i], lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        
        // Add border for active pin
        if (isActive) {
            lv_obj_set_style_border_width(pinContainers[i], 3, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(pinContainers[i], lv_color_hex(0x0066CC), LV_PART_MAIN | LV_STATE_DEFAULT);
        } else {
            lv_obj_set_style_border_width(pinContainers[i], 1, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(pinContainers[i], lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        
        logMessage("Pin %d - Assigned: %s, Active: %s\n", 
                  i, isAssigned ? "Yes" : "No", isActive ? "Yes" : "No");
    }
}

void MenuGui::setActivePin(int pinIndex) {
    if (pinIndex < -1 || pinIndex >= NUM_PINS) {
        logMessage("Invalid pin index: %d\n", pinIndex);
        return;
    }
    
    activePinIndex = pinIndex;
    updatePinVisualStates();
    
    logMessage("Active pin set to: %d\n", activePinIndex);
}

bool MenuGui::assignCurrentSensorToActivePin() {
    if (activePinIndex < 0 || activePinIndex >= NUM_PINS) {
        logMessage("No active pin selected for assignment\n");
        return false;
    }
    
    BaseSensor* currentSensor = sensorManager.getCurrentSensor();
    if (!currentSensor) {
        logMessage("No current sensor to assign\n");
        return false;
    }
    
    bool success = sensorManager.assignSensorToPin(currentSensor, activePinIndex);
    if (success) {
        updatePinLabels();
        updatePinVisualStates();
        logMessage("Assigned sensor %s to pin %d\n", currentSensor->UID.c_str(), activePinIndex);
    } else {
        logMessage("Failed to assign sensor %s to pin %d\n", currentSensor->UID.c_str(), activePinIndex);
    }
    
    return success;
}

bool MenuGui::unassignSensorFromActivePin() {
    if (activePinIndex < 0 || activePinIndex >= NUM_PINS) {
        logMessage("No active pin selected for unassignment\n");
        return false;
    }
    
    bool success = sensorManager.unassignSensorFromPin(activePinIndex);
    if (success) {
        updatePinLabels();
        updatePinVisualStates();
        logMessage("Unassigned sensor from pin %d\n", activePinIndex);
    } else {
        logMessage("Failed to unassign sensor from pin %d\n", activePinIndex);
    }
    
    return success;
}

bool MenuGui::isPinAssigned(int pinIndex) const {
    if (pinIndex < 0 || pinIndex >= NUM_PINS) return false;
    return sensorManager.getAssignedSensor(pinIndex) != nullptr;
}

BaseSensor* MenuGui::getAssignedSensor(int pinIndex) const {
    if (pinIndex < 0 || pinIndex >= NUM_PINS) return nullptr;
    return sensorManager.getAssignedSensor(pinIndex);
}

void MenuGui::handleStartButtonClick() {
    // Stop sensor manager to allow configuration changes
    sensorManager.setRunning(false);

    // Check if any sensors are assigned to pins
    const auto& pinMap = sensorManager.getPinMap();
    size_t count = 0;
    for (auto *sensor : pinMap) {
        if (sensor) count++;
    }

    if (count == 0) {
        logMessage("No sensors assigned to pins!\n");
        // TODO: Show error message to user (splash message)
        return;
    }

    // Connect all assigned sensors to pins
    if (!sensorManager.connect()) {
        logMessage("Error during sensor assignment!\n");
        // TODO: Show error message to user (splash message)
        return;
    }

    // Start sensor operations
    sensorManager.setRunning(true);
    logMessage("Starting sensor operations with %zu sensors assigned\n", count);
    
    // Switch to visualization screen
    switchToVisualization();
}

void MenuGui::handlePinClick(int pinIndex) {
    logMessage("Pin %d clicked\n", pinIndex);
    
    if (pinIndex < 0 || pinIndex >= NUM_PINS) {
        logMessage("Invalid pin index: %d\n", pinIndex);
        return;
    }
    
    // Set this pin as active
    setActivePin(pinIndex);
    
    // Toggle assignment if we have a current sensor
    BaseSensor* currentSensor = sensorManager.getCurrentSensor();
    if (currentSensor) {
        if (isPinAssigned(pinIndex)) {
            // Pin is assigned, unassign it
            unassignSensorFromActivePin();
        } else {
            // Pin is not assigned, assign current sensor to it
            assignCurrentSensorToActivePin();
        }
    } else {
        logMessage("No current sensor available for assignment\n");
    }
}

int MenuGui::getIndexFromContainer(lv_obj_t* container) {
    for (int i = 0; i < NUM_PINS; i++) {
        if (pinContainers[i] == container) {
            return i;
        }
    }
    return -1;
}