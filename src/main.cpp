#include <Arduino.h>
#include "ihmTelaMain.h"
#include "events.h"

void setup() {
    Serial.begin(115200);
    delay(2000);  // Aguardar Serial
    Serial.println("Iniciando setup...");
    ihmTelaMainInit();
    EventsInit();
    Serial.println("Setup concluído");
}

void loop() {
    ihmTelaMainTask();
    EventsTask();
}