
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
static void on_splash_msgbox_event(lv_event_t* e) {
  lv_event_code_t code = lv_event_get_code(e);
  if (code == LV_EVENT_VALUE_CHANGED) {
    const char* btn_txt = lv_msgbox_get_active_btn_text((lv_obj_t*)lv_event_get_target(e));
    // TODO: Handle button actions based on btn_txt ("OK" / "Cancel")
  }
}

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

#else
// LVGL not enabled, provide empty implementations, with logMessage instead
static void on_splash_msgbox_event(lv_event_t* e) 
{
  // No operation
}

void show_splash_popup(const char* title, const char* text, uint32_t autoclose_ms) {
  logMessage("Splash Popup: %s - %s", title, text);
}

#endif // USE_LVGL

