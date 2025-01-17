#include <Arduino.h>
#include "config.h"
#include "display.h"
#include "menu.h"

Menu menu;
WIFI_TOOL wifi_tool;
DisplayManager displayManager;
BLE_TOOL ble_tool;
IRHandler irHandler;

void setup() {
    Serial.begin(115200);
    // Инициализация компонентов
    displayManager.init();
    menu.init();
    irHandler.init();

    // Настройка пинов
    pinMode(PIN_BUTTON_UP, INPUT_PULLUP);
    pinMode(PIN_BUTTON_DOWN, INPUT_PULLUP);
    pinMode(PIN_BUTTON_ENTER, INPUT_PULLUP);
}

void loop() {
    handleButtonPress();
    menu.update();
}

void handleButtonPress() {
    if (digitalRead(PIN_BUTTON_UP) == LOW) {
        menu.navigateUp();
        delay(200);
    }
    
    if (digitalRead(PIN_BUTTON_DOWN) == LOW) {
        menu.navigateDown();
        delay(200);
    }
    
    if (digitalRead(PIN_BUTTON_ENTER) == LOW) {
        menu.select(); 
        delay(200);
    }
}