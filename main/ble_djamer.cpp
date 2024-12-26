#include "ble_djamer.h"

void BLE_TOOL::jammer() {
    displayManager.clear();
    displayManager.drawCenteredText("Soon enter to back", 10, 1);
    displayManager.update();
}