#ifndef MENU_H
#define MENU_H

#include "config.h"

enum State {
    MAIN_SCREEN,
    SETTINGS_MENU,
    ABOUT_SCREEN,
    FUNC1_STATE
};

struct MenuItem {
    const char* text;
    void (*action)();
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
    void drawMenuHeader();
    void drawMenuItems();
    
    MenuItem menuItems[MAX_MENU_ITEMS];
    int selectedMenuItem;
    State currentState;
};

#endif // MENU_H