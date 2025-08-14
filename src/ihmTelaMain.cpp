//----------------------------------------------
// ihmTelaMain.cpp (Copia de ihmDashboard.cpp)
//----------------------------------------------
#include <Arduino.h>
#include <lvgl.h>
#include "LGFX_Custom.h"
#include "ihmTelaMain.h"
#include "events.h"

LGFX gfx;

static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[SCREEN_WIDTH * SCREEN_HEIGHT / 10];

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

void ihmTelaMainInit() {
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

    // Criar botão 1
    lv_obj_t *btn_1 = lv_btn_create(lv_scr_act());
    lv_obj_set_size(btn_1, 200, 100); // Definir tamanho do botão
    lv_obj_align(btn_1, LV_ALIGN_CENTER, 0, 0); // Centralizar o botão
    
    // Criar label do botão 1
    lv_obj_t *label = lv_label_create(btn_1);
    lv_label_set_text(label, "Clique Aqui");
    lv_obj_center(label);
    
    // Registrar botão para eventos
    btn_1_event_cb(btn_1); 

}

void ihmTelaMainTask() {
    lv_timer_handler();
    lv_tick_inc(5);  // Incrementa o tick do LVGL a cada 5ms
    delay(5);
}