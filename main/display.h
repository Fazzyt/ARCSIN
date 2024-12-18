#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>
#include <Adafruit_SSD1306.h>
#include "config.h"

class DisplayManager {
public:
    DisplayManager();
    
    bool init();
    void clear();
    void update();
    
    void drawText(int x, int y, float size, const String& text);
    void drawCenteredText(const String& text, int y, float size = 1);
    
    void drawSineWave();
    void drawProgressBar(int current, int total);
    void renderMainScreen();
    void renderMenu(const String menuItems[], int selectedIndex, int itemCount);

private:
    Adafruit_SSD1306 display;
};

extern DisplayManager displayManager;

#endif