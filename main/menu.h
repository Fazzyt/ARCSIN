#ifndef MENU_H
#define MENU_H

#include "config.h"
#include "wifi_tool.h"
#include "ble_djamer.h"
#include "ir_handler.h"

enum State {
    MAIN_SCREEN,
    SETTINGS_MENU,
    SIN_STATE,
    WIFI_SCAN_STATE,
    BLUEJACKING_TOOL_STATE,
    IR_RECEIVE_STATE
};

struct MenuItem {
    const char* text;
};

class Menu {
public:
    Menu();
    void init();
    void update();
    void navigateUp();
    void navigateDown();
    void select();

private:
    float phaseShift = 0;
    
    void drawMenuHeader();
    void drawMenuItems();

    MenuItem menuItems[MAX_MENU_ITEMS];
    int selectedMenuItem;
    State currentState;
};

#endif // MENU_H