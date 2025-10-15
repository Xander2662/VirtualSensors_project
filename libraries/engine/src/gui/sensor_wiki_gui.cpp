/**
 * @file sensor_wiki_gui.cpp
 * @brief Implementation of the SensorWikiGui class
 *
 * This source file implements the sensor wiki functionality for
 * displaying sensor information and handling sensor selection.
 *
 * @copyright 2025 MTA
 * @author Ing. Jiri Konecny
 */

#include "sensor_wiki_gui.hpp"
#include "../helpers.hpp"

SensorWikiGui::SensorWikiGui(SensorManager& sensorManager) 
    : sensorManager(sensorManager) {
    // Initialize all GUI pointers to nullptr
    ui_WikiWidget = nullptr;
    ui_SensorList = nullptr;
    ui_SensorInfo = nullptr;
    ui_SensorTitle = nullptr;
    ui_SensorDescription = nullptr;
    ui_SensorSpecs = nullptr;
    ui_SelectButton = nullptr;
    ui_BackButton = nullptr;
    ui_PrevButton = nullptr;
    ui_NextButton = nullptr;
}

void SensorWikiGui::init() {
    if (initialized) return;
    
    try {
        // logMessage("Initializing SensorWikiGui...\n");
        buildWikiGui();
        updateSensorInfo();
        initialized = true;
        // logMessage("SensorWikiGui initialization completed!\n");
    }
    catch (const std::exception& e) {
        // logMessage("SensorWikiGui initialization failed: %s\n", e.what());
        initialized = false;
    }
}

void SensorWikiGui::buildWikiGui() {
    // logMessage("\t>building sensor wiki gui...\n");
    
    // Main wiki container
    ui_WikiWidget = lv_obj_create(lv_scr_act());
    lv_obj_remove_style_all(ui_WikiWidget);
    lv_obj_set_size(ui_WikiWidget, 760, 440);
    lv_obj_set_align(ui_WikiWidget, LV_ALIGN_CENTER);
    lv_obj_set_style_radius(ui_WikiWidget, 15, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_WikiWidget, lv_color_hex(0xF0F0F0), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_WikiWidget, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_WikiWidget, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_flag(ui_WikiWidget, LV_OBJ_FLAG_HIDDEN);
    
    // Sensor information panel
    ui_SensorInfo = lv_obj_create(ui_WikiWidget);
    lv_obj_set_size(ui_SensorInfo, 500, 380);
    lv_obj_set_pos(ui_SensorInfo, 10, 10);
    lv_obj_set_style_bg_color(ui_SensorInfo, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_SensorInfo, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui_SensorInfo, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    
    // Sensor title
    ui_SensorTitle = lv_label_create(ui_SensorInfo);
    lv_obj_set_size(ui_SensorTitle, 480, 40);
    lv_obj_set_pos(ui_SensorTitle, 10, 10);
    lv_label_set_text(ui_SensorTitle, "Sensor Name");
    lv_obj_set_style_text_font(ui_SensorTitle, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui_SensorTitle, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    // Sensor description
    ui_SensorDescription = lv_textarea_create(ui_SensorInfo);
    lv_obj_set_size(ui_SensorDescription, 480, 180);
    lv_obj_set_pos(ui_SensorDescription, 10, 60);
    lv_textarea_set_text(ui_SensorDescription, "Sensor description will appear here...");
    lv_obj_add_flag(ui_SensorDescription, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_obj_clear_flag(ui_SensorDescription, LV_OBJ_FLAG_CLICKABLE);
    
    // Sensor specifications
    ui_SensorSpecs = lv_textarea_create(ui_SensorInfo);
    lv_obj_set_size(ui_SensorSpecs, 480, 120);
    lv_obj_set_pos(ui_SensorSpecs, 10, 250);
    lv_textarea_set_text(ui_SensorSpecs, "Specifications will appear here...");
    lv_obj_add_flag(ui_SensorSpecs, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_obj_clear_flag(ui_SensorSpecs, LV_OBJ_FLAG_CLICKABLE);
    
    // Control panel
    lv_obj_t* controlPanel = lv_obj_create(ui_WikiWidget);
    lv_obj_set_size(controlPanel, 230, 380);
    lv_obj_set_pos(controlPanel, 520, 10);
    lv_obj_set_style_bg_color(controlPanel, lv_color_hex(0xE0E0E0), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(controlPanel, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(controlPanel, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    
    // Navigation buttons
    ui_PrevButton = lv_btn_create(controlPanel);
    lv_obj_set_size(ui_PrevButton, 90, 40);
    lv_obj_set_pos(ui_PrevButton, 10, 20);
    lv_obj_t* prevLabel = lv_label_create(ui_PrevButton);
    lv_label_set_text(prevLabel, "< Prev");
    lv_obj_center(prevLabel);
    lv_obj_add_event_cb(ui_PrevButton, [](lv_event_t* e) {
        auto self = static_cast<SensorWikiGui*>(lv_event_get_user_data(e));
        self->navigateSensor(-1);
    }, LV_EVENT_CLICKED, this);
    
    ui_NextButton = lv_btn_create(controlPanel);
    lv_obj_set_size(ui_NextButton, 90, 40);
    lv_obj_set_pos(ui_NextButton, 130, 20);
    lv_obj_t* nextLabel = lv_label_create(ui_NextButton);
    lv_label_set_text(nextLabel, "Next >");
    lv_obj_center(nextLabel);
    lv_obj_add_event_cb(ui_NextButton, [](lv_event_t* e) {
        auto self = static_cast<SensorWikiGui*>(lv_event_get_user_data(e));
        self->navigateSensor(1);
    }, LV_EVENT_CLICKED, this);
    
    // Select button
    ui_SelectButton = lv_btn_create(controlPanel);
    lv_obj_set_size(ui_SelectButton, 210, 50);
    lv_obj_set_pos(ui_SelectButton, 10, 80);
    lv_obj_set_style_bg_color(ui_SelectButton, lv_color_hex(0x00AA00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_t* selectLabel = lv_label_create(ui_SelectButton);
    lv_label_set_text(selectLabel, "SELECT SENSOR");
    lv_obj_center(selectLabel);
    lv_obj_set_style_text_color(selectLabel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_event_cb(ui_SelectButton, [](lv_event_t* e) {
        auto self = static_cast<SensorWikiGui*>(lv_event_get_user_data(e));
        self->handleSelectButtonClick();
    }, LV_EVENT_CLICKED, this);
    
    // Back button
    ui_BackButton = lv_btn_create(controlPanel);
    lv_obj_set_size(ui_BackButton, 210, 40);
    lv_obj_set_pos(ui_BackButton, 10, 330);
    lv_obj_set_style_bg_color(ui_BackButton, lv_color_hex(0x808080), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_t* backLabel = lv_label_create(ui_BackButton);
    lv_label_set_text(backLabel, "BACK TO MENU");
    lv_obj_center(backLabel);
    lv_obj_set_style_text_color(backLabel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_event_cb(ui_BackButton, [](lv_event_t* e) {
        auto self = static_cast<SensorWikiGui*>(lv_event_get_user_data(e));
        self->handleBackButtonClick();
    }, LV_EVENT_CLICKED, this);
    
    // Sensor list (simple for now)
    ui_SensorList = lv_list_create(controlPanel);
    lv_obj_set_size(ui_SensorList, 210, 180);
    lv_obj_set_pos(ui_SensorList, 10, 140);
}

void SensorWikiGui::updateSensorInfo() {
    BaseSensor* sensor = getSelectedSensor();
    if (!sensor) {
        lv_label_set_text(ui_SensorTitle, "No Sensor Selected");
        lv_textarea_set_text(ui_SensorDescription, "No sensor available for display.");
        lv_textarea_set_text(ui_SensorSpecs, "No specifications available.");
        return;
    }
    
    // Update title
    lv_label_set_text(ui_SensorTitle, sensor->getName().c_str());
    
    // Update description
    std::string description = getSensorInfoText(sensor);
    lv_textarea_set_text(ui_SensorDescription, description.c_str());
    
    // Update specifications
    std::string specs = getSensorSpecsText(sensor);
    lv_textarea_set_text(ui_SensorSpecs, specs.c_str());
}

std::string SensorWikiGui::getSensorInfoText(BaseSensor* sensor) {
    if (!sensor) return "No sensor information available.";
    
    std::string info = "Type: " + sensor->getTypeName() + "\n\n";
    info += "Description: " + sensor->getDescription() + "\n\n";

    return info;
}

std::string SensorWikiGui::getSensorSpecsText(BaseSensor* sensor) {
    if (!sensor) return "No specifications available.";
    
    std::string specs = "Technical Specifications:\n\n";
    specs += "Sensor ID: " + sensor->getId() + "\n";
    specs += "Type: " + sensor->getTypeName() + "\n";
    // Loops values and configs
    specs += "Values:\n";
    for(const auto& [key, param] : sensor->getValues()) {
        specs += "\t" + key + ": " + param.Value + " (" + param.Unit + ")\n";
    }
    specs += "\nConfigurations:\n";
    for(const auto& [key, param] : sensor->getConfigs()) {
        specs += "\t" + key + ": " + param.Value + " (" + param.Unit + ")\n";
    }

    
    return specs;
}

void SensorWikiGui::showWiki(int pinIndex) {
    if (!initialized) return;
    
    activePinIndex = pinIndex;
    updateSensorInfo();
    lv_obj_clear_flag(ui_WikiWidget, LV_OBJ_FLAG_HIDDEN);
    
    // logMessage("Showing sensor wiki for pin %d\n", pinIndex);
}

void SensorWikiGui::hideWiki() {
    if (!initialized) return;
    
    lv_obj_add_flag(ui_WikiWidget, LV_OBJ_FLAG_HIDDEN);
    activePinIndex = -1;
}

BaseSensor* SensorWikiGui::getSelectedSensor() {
    const auto& sensors = sensorManager.getSensors();
    if (sensors.empty() || selectedSensorIndex >= static_cast<int>(sensors.size())) {
        return nullptr;
    }
    return sensors[selectedSensorIndex];
}

void SensorWikiGui::setSelectedSensor(int index) {
    const auto& sensors = sensorManager.getSensors();
    if (index >= 0 && index < static_cast<int>(sensors.size())) {
        selectedSensorIndex = index;
        updateSensorInfo();
    }
}

void SensorWikiGui::navigateSensor(int direction) {
    const auto& sensors = sensorManager.getSensors();
    if (sensors.empty()) return;
    
    selectedSensorIndex += direction;
    if (selectedSensorIndex < 0) {
        selectedSensorIndex = sensors.size() - 1;
    } else if (selectedSensorIndex >= static_cast<int>(sensors.size())) {
        selectedSensorIndex = 0;
    }
    
    updateSensorInfo();
}

void SensorWikiGui::handleSelectButtonClick() {
    BaseSensor* sensor = getSelectedSensor();
    if (!sensor || activePinIndex < 0) {
        // logMessage("Cannot select sensor: no sensor or no active pin\n");
        return;
    }
    
    // Assign sensor to pin through sensor manager
    bool success = sensorManager.assignSensorToPin(sensor, activePinIndex);
    if (success) {
        // logMessage("Sensor %s assigned to pin %d\n", sensor->getName().c_str(), activePinIndex);
        // Switch back to menu
        handleBackButtonClick();
    } else {
        // logMessage("Failed to assign sensor to pin\n");
    }
}

void SensorWikiGui::handleBackButtonClick() {
    hideWiki();
    switchToMenu();
}