#include <Arduino.h>
#include "config.h"
#include "display.h"
#include "menu.h"

Menu menu;
WIFI_TOOL wifi_tool;
DisplayManager displayManager;

void setup() {
    Serial.begin(115200);
    // Инициализация компонентов
    displayManager.init();
    menu.init();
    // Настройка пинов
    pinMode(PIN_BUTTON_UP, INPUT_PULLUP);
    pinMode(PIN_BUTTON_DOWN, INPUT_PULLUP);
    pinMode(PIN_BUTTON_ENTER, INPUT_PULLUP);
    
}

void loop() {
    handleButtonPress();
    delay(200);
}

void handleButtonPress() {
    if (digitalRead(PIN_BUTTON_UP) == LOW) {
        menu.navigateUp();
    }
    
    if (digitalRead(PIN_BUTTON_DOWN) == LOW) {
        menu.navigateDown();
    }
    
    if (digitalRead(PIN_BUTTON_ENTER) == LOW) {
        menu.select(); 
    }
}