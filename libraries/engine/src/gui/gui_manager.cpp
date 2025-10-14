/**
 * @file gui_manager.cpp
 * @brief Implementation of the GuiManager class
 *
 * This source file implements the GuiManager functionality for
 * coordinating between MenuGui and SensorVisualizationGui components.
 *
 * @copyright 2025 MTA
 * @author Ing. Jiri Konecny, Ondřej Wrubel
 */

#include "gui_manager.hpp"
#include "../helpers.hpp"

GuiManager::GuiManager(SensorManager &manager) 
    : sensorManager(manager), 
      menuGui(manager), 
      vizGui(manager),
      currentState(GuiState::MENU),
      initialized(false) {
}

void GuiManager::init() {
    if (!sensorManager.isInitialized())
    {
        splashMessage("SensorManager not initialized. Cannot initialize GuiManager.\n");
        return;
    }
    

    if (initialized) {
        logMessage("GuiManager already initialized\n");
        return;
    }
    
    try {
        logMessage("Initializing GuiManager...\n");
        
        // Initialize both GUI components
        menuGui.init();
        vizGui.init();
        
        // Start in menu state
        currentState = GuiState::MENU;
        showMenu();
        
        initialized = true;
        logMessage("GuiManager initialization completed!\n");
        
    } catch (const std::exception &e) {
        logMessage("GuiManager initialization failed: %s\n", e.what());
        initialized = false;
        throw;
    }
}

void GuiManager::hideAllComponents() {
    if (menuGui.isInitialized()) {
        menuGui.hideMenu();
    }
    if (vizGui.isInitialized()) {
        vizGui.hideVisualization();
        vizGui.hideWiki();
    }
}

void GuiManager::showMenu() {
    if (!initialized) {
        logMessage("GuiManager not initialized\n");
        return;
    }
    
    hideAllComponents();
    menuGui.showMenu();
    currentState = GuiState::MENU;
    logMessage("Switched to MENU state\n");
}

void GuiManager::showVisualization() {
    if (!initialized) {
        logMessage("GuiManager not initialized\n");
        return;
    }
    
    hideAllComponents();
    vizGui.showVisualization();
    vizGui.drawCurrentSensor(); // Refresh display
    currentState = GuiState::VISUALIZATION;
    logMessage("Switched to VISUALIZATION state\n");
}

void GuiManager::showWiki() {
    if (!initialized) {
        logMessage("GuiManager not initialized\n");
        return;
    }
    
    hideAllComponents();
    vizGui.showWiki();
    currentState = GuiState::WIKI;
    logMessage("Switched to WIKI state\n");
}

// All other functionality is accessed directly through the components
// GuiManager only handles initialization and screen switching