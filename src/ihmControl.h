#ifndef IHM_CONTROL_H
#define IHM_CONTROL_H

#include <Arduino.h>
#include <lvgl.h>
#include "LGFX_Custom.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 480
// Máquina de estados da IHM (controle de telas)
enum {
    IHM_RESET,
    IHM_WAIT_CONTROL,
    IHM_IDLE,
    QTD_IHM_STATE
};

void ihmControlInit();
void ihmControlTask();

#endif