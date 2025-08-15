#include <Arduino.h>
#include <lvgl.h>
#include "ihmTelaMain.h"
#include "events.h"

void createMainUI(ui_t *ui) {
    // Criar container principal
    ui->container = lv_obj_create(lv_scr_act()); // Cria o container na tela ativa
    lv_obj_set_size(ui->container, SCREEN_WIDTH, SCREEN_HEIGHT); 
    lv_obj_align(ui->container, LV_ALIGN_TOP_LEFT, 0, 0);
    lv_obj_set_style_bg_color(ui->container, lv_color_hex(0x000000), LV_PART_MAIN);

    // Criar botão 1
    ui->btn_1 = lv_btn_create(ui->container);
    lv_obj_set_size(ui->btn_1, 200, 100);
    lv_obj_align(ui->btn_1, LV_ALIGN_CENTER, 0, 0);

    // Criar label do botão 1
    ui->label_btn1 = lv_label_create(ui->btn_1);
    lv_label_set_text(ui->label_btn1, "Iniciar");
    lv_obj_center(ui->label_btn1);

    // Registrar botão para eventos
    btn_1_event_cb(ui->btn_1);
}

void ihmTelaMainInit() {
    static ui_t ui;
    createMainUI(&ui);
}

void ihmTelaMainTask() {
    // Tarefas periódicas, se necessário
}