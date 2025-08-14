#include <Arduino.h>
#include <lvgl.h>
#include "LGFX_Custom.h"

LGFX gfx;

static const uint16_t screenWidth = 800;
static const uint16_t screenHeight = 480;
static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[screenWidth * screenHeight / 10];

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

void gui_init() {
    Serial.println("Inicializando display...");
    gfx.begin();
    gfx.setBrightness(255);  // Backlight máximo
    Serial.println("Display inicializado");

    gfx.fillScreen(0xF800);  // Vermelho
    Serial.println("Tela deve estar vermelha");
    delay(2000);
    gfx.fillScreen(0x0000);  // Preto
    Serial.println("Tela deve estar preta");

    Serial.println("Inicializando LVGL...");
    lv_init();
    lv_disp_draw_buf_init(&draw_buf, buf, NULL, screenWidth * screenHeight / 10);
    Serial.println("Buffer LVGL inicializado");

    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.hor_res = screenWidth;
    disp_drv.ver_res = screenHeight;
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
}

void create_button() {
    Serial.println("Criando botão...");
    lv_obj_t *btn = lv_btn_create(lv_scr_act());
    if (!btn) {
        Serial.println("Erro: Falha ao criar botão");
        return;
    }
    lv_obj_set_size(btn, 200, 100);
    lv_obj_align(btn, LV_ALIGN_CENTER, 0, 0);

    lv_obj_t *label = lv_label_create(btn);
    if (!label) {
        Serial.println("Erro: Falha ao criar label");
        return;
    }
    lv_label_set_text(label, "Clique Aqui");
    lv_obj_center(label);
    Serial.println("Botão criado");
}

void setup() {
    Serial.begin(115200);
    delay(2000);  // Aguardar Serial
    Serial.println("Iniciando setup...");
    gui_init();
    create_button();
    Serial.println("Setup concluído");
}

void loop() {
    lv_timer_handler();
    delay(5);
}