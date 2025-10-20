
/**
 * @file splasher.h
 * @brief Modal popup utility for LVGL with OK/Cancel buttons and optional auto-close.
 *
 * Provides a function to display a modal popup (message box) with OK and Cancel buttons,
 * and an optional auto-close timer. Intended for use with the LVGL graphics library.
 *
 * @copyright 2025 MTA
 * @author Ing. Jiri Konecny
 */

#ifndef SPLASHER_H
#define SPLASHER_H

#include "../config.hpp"  ///< Configuration file inclusion

#ifdef USE_LVGL
extern "C"
{
#include <lvgl.h>
}

/**
 * @brief Event handler for message box button events.
 *
 * Handles button clicks in the modal popup. You can customize the action based on the button text ("OK"/"Cancel").
 * @param e LVGL event pointer
 */
static void on_splash_msgbox_event(lv_event_t* e);


/**
 * @brief Show a modal popup with OK/Cancel buttons and optional auto-close.
 *
 * Displays a modal message box on the active LVGL screen. The popup includes OK and Cancel buttons.
 * Optionally, the popup can close automatically after a specified time.
 *
 * @param title Title of the popup window
 * @param text Message text to display
 * @param autoclose_ms Optional auto-close timeout in milliseconds (0 = no auto-close)
 */
void show_splash_popup(const char* title, const char* text, uint32_t autoclose_ms = 0);

#endif // USE_LVGL
#endif // SPLASHER_H
