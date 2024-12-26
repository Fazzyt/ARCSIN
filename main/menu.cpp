#include "menu.h"
#include "display.h"

Menu::Menu() : 
    currentState(MAIN_SCREEN), 
    selectedMenuItem(0) {
    // Инициализация пунктов меню
    menuItems[0] = {"Sinus"};
    menuItems[1] = {"WIFI SCAN"};
    menuItems[2] = {"BLE soon"};
    menuItems[3] = {"Exit"}; // Выход
}

void Menu::init() {
    currentState = MAIN_SCREEN;
}

void Menu::update() {
    switch(currentState) {
        case MAIN_SCREEN: {
            displayManager.clear();
            displayManager.drawText(65, 32, 1,"ARCSIN");
            displayManager.drawSineWave(0);
            displayManager.update();
            break;
            }

        case SETTINGS_MENU: {
            displayManager.clear();
            drawMenuItems();
            break;
            }

        case SIN_STATE: {
            displayManager.clear(); 
            displayManager.drawSineWave(phaseShift);
            displayManager.update();

            phaseShift += 0.1;

            if (phaseShift >= 15){
                phaseShift = 0;
            }

            break;
            }

        case WIFI_SCAN_STATE: {
            wifi_tool.checkNetworksAsync(); 
            break;
            }

        case BLUEJACKING_TOOL_STATE: {
            ble_tool.jammer();
            break;
            }
    }
}

void Menu::navigateUp() {
    if (currentState != MAIN_SCREEN) {
        selectedMenuItem = (selectedMenuItem - 1 + MAX_MENU_ITEMS ) % MAX_MENU_ITEMS;
    }
}

void Menu::navigateDown() {
    if (currentState != MAIN_SCREEN) {
        selectedMenuItem = (selectedMenuItem + 1) % MAX_MENU_ITEMS;
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
            break;

        case SETTINGS_MENU:
            if (selectedMenuItem == 0) { currentState = SIN_STATE;}
            else if (selectedMenuItem == 1) { currentState = WIFI_SCAN_STATE;}
            else if (selectedMenuItem == 2) { currentState = BLUEJACKING_TOOL_STATE;}
            else if (selectedMenuItem == 3) { currentState = MAIN_SCREEN;}
            break;

        case SIN_STATE:
            currentState = SETTINGS_MENU;
            selectedMenuItem = 0;
            break;

        case WIFI_SCAN_STATE:
            currentState = SETTINGS_MENU;
            selectedMenuItem = 1;
            break;

        case BLUEJACKING_TOOL_STATE:
            currentState = SETTINGS_MENU;
            selectedMenuItem = 2;
    }
}