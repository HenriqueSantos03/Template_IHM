#include <Arduino.h>
#include <lvgl.h>
#include "events.h"

static void button_event_handler(lv_event_t *e) {
    Serial.println("clique");
}

void eventsInit() {
    // Inicialização de eventos, se necessário
}

void eventsTask() {
    // Tarefas periódicas de eventos, se necessário
}

void btn_1_event_cb(lv_obj_t *btn) {
    lv_obj_add_event_cb(btn, button_event_handler, LV_EVENT_CLICKED, NULL);
}