#include <Arduino.h>
#include "ihmControl.h"
#include "masterControl.h"
#include "UartTron.h"

void setup() {
    Serial.begin(115200);
    uartTronInit();      // inicia a comunicação UART
    ihmControlInit();    // inicializa a tela e a interface
    masterControlInit(); 
}

void loop() {
    ihmControlTask();    // executa e atualiza a maquina de estados da IHM
    uartTronTask();      // executa a tarefa de comunicação UART
    masterControlTask(); // executa tarefas periódicas de controle mestre
}