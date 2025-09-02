#include <Arduino.h>
#include <lvgl.h>
#include "ihmTelaMain.h"
#include "events.h"

void createMainUI(ui_t *ui) {
    // Criar container principal
    // Configurar a tela ativa (lv_scr_act) para ter fundo preto e evitar cantos brancos
    lv_obj_set_style_bg_color(lv_scr_act(), lv_color_hex(0x000000), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(lv_scr_act(), LV_OPA_COVER, LV_PART_MAIN);

    // Criar o dashboard principal
    ui->ui_telaMain_dashboard = lv_obj_create(lv_scr_act());
    lv_obj_set_size(ui->ui_telaMain_dashboard, SCREEN_WIDTH, SCREEN_HEIGHT); // Usar dimensões exatas da tela
    lv_obj_set_pos(ui->ui_telaMain_dashboard, 0, 0); // Posicionar exatamente na origem (0,0)
    lv_obj_set_style_pad_all(ui->ui_telaMain_dashboard, 0, LV_PART_MAIN); // Remover qualquer padding
    lv_obj_set_style_border_width(ui->ui_telaMain_dashboard, 0, LV_PART_MAIN); // Remover bordas
    lv_obj_set_style_radius(ui->ui_telaMain_dashboard, 0, LV_PART_MAIN); // Remover bordas arredondadas
    lv_obj_set_style_bg_opa(ui->ui_telaMain_dashboard, 0, LV_PART_MAIN | LV_STATE_DEFAULT); // Fundo transparente
    lv_obj_set_scrollbar_mode(ui->ui_telaMain_dashboard, LV_SCROLLBAR_MODE_OFF); // Desativar barra de rolagem
    lv_obj_clear_flag(ui->ui_telaMain_dashboard, LV_OBJ_FLAG_SCROLLABLE); // Desativar scroll

    // Criar container principal
    ui->ui_telaMain_container = lv_obj_create(ui->ui_telaMain_dashboard);
    lv_obj_set_size(ui->ui_telaMain_container, SCREEN_WIDTH, SCREEN_HEIGHT); // Usar dimensões exatas da tela
    lv_obj_set_pos(ui->ui_telaMain_container, 0, 0); // Posicionar exatamente na origem (0,0)
    lv_obj_set_style_pad_all(ui->ui_telaMain_container, 0, LV_PART_MAIN); // Remover qualquer padding
    lv_obj_set_style_border_width(ui->ui_telaMain_container, 0, LV_PART_MAIN); // Remover bordas
    lv_obj_set_style_radius(ui->ui_telaMain_container, 0, LV_PART_MAIN); // Remover bordas arredondadas
    lv_obj_set_style_bg_color(ui->ui_telaMain_container, lv_color_hex(0x000000), LV_PART_MAIN); // Fundo preto
    lv_obj_set_style_bg_opa(ui->ui_telaMain_container, LV_OPA_COVER, LV_PART_MAIN); // Garantir opacidade total
    lv_obj_set_scrollbar_mode(ui->ui_telaMain_container, LV_SCROLLBAR_MODE_OFF); // Desativar barra de rolagem
    lv_obj_clear_flag(ui->ui_telaMain_container, LV_OBJ_FLAG_SCROLLABLE); // Desativar scroll
    lv_obj_add_flag(ui->ui_telaMain_container, LV_OBJ_FLAG_EVENT_BUBBLE); // Evitar que o container capture eventos de scroll


    // Criar botão 1
    ui->btn_1 = lv_btn_create(ui->ui_telaMain_container);
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