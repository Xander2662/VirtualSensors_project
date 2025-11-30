/**
 * @file sensor_visualization_gui.cpp
 * @brief Implementation of the DataBundlesGui class
 *
 * This source file implements the DataBundlesGui functionality for
 * active sensor visualization, data display, and navigation.
 *
 * @copyright 2025 MTA
 * @author Ing. Jiri Konecny, Ondřej Wrubel
 */

#include "data_bundles_gui.hpp"
#include "../helpers.hpp"
#include "./images/ui_images.h"

DataBundlesGui::DataBundlesGui()
{
ui_DataBundlesWidget = nullptr;
ui_DataBundlePageWatcher = nullptr;
for (int i = 0; i < 5; ++i) 
    ui_DataBundlePageWatcherCell[i] = nullptr;
for (int i = 0; i < 6; ++i) {
    ui_DataBundle[i] = nullptr;
    ui_DataBundleHeaderGroup[i] = nullptr;
    ui_DataBundleHeaderCornerBottomLeft[i] = nullptr;
    ui_DataBundleHeaderCornerBottomRight[i] = nullptr;
    ui_DataBundleHeader[i] = nullptr;
    ui_DataBundleHeaderLabel[i] = nullptr;
    ui_DataBundleChart[i] = nullptr;
    ui_DataBundleChart_series_1[i] = nullptr;
    ui_DataBundleFooterGroup[i] = nullptr;
    ui_DataBundleFooterBridge[i] = nullptr;
    ui_DataBundleFooterBridgeFill[i] = nullptr;
    ui_DataBundleFooterTimerGroup[i] = nullptr;
    ui_DataBundleFooterDateCornerTopLeft[i] = nullptr;
    ui_DataBundleFooterDateCornerTopRight[i] = nullptr;
    ui_DataBundleFooterDate[i] = nullptr;
    ui_DataBundleFooterLabelDate[i] = nullptr;
    ui_DataBundleFooterLabelTime[i] = nullptr;
    ui_DataBundleFooterButtonsGroup[i] = nullptr;
    ui_DataBundleFooterButtonsCornerTopLeft[i] = nullptr;
    ui_DataBundleFooterButtonsCornerTopRight[i] = nullptr;
    ui_DataBundleFooterButtons[i] = nullptr;
    ui_DataBundleFooterButtonExport[i] = nullptr;
    ui_DataBundleFooterButtonExportImage[i] = nullptr;
    ui_DataBundleFooterButtonClear[i] = nullptr;
    ui_DataBundleFooterButtonClearImage[i] = nullptr;
}
ui_LogoGroup = nullptr;
ui_LogoCornerBottomLeft = nullptr;
ui_LogoCornerFillBottomLeft = nullptr;
ui_LogoCornerBottomRight = nullptr;
ui_LogoCornerFillBottomRight = nullptr;
ui_LogoOutlay = nullptr;
ui_LogoImage = nullptr;
}

void DataBundlesGui::init()
{
    if (initialized)
        return;

    try
    {
        // // logMessage("Initializing DataBundlesGui...\n");
        constructDataBundles();
        initialized = true;
        // // logMessage("DataBundlesGui initialization completed!\n");
    }
    catch (const std::exception &e)
    {
        // // logMessage("DataBundlesGui initialization failed: %s\n", e.what());
        initialized = false;
    }
}

void DataBundlesGui::constructDataBundles()
{
    // 1. Initialize pointers to NULL for safety
    for(int i = 0; i < 6; i++) {
        ui_DataBundle[i] = NULL;
    }

    // 2. Main Container Widget (The Frame)
    ui_DataBundlesWidget = lv_obj_create(lv_scr_act()); 
    lv_obj_remove_style_all(ui_DataBundlesWidget);
    lv_obj_set_width(ui_DataBundlesWidget, 760);
    lv_obj_set_height(ui_DataBundlesWidget, 440);
    lv_obj_set_align(ui_DataBundlesWidget, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_DataBundlesWidget, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_radius(ui_DataBundlesWidget, 15, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_DataBundlesWidget, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_DataBundlesWidget, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_DataBundlesWidget, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_DataBundlesWidget, 1, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Title Label
    lv_obj_t* title_label = lv_label_create(ui_DataBundlesWidget);
    lv_label_set_text(title_label, "Data Bundles");
    lv_obj_set_y(title_label, 10);
    lv_obj_set_align(title_label, LV_ALIGN_TOP_MID);
    lv_obj_set_style_text_font(title_label, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);

    // 3. Page Watcher (Static UI elements)
    ui_DataBundlePageWatcher = lv_obj_create(ui_DataBundlesWidget);
    lv_obj_remove_style_all(ui_DataBundlePageWatcher);
    lv_obj_set_size(ui_DataBundlePageWatcher, 80, 15);
    lv_obj_set_y(ui_DataBundlePageWatcher, -35);
    lv_obj_set_align(ui_DataBundlePageWatcher, LV_ALIGN_BOTTOM_MID);

    // Create the 5 indicator dots (You can hide/show these later if needed)
    for(int i = 0; i < 5; i++) {
        ui_DataBundlePageWatcherCell[i] = lv_obj_create(ui_DataBundlePageWatcher);
        lv_obj_remove_style_all(ui_DataBundlePageWatcherCell[i]);
        lv_obj_set_size(ui_DataBundlePageWatcherCell[i], 12, 12);
        lv_obj_set_x(ui_DataBundlePageWatcherCell[i], (i - 2) * 15);
        lv_obj_set_align(ui_DataBundlePageWatcherCell[i], LV_ALIGN_BOTTOM_MID);
        lv_obj_set_style_radius(ui_DataBundlePageWatcherCell[i], 100, LV_PART_MAIN);
        lv_obj_set_style_border_width(ui_DataBundlePageWatcherCell[i], 2, LV_PART_MAIN);
        lv_obj_set_style_bg_color(ui_DataBundlePageWatcherCell[i], lv_color_hex(0xFFFFFF), LV_PART_MAIN);
        lv_obj_set_style_border_color(ui_DataBundlePageWatcherCell[i], lv_color_hex(0x009BFF), LV_PART_MAIN);
    }   
}   

void DataBundlesGui::createDataBundle(int i)
{
    // 1. Safety Checks
    if (i < 0 || i >= 6) return;          // Out of bounds
    if (ui_DataBundle[i] != NULL) return; // Already exists

    // 2. Determine Position based on Index
    int x_pos = 0;
    int y_pos = 0;

    switch(i) {
        case 0: x_pos = -250; y_pos = -85; break; // Top Left
        case 1: x_pos = 0;    y_pos = -85; break; // Top Mid
        case 2: x_pos = 250;  y_pos = -85; break; // Top Right
        case 3: x_pos = -250; y_pos = 85;  break; // Bottom Left
        case 4: x_pos = 0;    y_pos = 85;  break; // Bottom Mid
        case 5: x_pos = 250;  y_pos = 85;  break; // Bottom Right
    }

    // 3. Create Main Bundle Container
    ui_DataBundle[i] = lv_obj_create(ui_DataBundlesWidget);
    lv_obj_remove_style_all(ui_DataBundle[i]);
    lv_obj_set_size(ui_DataBundle[i], 200, 160);
    
    // Apply the calculated position
    lv_obj_set_align(ui_DataBundle[i], LV_ALIGN_CENTER);
    lv_obj_set_pos(ui_DataBundle[i], x_pos, y_pos);

    // --- Header Group ---
    ui_DataBundleHeaderGroup[i] = lv_obj_create(ui_DataBundle[i]);
    lv_obj_remove_style_all(ui_DataBundleHeaderGroup[i]);
    lv_obj_set_size(ui_DataBundleHeaderGroup[i], 200, 20);
    lv_obj_set_align(ui_DataBundleHeaderGroup[i], LV_ALIGN_TOP_MID);

    ui_DataBundleHeaderCornerBottomLeft[i] = lv_obj_create(ui_DataBundleHeaderGroup[i]);
    lv_obj_remove_style_all(ui_DataBundleHeaderCornerBottomLeft[i]);
    lv_obj_set_size(ui_DataBundleHeaderCornerBottomLeft[i], 10, 10);
    lv_obj_set_align(ui_DataBundleHeaderCornerBottomLeft[i], LV_ALIGN_BOTTOM_LEFT);
    lv_obj_set_style_bg_color(ui_DataBundleHeaderCornerBottomLeft[i], lv_color_hex(0x007CCC), LV_PART_MAIN);

    ui_DataBundleHeaderCornerBottomRight[i] = lv_obj_create(ui_DataBundleHeaderGroup[i]);
    lv_obj_remove_style_all(ui_DataBundleHeaderCornerBottomRight[i]);
    lv_obj_set_size(ui_DataBundleHeaderCornerBottomRight[i], 10, 10);
    lv_obj_set_align(ui_DataBundleHeaderCornerBottomRight[i], LV_ALIGN_BOTTOM_RIGHT);
    lv_obj_set_style_bg_color(ui_DataBundleHeaderCornerBottomRight[i], lv_color_hex(0x007CCC), LV_PART_MAIN);

    ui_DataBundleHeader[i] = lv_obj_create(ui_DataBundleHeaderGroup[i]);
    lv_obj_remove_style_all(ui_DataBundleHeader[i]);
    lv_obj_set_size(ui_DataBundleHeader[i], 200, 20);
    lv_obj_set_align(ui_DataBundleHeader[i], LV_ALIGN_TOP_MID);
    lv_obj_set_style_radius(ui_DataBundleHeader[i], 10, LV_PART_MAIN);
    lv_obj_set_style_bg_color(ui_DataBundleHeader[i], lv_color_hex(0x007CCC), LV_PART_MAIN);

    ui_DataBundleHeaderLabel[i] = lv_label_create(ui_DataBundleHeader[i]);
    lv_obj_set_align(ui_DataBundleHeaderLabel[i], LV_ALIGN_CENTER);
    lv_label_set_text(ui_DataBundleHeaderLabel[i], "Bundle Title"); 
    lv_obj_set_style_text_font(ui_DataBundleHeaderLabel[i], &lv_font_montserrat_12, LV_PART_MAIN);

    // --- Chart ---
    ui_DataBundleChart[i] = lv_chart_create(ui_DataBundle[i]);
    lv_obj_set_size(ui_DataBundleChart[i], 200, 110);
    lv_obj_set_y(ui_DataBundleChart[i], -4);
    lv_obj_set_align(ui_DataBundleChart[i], LV_ALIGN_CENTER);
    lv_chart_set_type(ui_DataBundleChart[i], LV_CHART_TYPE_LINE);
    lv_chart_set_div_line_count(ui_DataBundleChart[i], 5, 10);
    lv_obj_set_style_radius(ui_DataBundleChart[i], 0, LV_PART_MAIN);
    lv_obj_set_style_bg_color(ui_DataBundleChart[i], lv_color_hex(0xFFFFFF), LV_PART_MAIN);
    
    ui_DataBundleChart_series_1[i] = lv_chart_add_series(ui_DataBundleChart[i], lv_color_hex(0xFF8200), LV_CHART_AXIS_PRIMARY_Y);

    // --- Footer Group ---
    ui_DataBundleFooterGroup[i] = lv_obj_create(ui_DataBundle[i]);
    lv_obj_remove_style_all(ui_DataBundleFooterGroup[i]);
    lv_obj_set_size(ui_DataBundleFooterGroup[i], 200, 30);
    lv_obj_set_align(ui_DataBundleFooterGroup[i], LV_ALIGN_BOTTOM_MID);

    ui_DataBundleFooterBridge[i] = lv_obj_create(ui_DataBundleFooterGroup[i]);
    lv_obj_remove_style_all(ui_DataBundleFooterBridge[i]);
    lv_obj_set_size(ui_DataBundleFooterBridge[i], 40, 15);
    lv_obj_set_pos(ui_DataBundleFooterBridge[i], 25, -7);
    lv_obj_set_align(ui_DataBundleFooterBridge[i], LV_ALIGN_CENTER);
    lv_obj_set_style_bg_color(ui_DataBundleFooterBridge[i], lv_color_hex(0x055DA9), LV_PART_MAIN);

    ui_DataBundleFooterBridgeFill[i] = lv_obj_create(ui_DataBundleFooterGroup[i]);
    lv_obj_remove_style_all(ui_DataBundleFooterBridgeFill[i]);
    lv_obj_set_size(ui_DataBundleFooterBridgeFill[i], 25, 15);
    lv_obj_set_pos(ui_DataBundleFooterBridgeFill[i], 17, -1);
    lv_obj_set_align(ui_DataBundleFooterBridgeFill[i], LV_ALIGN_CENTER);
    lv_obj_set_style_radius(ui_DataBundleFooterBridgeFill[i], 5, LV_PART_MAIN);
    lv_obj_set_style_bg_color(ui_DataBundleFooterBridgeFill[i], lv_color_hex(0xFFFFFF), LV_PART_MAIN);

    // --- Footer Timer ---
    ui_DataBundleFooterTimerGroup[i] = lv_obj_create(ui_DataBundleFooterGroup[i]);
    lv_obj_remove_style_all(ui_DataBundleFooterTimerGroup[i]);
    lv_obj_set_size(ui_DataBundleFooterTimerGroup[i], 105, 20);
    lv_obj_set_pos(ui_DataBundleFooterTimerGroup[i], 0, -9);
    lv_obj_set_align(ui_DataBundleFooterTimerGroup[i], LV_ALIGN_BOTTOM_LEFT);

    ui_DataBundleFooterDateCornerTopLeft[i] = lv_obj_create(ui_DataBundleFooterTimerGroup[i]);
    lv_obj_remove_style_all(ui_DataBundleFooterDateCornerTopLeft[i]);
    lv_obj_set_size(ui_DataBundleFooterDateCornerTopLeft[i], 10, 10);
    lv_obj_set_align(ui_DataBundleFooterDateCornerTopLeft[i], LV_ALIGN_TOP_LEFT);
    lv_obj_set_style_bg_color(ui_DataBundleFooterDateCornerTopLeft[i], lv_color_hex(0x055DA9), LV_PART_MAIN);

    ui_DataBundleFooterDateCornerTopRight[i] = lv_obj_create(ui_DataBundleFooterTimerGroup[i]);
    lv_obj_remove_style_all(ui_DataBundleFooterDateCornerTopRight[i]);
    lv_obj_set_size(ui_DataBundleFooterDateCornerTopRight[i], 10, 10);
    lv_obj_set_align(ui_DataBundleFooterDateCornerTopRight[i], LV_ALIGN_TOP_RIGHT);
    lv_obj_set_style_bg_color(ui_DataBundleFooterDateCornerTopRight[i], lv_color_hex(0x055DA9), LV_PART_MAIN);

    ui_DataBundleFooterDate[i] = lv_obj_create(ui_DataBundleFooterTimerGroup[i]);
    lv_obj_remove_style_all(ui_DataBundleFooterDate[i]);
    lv_obj_set_size(ui_DataBundleFooterDate[i], 105, 20);
    lv_obj_set_align(ui_DataBundleFooterDate[i], LV_ALIGN_TOP_MID);
    lv_obj_set_style_radius(ui_DataBundleFooterDate[i], 10, LV_PART_MAIN);
    lv_obj_set_style_bg_color(ui_DataBundleFooterDate[i], lv_color_hex(0x055DA9), LV_PART_MAIN);

    ui_DataBundleFooterLabelDate[i] = lv_label_create(ui_DataBundleFooterDate[i]);
    lv_label_set_text(ui_DataBundleFooterLabelDate[i], "01.01.2024");
    lv_obj_set_x(ui_DataBundleFooterLabelDate[i], 7);
    lv_obj_set_align(ui_DataBundleFooterLabelDate[i], LV_ALIGN_LEFT_MID);
    lv_obj_set_style_text_font(ui_DataBundleFooterLabelDate[i], &lv_font_montserrat_12, LV_PART_MAIN);

    ui_DataBundleFooterLabelTime[i] = lv_label_create(ui_DataBundleFooterDate[i]);
    lv_label_set_text(ui_DataBundleFooterLabelTime[i], "12:00");
    lv_obj_set_x(ui_DataBundleFooterLabelTime[i], -5);
    lv_obj_set_align(ui_DataBundleFooterLabelTime[i], LV_ALIGN_RIGHT_MID);
    lv_obj_set_style_text_font(ui_DataBundleFooterLabelTime[i], &lv_font_montserrat_12, LV_PART_MAIN);

    // --- Footer Buttons ---
    ui_DataBundleFooterButtonsGroup[i] = lv_obj_create(ui_DataBundleFooterGroup[i]);
    lv_obj_remove_style_all(ui_DataBundleFooterButtonsGroup[i]);
    lv_obj_set_size(ui_DataBundleFooterButtonsGroup[i], 70, 30);
    lv_obj_set_pos(ui_DataBundleFooterButtonsGroup[i], 0, 1);
    lv_obj_set_align(ui_DataBundleFooterButtonsGroup[i], LV_ALIGN_BOTTOM_RIGHT);

    ui_DataBundleFooterButtonsCornerTopLeft[i] = lv_obj_create(ui_DataBundleFooterButtonsGroup[i]);
    lv_obj_remove_style_all(ui_DataBundleFooterButtonsCornerTopLeft[i]);
    lv_obj_set_size(ui_DataBundleFooterButtonsCornerTopLeft[i], 10, 10);
    lv_obj_set_align(ui_DataBundleFooterButtonsCornerTopLeft[i], LV_ALIGN_TOP_LEFT);
    lv_obj_set_style_bg_color(ui_DataBundleFooterButtonsCornerTopLeft[i], lv_color_hex(0x055DA9), LV_PART_MAIN);

    ui_DataBundleFooterButtonsCornerTopRight[i] = lv_obj_create(ui_DataBundleFooterButtonsGroup[i]);
    lv_obj_remove_style_all(ui_DataBundleFooterButtonsCornerTopRight[i]);
    lv_obj_set_size(ui_DataBundleFooterButtonsCornerTopRight[i], 10, 10);
    lv_obj_set_align(ui_DataBundleFooterButtonsCornerTopRight[i], LV_ALIGN_TOP_RIGHT);
    lv_obj_set_style_bg_color(ui_DataBundleFooterButtonsCornerTopRight[i], lv_color_hex(0x055DA9), LV_PART_MAIN);

    ui_DataBundleFooterButtons[i] = lv_obj_create(ui_DataBundleFooterButtonsGroup[i]);
    lv_obj_remove_style_all(ui_DataBundleFooterButtons[i]);
    lv_obj_set_size(ui_DataBundleFooterButtons[i], 70, 30);
    lv_obj_set_align(ui_DataBundleFooterButtons[i], LV_ALIGN_TOP_MID);
    lv_obj_set_style_radius(ui_DataBundleFooterButtons[i], 10, LV_PART_MAIN);
    lv_obj_set_style_bg_color(ui_DataBundleFooterButtons[i], lv_color_hex(0x055DA9), LV_PART_MAIN);

    ui_DataBundleFooterButtonExport[i] = lv_btn_create(ui_DataBundleFooterButtons[i]);
    lv_obj_set_size(ui_DataBundleFooterButtonExport[i], 28, 24);
    lv_obj_set_pos(ui_DataBundleFooterButtonExport[i], 5, -1);
    lv_obj_set_align(ui_DataBundleFooterButtonExport[i], LV_ALIGN_LEFT_MID);
    lv_obj_set_style_radius(ui_DataBundleFooterButtonExport[i], 5, LV_PART_MAIN);
    
    ui_DataBundleFooterButtonExportImage[i] = lv_img_create(ui_DataBundleFooterButtonExport[i]);
    lv_img_set_src(ui_DataBundleFooterButtonExportImage[i], &ui_img_export_png);
    lv_obj_set_align(ui_DataBundleFooterButtonExportImage[i], LV_ALIGN_CENTER);
    lv_img_set_zoom(ui_DataBundleFooterButtonExportImage[i], 81);

    ui_DataBundleFooterButtonClear[i] = lv_btn_create(ui_DataBundleFooterButtons[i]);
    lv_obj_set_size(ui_DataBundleFooterButtonClear[i], 28, 24);
    lv_obj_set_pos(ui_DataBundleFooterButtonClear[i], -5, -1);
    lv_obj_set_align(ui_DataBundleFooterButtonClear[i], LV_ALIGN_RIGHT_MID);
    lv_obj_set_style_radius(ui_DataBundleFooterButtonClear[i], 5, LV_PART_MAIN);

    ui_DataBundleFooterButtonClearImage[i] = lv_img_create(ui_DataBundleFooterButtonClear[i]);
    lv_img_set_src(ui_DataBundleFooterButtonClearImage[i], &ui_img_trashicon_png);
    lv_obj_set_align(ui_DataBundleFooterButtonClearImage[i], LV_ALIGN_CENTER);
    lv_img_set_zoom(ui_DataBundleFooterButtonClearImage[i], 81);
}

void DataBundlesGui::addNavButtonsToWidget(lv_obj_t *parentWidget)
{
    if (!parentWidget)
        return;

    // Previous button
    lv_obj_t ui_btnPrev = lv_btn_create(parentWidget);
    lv_obj_set_width(ui_btnPrev, 80);
    lv_obj_set_height(ui_btnPrev, 40);
    lv_obj_set_x(ui_btnPrev, 35);
    lv_obj_set_y(ui_btnPrev, -40);
    lv_obj_set_align(ui_btnPrev, LV_ALIGN_BOTTOM_LEFT);
    lv_obj_add_event_cb(ui_btnPrev, [](lv_event_t *e)
                        {
        auto self = static_cast<DataBundlesGui*>(lv_event_get_user_data(e));
        self->goToPreviousSensor(); }, LV_EVENT_CLICKED, this);

    lv_obj_t ui_btnPrevLabel = lv_label_create(ui_btnPrev);
    lv_label_set_text(ui_btnPrevLabel, "Prev");
    lv_obj_center(ui_btnPrevLabel);
    lv_obj_set_style_text_font(ui_btnPrevLabel, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Next button
    lv_obj_t ui_btnNext = lv_btn_create(parentWidget);
    lv_obj_set_width(ui_btnNext, 80);
    lv_obj_set_height(ui_btnNext, 40);
    lv_obj_set_x(ui_btnNext, 183);
    lv_obj_set_y(ui_btnNext, -40);
    lv_obj_set_align(ui_btnNext, LV_ALIGN_BOTTOM_LEFT);
    lv_obj_add_event_cb(ui_btnNext, [](lv_event_t *e)
                        {
        auto self = static_cast<DataBundlesGui*>(lv_event_get_user_data(e));
        self->goToNextSensor(); }, LV_EVENT_CLICKED, this);

    lv_obj_t ui_btnNextLabel = lv_label_create(ui_btnNext);
    lv_label_set_text(ui_btnNextLabel, "Next");
    lv_obj_center(ui_btnNextLabel);
    lv_obj_set_style_text_font(ui_btnNextLabel, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);

    // // logMessage("Navigation buttons added to widget\n");
}

void DataBundlesGui::addControlButtonsToWidget(lv_obj_t *parentWidget)
{
    if (!parentWidget)
        return;

    lv_obj_t ui_btnBackGroup = lv_obj_create(parentWidget);
    lv_obj_remove_style_all(ui_btnBackGroup);
    lv_obj_set_width(ui_btnBackGroup, 100);
    lv_obj_set_height(ui_btnBackGroup, 40);
    lv_obj_clear_flag(ui_btnBackGroup, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE); /// Flags

    lv_obj_t ui_btnBackCornerBottomLeft = lv_obj_create(ui_btnBackGroup);
    lv_obj_remove_style_all(ui_btnBackCornerBottomLeft);
    lv_obj_set_width(ui_btnBackCornerBottomLeft, 20);
    lv_obj_set_height(ui_btnBackCornerBottomLeft, 20);
    lv_obj_set_align(ui_btnBackCornerBottomLeft, LV_ALIGN_BOTTOM_LEFT);
    lv_obj_clear_flag(ui_btnBackCornerBottomLeft, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_obj_set_style_bg_color(ui_btnBackCornerBottomLeft, lv_color_hex(0x009BFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_btnBackCornerBottomLeft, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui_btnBackCornerBottomLeft, false, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t ui_btnBackCornerTopRight = lv_obj_create(ui_btnBackGroup);
    lv_obj_remove_style_all(ui_btnBackCornerTopRight);
    lv_obj_set_width(ui_btnBackCornerTopRight, 20);
    lv_obj_set_height(ui_btnBackCornerTopRight, 20);
    lv_obj_set_align(ui_btnBackCornerTopRight, LV_ALIGN_TOP_RIGHT);
    lv_obj_clear_flag(ui_btnBackCornerTopRight, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_obj_set_style_bg_color(ui_btnBackCornerTopRight, lv_color_hex(0x009BFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_btnBackCornerTopRight, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui_btnBackCornerTopRight, false, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Back button for returning to menu
    lv_obj_t ui_btnBack = lv_btn_create(ui_btnBackGroup);
    lv_obj_set_width(ui_btnBack, 100);
    lv_obj_set_height(ui_btnBack, 40);
    lv_obj_set_align(ui_btnBack, LV_ALIGN_CENTER);
    lv_obj_add_event_cb(ui_btnBack, [](lv_event_t *e)
                        {
        auto self = static_cast<DataBundlesGui*>(lv_event_get_user_data(e));
        // // logMessage("Back button pressed - returning to menu\n");
        switchToWiki(); }, LV_EVENT_CLICKED, this);

    lv_obj_t ui_btnBackLabel = lv_label_create(ui_btnBack);
    lv_label_set_text(ui_btnBackLabel, "Back");
    lv_obj_center(ui_btnBackLabel);
    lv_obj_set_style_text_font(ui_btnBackLabel, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);

    // // logMessage("Control buttons added to widget\n");
}

void DataBundlesGui::showShadowOverlay()
{
    if (ui_ShadowOverlay)
    {
        lv_obj_del(ui_ShadowOverlay);
        ui_ShadowOverlay = NULL;
    }

    ui_ShadowOverlay = lv_obj_create(lv_scr_act());
    lv_obj_clear_flag(ui_ShadowOverlay, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_add_flag(ui_ShadowOverlay, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_set_size(ui_ShadowOverlay, lv_pct(100), lv_pct(100));
    lv_obj_align(ui_ShadowOverlay, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_radius(ui_ShadowOverlay, 0, 0);

    lv_obj_set_style_bg_color(ui_ShadowOverlay, lv_color_black(), 0);
    lv_obj_set_style_bg_opa(ui_ShadowOverlay, LV_OPA_50, 0);
    lv_obj_set_style_border_width(ui_ShadowOverlay, 0, 0);
}

void DataBundlesGui::hideShadowOverlay()
{
    if (ui_ShadowOverlay)
    {
        lv_obj_del(ui_ShadowOverlay);
        ui_ShadowOverlay = NULL;
    }
}

void DataBundlesGui::handleClearButtonClick()
{
    // Add buttons
    static const char *btns[] = {"Yes", ""};
    // Show confirmation dialog before clearing history
    showShadowOverlay();
    lv_obj_t *confirmDialog = lv_msgbox_create(lv_scr_act(), "Confirm Deletion", "Are you sure you want to delete this data bundle?", btns, true);
    lv_obj_set_width(confirmDialog, 250);
    lv_obj_center(confirmDialog);
    lv_obj_move_foreground(confirmDialog);
    lv_obj_add_event_cb(confirmDialog, [](lv_event_t *e)
                        {
        auto self = static_cast<DataBundlesGui*>(lv_event_get_user_data(e));
        lv_event_code_t code = lv_event_get_code(e);

        if (code == LV_EVENT_VALUE_CHANGED)
        {
            lv_obj_t *msgbox = lv_event_get_current_target(e);
            const char *btnText = lv_msgbox_get_active_btn_text(msgbox);
            if (btnText && strcmp(btnText, "Yes") == 0)
            {
                self->handleClearConfirmButtonClick();
            }
            self->hideShadowOverlay();
            lv_obj_del(msgbox);
        }
        else if (code == LV_EVENT_DELETE)
        {
            self->hideShadowOverlay();
        } }, LV_EVENT_ALL, this);
}

void DataBundlesGui::handleClearConfirmButtonClick()
{
// TODO: Implement the logic to clear the data bundle
}

void DataBundlesGui::addLogoPanelToWidget(lv_obj_t *parentWidget)
{
    ui_LogoGroup = lv_obj_create(parentWidget);
    lv_obj_remove_style_all(ui_LogoGroup);
    lv_obj_set_width(ui_LogoGroup, 100);
    lv_obj_set_height(ui_LogoGroup, 20);
    lv_obj_set_x(ui_LogoGroup, 10);
    lv_obj_set_y(ui_LogoGroup, 0);
    lv_obj_set_align(ui_LogoGroup, LV_ALIGN_BOTTOM_RIGHT);
    lv_obj_clear_flag(ui_LogoGroup, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE); /// Flags

    ui_LogoCornerBottomLeft = lv_obj_create(ui_LogoGroup);
    lv_obj_remove_style_all(ui_LogoCornerBottomLeft);
    lv_obj_set_width(ui_LogoCornerBottomLeft, 10);
    lv_obj_set_height(ui_LogoCornerBottomLeft, 10);
    lv_obj_set_x(ui_LogoCornerBottomLeft, 10);
    lv_obj_set_y(ui_LogoCornerBottomLeft, 0);
    lv_obj_set_align(ui_LogoCornerBottomLeft, LV_ALIGN_BOTTOM_LEFT);
    lv_obj_clear_flag(ui_LogoCornerBottomLeft, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_obj_set_style_bg_color(ui_LogoCornerBottomLeft, lv_color_hex(0x055DA9), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_LogoCornerBottomLeft, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui_LogoCornerBottomLeft, false, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_LogoCornerBottomRight = lv_obj_create(ui_LogoGroup);
    lv_obj_remove_style_all(ui_LogoCornerBottomRight);
    lv_obj_set_width(ui_LogoCornerBottomRight, 10);
    lv_obj_set_height(ui_LogoCornerBottomRight, 10);
    lv_obj_set_x(ui_LogoCornerBottomRight, -10);
    lv_obj_set_y(ui_LogoCornerBottomRight, 0);
    lv_obj_set_align(ui_LogoCornerBottomRight, LV_ALIGN_TOP_RIGHT);
    lv_obj_clear_flag(ui_LogoCornerBottomRight, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_obj_set_style_bg_color(ui_LogoCornerBottomRight, lv_color_hex(0x055DA9), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_LogoCornerBottomRight, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui_LogoCornerBottomRight, false, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_LogoOutlay = lv_obj_create(ui_LogoGroup);
    lv_obj_remove_style_all(ui_LogoOutlay);
    lv_obj_set_width(ui_LogoOutlay, 80);
    lv_obj_set_height(ui_LogoOutlay, 20);
    lv_obj_set_align(ui_LogoOutlay, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_LogoOutlay, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_obj_set_style_radius(ui_LogoOutlay, 1000, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_LogoOutlay, lv_color_hex(0x055DA9), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_LogoOutlay, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui_LogoOutlay, false, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_LogoImage = lv_img_create(ui_LogoGroup);
    lv_img_set_src(ui_LogoImage, &ui_img_mtalogo_png);
    lv_obj_set_width(ui_LogoImage, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_LogoImage, LV_SIZE_CONTENT); /// 1
    lv_obj_set_align(ui_LogoImage, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_LogoImage, LV_OBJ_FLAG_ADV_HITTEST);  /// Flags
    lv_obj_clear_flag(ui_LogoImage, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_img_set_zoom(ui_LogoImage, 70);
}

void DataBundlesGui::showDataBundles()
{
    if (!initialized || !ui_DataBundlesWidget)
        return;

    lv_obj_clear_flag(ui_DataBundlesWidget, LV_OBJ_FLAG_HIDDEN);
}

void DataBundlesGui::hideDataBundles()
{
    if (!initialized || !ui_DataBundlesWidget)
        return;

    lv_obj_add_flag(ui_DataBundlesWidget, LV_OBJ_FLAG_HIDDEN);
}