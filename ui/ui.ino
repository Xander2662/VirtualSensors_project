//Elecrow DIS08070H board-template main source file
#include<Arduino.h>
//#define ESP_PLATFORM
#define LGFX_USE_V1
#include <LovyanGFX.hpp>
#include <lgfx/v1/platforms/esp32s3/Panel_RGB.hpp>
#include <lgfx/v1/platforms/esp32s3/Bus_RGB.hpp>
#include <lvgl.h>
#include <ui.h>
#include <engine.hpp>  // include engine header
#include <gui/gui_manager.hpp>  // include new GUI manager
#include <gui/gui_callbacks.hpp>  // include GUI callback declarations

/*Don't forget to set Sketchbook location in File/Preferences to the path of your UI project (the parent foder of this INO file)*/


enum BoardConstants { TFT_BL=2, LVGL_BUFFER_RATIO=6 };


class LGFX : public lgfx::LGFX_Device
{
public:
  lgfx::Bus_RGB     _bus_instance;
  lgfx::Panel_RGB   _panel_instance;
  LGFX (void)
  {
    {
      auto cfg = _bus_instance.config();
      cfg.panel = &_panel_instance;

      cfg.pin_d0  = GPIO_NUM_15; // B0
      cfg.pin_d1  = GPIO_NUM_7;  // B1
      cfg.pin_d2  = GPIO_NUM_6;  // B2
      cfg.pin_d3  = GPIO_NUM_5;  // B3
      cfg.pin_d4  = GPIO_NUM_4;  // B4

      cfg.pin_d5  = GPIO_NUM_9;  // G0
      cfg.pin_d6  = GPIO_NUM_46; // G1
      cfg.pin_d7  = GPIO_NUM_3;  // G2
      cfg.pin_d8  = GPIO_NUM_8;  // G3
      cfg.pin_d9  = GPIO_NUM_16; // G4
      cfg.pin_d10 = GPIO_NUM_1;  // G5

      cfg.pin_d11 = GPIO_NUM_14; // R0
      cfg.pin_d12 = GPIO_NUM_21; // R1
      cfg.pin_d13 = GPIO_NUM_47; // R2
      cfg.pin_d14 = GPIO_NUM_48; // R3
      cfg.pin_d15 = GPIO_NUM_45; // R4

      cfg.pin_henable = GPIO_NUM_41;
      cfg.pin_vsync   = GPIO_NUM_40;
      cfg.pin_hsync   = GPIO_NUM_39;
      cfg.pin_pclk    = GPIO_NUM_0;
      cfg.freq_write  = 15000000;

      cfg.hsync_polarity    = 0;
      cfg.hsync_front_porch = 40;
      cfg.hsync_pulse_width = 48;
      cfg.hsync_back_porch  = 40;

      cfg.vsync_polarity    = 0;
      cfg.vsync_front_porch = 1;
      cfg.vsync_pulse_width = 31;
      cfg.vsync_back_porch  = 13;

      cfg.pclk_active_neg   = 1;
      cfg.de_idle_high      = 0;
      cfg.pclk_idle_high    = 0;

      _bus_instance.config(cfg);
    }
    {
      auto cfg = _panel_instance.config();
      cfg.memory_width  = 800;
      cfg.memory_height = 480;
      cfg.panel_width  = 800;
      cfg.panel_height = 480;
      cfg.offset_x = 0;
      cfg.offset_y = 0;
      _panel_instance.config(cfg);
    }
    _panel_instance.setBus(&_bus_instance);
    setPanel(&_panel_instance);
  }
};


LGFX lcd;

/*Change to your screen resolution*/
static const uint16_t screenWidth  = 800;
static const uint16_t screenHeight = 480;

static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf [screenWidth * screenHeight / LVGL_BUFFER_RATIO];


#include "touch.h"


#if LV_USE_LOG != 0
/* Serial debugging */
void my_print (const char * buf)
{
    Serial.printf( buf );
    Serial.flush();
}
#endif


/* Display flushing */
void my_disp_flush (lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
    uint32_t w = (area->x2 - area->x1 + 1);
    uint32_t h = (area->y2 - area->y1 + 1);

#if (LV_COLOR_16_SWAP != 0)
    lcd.pushImageDMA( area->x1, area->y1, w, h, (lgfx::rgb565_t*) &color_p->full );
#else
    lcd.pushImageDMA( area->x1, area->y1, w, h, (lgfx::rgb565_t*) &color_p->full );
#endif
    lv_disp_flush_ready( disp );
}


/*Read the touchpad*/
void my_touchpad_read (lv_indev_drv_t * indev_driver, lv_indev_data_t * data)
{
    if ( touch_has_signal() ) {
        if ( touch_touched() ) {
            data->state = LV_INDEV_STATE_PR;
            //Set the coordinates
            data->point.x = touch_last_x;
            data->point.y = touch_last_y;
            //Serial.print( "Data x :" );
            //Serial.println( touch_last_x );
            //Serial.print( "Data y :" );
            //Serial.println( touch_last_y );
        }
        else if ( touch_released() ) {
            data->state = LV_INDEV_STATE_REL;
        }
    }
    else {
        data->state = LV_INDEV_STATE_REL;
    }
    delay(15);
}

SensorManager sensorManager;  // Create SensorManager instance
GuiManager guiManager(sensorManager);  // Create GUI manager instance

// Global GUI screen switching functions for use by GUI components
void switchToMenu() {
    if (guiManager.isInitialized()) {
        // Stop sensors when returning to menu
        sensorManager.setRunning(false);
        guiManager.showMenu();
    }
}

void switchToVisualization() {
    if (guiManager.isInitialized()) {
        guiManager.showVisualization();
    }
}

void switchToWiki() {
    if (guiManager.isInitialized()) {
        guiManager.showWiki();
    }
}

void setup ()
{
    Serial.begin( 115200 ); /* prepare for possible serial debug */
    Serial.println( "Starting setup..." );
    delay( 10 );

    //Init Display
    lcd.begin();
    lcd.fillScreen( TFT_BLACK );
    delay( 200 );

    lv_init();

    delay( 100 );
    touch_init();

    //screenWidth = lcd.width();
    //screenHeight = lcd.height();
    lv_disp_draw_buf_init( &draw_buf, buf, NULL, screenWidth * screenHeight / LVGL_BUFFER_RATIO );

    /*Initialize the display*/
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init( &disp_drv );
    /*Change the following line to your display resolution*/
    disp_drv.hor_res = screenWidth;
    disp_drv.ver_res = screenHeight;
    disp_drv.flush_cb = my_disp_flush;
    disp_drv.draw_buf = &draw_buf;
    lv_disp_drv_register( &disp_drv );

    /*Initialize the (dummy) input device driver*/
    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init( &indev_drv );
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = my_touchpad_read;
    lv_indev_drv_register( &indev_drv );

    pinMode(TFT_BL, OUTPUT);
    digitalWrite(TFT_BL, HIGH);

    ui_init();
    //lcd.fillScreen(TFT_BLACK);
    
    while(!sensorManager.init()) {
        Serial.println("Waiting for SensorManager initialization...");
        delay(100);
    }
    
    // Initialize the new GUI manager
    guiManager.init();
    switchToMenu();  // Start in menu screen
    
    Serial.println( "Setup done" );
}

const int FPS = 60;
const int CYCLE_DRAW_MS = (1000/FPS);
const int CYCLE_SYNC_MS = 100;

const int LOOP_SYNC_TH = CYCLE_SYNC_MS/CYCLE_DRAW_MS;
int LOOP_SYNC_COUNTER = LOOP_SYNC_TH;

void loop ()
{
    if (LOOP_SYNC_COUNTER-- < 0) {
        if (sensorManager.isRunning()) {
            sensorManager.resync();
        }
        LOOP_SYNC_COUNTER = LOOP_SYNC_TH;   
        delay(10);
    }

    // Draw sensor data when sensors are running and in visualization mode
    if (sensorManager.isRunning() && guiManager.isInitialized()) {
        if (guiManager.getCurrentState() == GuiState::VISUALIZATION) {
            guiManager.getVisualizationGui().drawCurrentSensor();
        }
        delay(1);
    }
    //logMessage("Loop start\n");
    lv_timer_handler();
    delay(CYCLE_DRAW_MS);
}


