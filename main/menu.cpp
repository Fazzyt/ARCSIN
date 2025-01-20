#include "menu.h"
#include "display.h"

Menu::Menu() : 
    currentState(MAIN_SCREEN), 
    selectedMenuItem(0) {
    // Инициализация пунктов меню
    menuItems[0] = {"Sinus"};
    menuItems[1] = {"WIFI SCAN"};
    menuItems[2] = {"BLE soon"};
    menuItems[3] = {"IR receiver"};
    menuItems[4] = {"IR transmitter"};
    menuItems[5] = {"Exit"}; // Выход
}

void Menu::init() {
    currentState = MAIN_SCREEN;
}

void Menu::update() {
    switch(currentState) {
        case MAIN_SCREEN:
            displayManager.clear();
            displayManager.drawCenteredText("ARCSIN", SCREEN_HEIGHT / 2, 1);
            displayManager.drawBatteryIcon(5, 0, 15, 8, 1);
            displayManager.update();
            break;

        case SETTINGS_MENU:
            displayManager.clear();
            drawMenuItems();
            break;

        case SIN_STATE:
            displayManager.clear(); 
            displayManager.drawSineWave(phaseShift);
            displayManager.update();
            /*
            phaseShift += 0.1;

            if (phaseShift >= 15){
                phaseShift = 0;
            }
            */
            break;

        case WIFI_SCAN_STATE:
            wifi_tool.checkNetworksAsync(); 
            break;

        case BLUEJACKING_TOOL_STATE:
            ble_tool.jammer();
            break;
        
        case IR_RECEIVE_STATE:
            irHandler.receiver();
            break;
        
        case IR_TRANSMIT_STATE:
            displayManager.clear(); 
            displayManager.drawText(0, 32, 1, "go to transmit");
            displayManager.update();
            break;
    }
}

void Menu::navigateUp() {
    switch(currentState) {
        case SETTINGS_MENU:
            selectedMenuItem = (selectedMenuItem - 1 + MAX_MENU_ITEMS ) % MAX_MENU_ITEMS;
            break;
        case IR_RECEIVE_STATE:
            irHandler.receiver_resume();
            break;
    }
}

void Menu::navigateDown() {
    switch(currentState) {
        case SETTINGS_MENU:
            selectedMenuItem = (selectedMenuItem + 1) % MAX_MENU_ITEMS;
            break;
        
        case IR_TRANSMIT_STATE:
            irHandler.transmit();
            break;
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
            else if (selectedMenuItem == 3) { currentState = IR_RECEIVE_STATE;}
            else if (selectedMenuItem == 4) { currentState = IR_TRANSMIT_STATE;}
            else if (selectedMenuItem == 5) { currentState = MAIN_SCREEN;}
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
            break;
        
        case IR_RECEIVE_STATE:
            currentState = SETTINGS_MENU;
            selectedMenuItem = 3;
            break;
        
        case IR_TRANSMIT_STATE:
            currentState = SETTINGS_MENU;
            selectedMenuItem = 4;
            break;
    }
}