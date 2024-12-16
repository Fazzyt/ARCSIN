#include "display.h"
#include "config.h"

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>
#include <math.h>

#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C

DisplayManager displayManager;

DisplayManager::DisplayManager() : display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET) {}

bool DisplayManager::init() {
    if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
        Serial.println(F("Display initialization failed"));
        return false;
    }

    display.clearDisplay();
    display.setTextColor(SSD1306_WHITE);
    display.setTextSize(1);
    display.setCursor(0, 0);
    return true;
}

void DisplayManager::clear() {
    display.clearDisplay();
}

void DisplayManager::update() {
    display.display();
}

void DisplayManager::drawText(int x, int y, float size, const String& text) {
    display.setCursor(x, y);
    display.setTextSize(size);
    display.println(text);
}

void DisplayManager::drawCenteredText(const String& text, int y, float size) {
    int16_t x1, y1;
    uint16_t w, h;
    display.getTextBounds(text, 0, 0, &x1, &y1, &w, &h);
    int x = (SCREEN_WIDTH - w) / 2;
    drawText(x, y, size, text);
}

void DisplayManager::drawSineWave() {
    for (int x = 0; x < SCREEN_WIDTH; x++) {
        int y = SCREEN_HEIGHT / 2 + sin(x * 0.1) * (SCREEN_HEIGHT / 4);
        display.drawPixel(x, y, SSD1306_WHITE);
    }
}

void DisplayManager::renderMainScreen() {
    clear();
    drawCenteredText("ARCSIN", 10, 2);
    drawSineWave();
    update();
}

void DisplayManager::renderMenu(const String menuItems[], int selectedIndex, int itemCount) {
    clear();
    for (int i = 0; i < itemCount; i++) {
        int y = 10 + (i * 15);
        if (i == selectedIndex) {
            display.fillRect(0, y - 2, SCREEN_WIDTH, 12, SSD1306_WHITE);
            display.setTextColor(SSD1306_BLACK);
        } else {
            display.setTextColor(SSD1306_WHITE);
        }
        drawText(10, y, 1, menuItems[i]);
    }
    update();
}