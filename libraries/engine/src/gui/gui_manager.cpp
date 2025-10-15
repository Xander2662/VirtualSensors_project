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
#include "menu_gui.hpp"
#include "sensor_visualization_gui.hpp"
#include "sensor_wiki_gui.hpp"
#include "../helpers.hpp"

GuiManager::GuiManager(SensorManager &manager) 
    : sensorManager(manager), 
      menuGui(manager), 
      vizGui(manager),
      wikiGui(manager),
      currentState(GuiState::NONE),
      initialized(false) {
}

void GuiManager::init() {
    if (!sensorManager.isInitialized())
    {
        splashMessage("SensorManager not initialized. Cannot initialize GuiManager.\n");
        return;
    }
    

    if (initialized) {
        // logMessage("GuiManager already initialized\n");
        return;
    }
    
    try {
        logMessage("Initializing GUI Manager...\n");
        currentState = GuiState::NONE;
        
        // Initialize all GUI components
        menuGui.init();
        vizGui.init();
        wikiGui.init();
        
        initialized = true;
        logMessage("GUI Manager initialization completed!\n");
        
    } catch (const std::exception &e) {
        splashMessage("GUI Manager initialization failed: %s\n", e.what());
        initialized = false;
    }
}

void GuiManager::hideAllComponents() {
    if (menuGui.isInitialized()) {
        menuGui.hideMenu();
    }
    if (vizGui.isInitialized()) {
        vizGui.hideVisualization();
    }
    if (wikiGui.isInitialized()) {
        wikiGui.hideWiki();
    }
}

void GuiManager::showMenu() {
    if (!initialized) {
        // logMessage("GuiManager not initialized\n");
        return;
    }
    
    hideAllComponents();
    menuGui.showMenu();
    currentState = GuiState::MENU;
    // logMessage("Switched to MENU state\n");
}

void GuiManager::showVisualization() {
    if (!initialized) {
        // logMessage("GuiManager not initialized\n");
        return;
    }
    
    hideAllComponents();
    vizGui.showVisualization();
    vizGui.drawCurrentSensor(); // Refresh display
    currentState = GuiState::VISUALIZATION;
    // logMessage("Switched to VISUALIZATION state\n");
}

void GuiManager::showWiki() {
    if (!initialized) {
        // logMessage("GuiManager not initialized\n");
        return;
    }
    
    hideAllComponents();
    wikiGui.showWiki(menuGui.getActivePin());
    currentState = GuiState::WIKI;
    // logMessage("Switched to WIKI state\n");
}

void GuiManager::switchContent(GuiState targetState) {
    if (!initialized) {
        // logMessage("GuiManager not initialized\n");
        return;
    }
    
    // Don't switch if already in target state
    if (currentState == targetState) {
        // logMessage("Already in target state %d\n", static_cast<int>(targetState));
        return;
    }
    
    switch (targetState) {
        case GuiState::MENU:
            sensorManager.setRunning(false);
            showMenu();
            // logMessage("Switched content to MENU\n");
            break;
            
        case GuiState::VISUALIZATION:
            showVisualization();
            sensorManager.setRunning(true);
            // logMessage("Switched content to VISUALIZATION\n");
            break;
            
        case GuiState::WIKI:
            showWiki();
            // Don't change sensor running state for wiki
            // logMessage("Switched content to WIKI\n");
            break;

        case GuiState::NONE:
            hideAllComponents();
            sensorManager.setRunning(false);
            // logMessage("Switched content to NONE (all components hidden)\n");
            break;
            
        default:
            // logMessage("Unknown target GUI state %d, switching to MENU\n", static_cast<int>(targetState));
            sensorManager.setRunning(false);
            showMenu();
            break;
    }
}

void GuiManager::redraw() {
    if (!initialized) {
        // logMessage("GuiManager not initialized, cannot redraw\n");
        return;
    }
    
    switch (currentState) {
        case GuiState::VISUALIZATION:
            // Redraw current sensor in visualization mode
            if (vizGui.isInitialized()) {
                vizGui.drawCurrentSensor();
            }
            break;
            
        case GuiState::MENU:
            // Menu doesn't need periodic redraw - it's event-driven
            break;
            
        case GuiState::WIKI:
            // Wiki doesn't need periodic redraw - it's event-driven
            break;
            
        default:
            break;
    }
}

// All other functionality is accessed directly through the components
// GuiManager only handles initialization and screen switching, and redrawing of the current screen