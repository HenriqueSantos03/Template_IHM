#include <Arduino.h>
#include "UartTron.h"

void uartTronInit(){
    // Inicializa serial 1 nos pinos 18 (RX) e 17 (TX) com baud rate de 115200
    Serial1.begin(115200, SERIAL_8N1, UART_RX_PIN, UART_TX_PIN);
    Serial1.println("UART Tron initialized");
}

void uartTronTask() {
    // Check if data is available to read
    if (Serial1.available()) {
        String data = Serial1.readStringUntil('\n'); // Read until newline
        Serial.println("Received: " + data); // Print received data to Serial
    }

    // Example of sending data
    static unsigned long lastSendTime = 0;
    if (millis() > (lastSendTime + 1000)) { // Send every second
        Serial1.println("Hello from UartTron!");
        lastSendTime = millis();
    }
}