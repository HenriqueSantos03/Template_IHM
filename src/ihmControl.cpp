#include <Arduino.h>
#include <lvgl.h>
#include "LGFX_Custom.h"
#include "ihmControl.h"

LGFX gfx;

static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[SCREEN_WIDTH * SCREEN_HEIGHT / 10];

static uint8_t ihmFirstEntry;
static uint8_t ihmState;
static unsigned long ihmTick = 0;
static unsigned long ihmDelayTick = 0;

void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p) {
    uint32_t w = (area->x2 - area->x1 + 1);
    uint32_t h = (area->y2 - area->y1 + 1);
    gfx.startWrite();
    gfx.setAddrWindow(area->x1, area->y1, w, h);
    gfx.pushPixels((uint16_t *)&color_p->full, w * h, true);
    gfx.endWrite();
    lv_disp_flush_ready(disp);
}

void my_touchpad_read(lv_indev_drv_t *indev_driver, lv_indev_data_t *data) {
    uint16_t touchX, touchY;
    bool touched = gfx.getTouch(&touchX, &touchY);
    if (!touched) {
        data->state = LV_INDEV_STATE_REL;
    } else {
        data->state = LV_INDEV_STATE_PR;
        data->point.x = touchX;
        data->point.y = touchY;
        Serial.printf("Toque: x=%d, y=%d\n", touchX, touchY);
    }
}

void initIhmControl() {
    Serial.println("Inicializando display...");
    gfx.begin();
    gfx.setBrightness(255);  // Backlight máximo
    Serial.println("Display inicializado");

    Serial.println("Inicializando LVGL...");
    lv_init();
    lv_disp_draw_buf_init(&draw_buf, buf, NULL, SCREEN_WIDTH * SCREEN_HEIGHT / 10);
    Serial.println("Buffer LVGL inicializado");

    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.hor_res = SCREEN_WIDTH;
    disp_drv.ver_res = SCREEN_HEIGHT;
    disp_drv.flush_cb = my_disp_flush;
    disp_drv.draw_buf = &draw_buf;
    lv_disp_drv_register(&disp_drv);
    Serial.println("Driver de display registrado");

    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = my_touchpad_read;
    lv_indev_drv_register(&indev_drv);
    Serial.println("Driver de toque registrado");

    ihmTick = millis();
    ihmDelayTick = millis();
    ihmState = IHM_RESET;
}

void vTaskIhmControl() {
    if (millis() > (ihmTick + 250)) {
        ihmTick = millis();

        switch (ihmState) {
            case IHM_RESET:
                if (millis() > (ihmDelayTick + 1500)) {
                    ihmState = IHM_WAIT_CONTROL;
                }
                break;
            case IHM_WAIT_CONTROL:
                ihmState = IHM_IDLE;
                break;
            case IHM_IDLE:
                // Estado ocioso, pronto para interações
                break;
        }
    }
    lv_timer_handler();
    lv_tick_inc(5);  // Incrementa o tick do LVGL a cada 5ms
    delay(5);
}