#include "menu.h"
#include "display.h"

Menu::Menu() : 
    currentState(MAIN_SCREEN), 
    selectedMenuItem(0) {
    // Инициализация пунктов меню
    menuItems[0] = {"Sinus", nullptr};
    menuItems[1] = {"WIFI SCAN", nullptr};
    menuItems[2] = {"Func 3", nullptr};
    menuItems[3] = {"Exit", nullptr}; // Выход без действия
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
        case SIN_STATE:
            displayManager.clear();
            displayManager.drawSineWave();
            displayManager.update();
            break; 
        case WIFI_SCAN_STATE:
            wifi_tool.checkNetworks(); 
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
            if (selectedMenuItem == 0) { currentState = SIN_STATE;}
            else if (selectedMenuItem == 1) { currentState = WIFI_SCAN_STATE;}
            else if (selectedMenuItem == 3) { currentState = MAIN_SCREEN;}

            update();
            break;
            
        case SIN_STATE:
            currentState = SETTINGS_MENU;
            selectedMenuItem = 0;
            update();
            break;
        
        case WIFI_SCAN_STATE:
            currentState = SETTINGS_MENU;
            selectedMenuItem = 0;
            update();
            break;
    }
}