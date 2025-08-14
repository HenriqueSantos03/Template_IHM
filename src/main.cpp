#include <Arduino.h>
#include "ihmControl.h"
#include "ihmTelaMain.h"
#include "events.h"

void setup() {
    Serial.begin(115200);
    delay(2000);  // Aguardar Serial
    Serial.println("Iniciando setup...");
    initIhmControl();
    ihmTelaMainInit();
    EventsInit();
    Serial.println("Setup concluído");
}

void loop() {
    vTaskIhmControl();
    ihmTelaMainTask();
    EventsTask();
}