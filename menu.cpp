#include "menu.h"
#include "display.h"

Menu::Menu() : 
    currentState(MAIN_SCREEN), 
    selectedMenuItem(0) {
    // Инициализация пунктов меню
    menuItems[0] = {"Settings", nullptr};
    menuItems[1] = {"Sin", nullptr};
    menuItems[2] = {"Func 2", nullptr};
    menuItems[3] = {"Func 3", nullptr};
    menuItems[4] = {"Exit", nullptr}; // Выход без действия
}

void Menu::init() {
    displayManager.renderMainScreen();
}

void Menu::update() {
    switch(currentState) {
        case MAIN_SCREEN:
            displayManager.renderMainScreen();
            break;
        case SETTINGS_MENU:
            displayManager.clear();
            drawMenuItems();
            break;
        case FUNC1_STATE:
            displayManager.clear();
            displayManager.drawSineWave();
            displayManager.update();
            break; 
    }
}

void Menu::navigateUp() {
    if (currentState != MAIN_SCREEN) {
        selectedMenuItem = (selectedMenuItem - 1 + MAX_MENU_ITEMS ) % MAX_MENU_ITEMS;
        update();
    }
}

void Menu::navigateDown() {
    if (currentState != MAIN_SCREEN) {
        selectedMenuItem = (selectedMenuItem + 1) % MAX_MENU_ITEMS;
        update();
    }
}

void Menu::drawMenuItems() {
    displayManager.drawText(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2, 1, menuItems[selectedMenuItem].text);
    displayManager.update();
}

void Menu::select() {
    switch(currentState) {
        case MAIN_SCREEN:
            currentState = SETTINGS_MENU;
            selectedMenuItem = 0;
            update();
            break;
        
        case SETTINGS_MENU:
            if (selectedMenuItem == 1) { currentState = FUNC1_STATE;}
            else if (selectedMenuItem == 4) { currentState = MAIN_SCREEN;}

            update();
            break;
    }
}