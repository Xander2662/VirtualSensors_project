
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

 #include "splasher.hpp"

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
static void on_splash_msgbox_event(lv_event_t* e) {
  lv_event_code_t code = lv_event_get_code(e);
  if (code == LV_EVENT_VALUE_CHANGED) {
    const char* btn_txt = lv_msgbox_get_active_btn_text((lv_obj_t*)lv_event_get_target(e));
    // TODO: Handle button actions based on btn_txt ("OK" / "Cancel")
  }
}


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
void show_splash_popup(const char* title, const char* text, uint32_t autoclose_ms) {
  static const char* btns[] = {"OK", "Cancel", ""};
  lv_obj_t* scr = lv_scr_act();
  lv_obj_t* mbox = lv_msgbox_create(scr, title, text, btns, true);
  lv_obj_center(mbox);
  lv_obj_add_event_cb(mbox, on_splash_msgbox_event, LV_EVENT_VALUE_CHANGED, NULL);

  if (autoclose_ms > 0) {
    lv_timer_t* t = lv_timer_create([](lv_timer_t* t){
      lv_obj_t* obj = (lv_obj_t*)t->user_data;
      if (obj) lv_msgbox_close(obj);
      lv_timer_del(t);
    }, autoclose_ms, mbox);
    (void)t;
  }
}

#endif // USE_LVGL