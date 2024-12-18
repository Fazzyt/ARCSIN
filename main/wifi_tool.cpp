#include "wifi_tool.h"

void WIFI_TOOL::checkNetworks() {
    displayManager.clear();
    displayManager.drawCenteredText("Scanning WiFi...", 10, 1);
    displayManager.update();

    int networksFound = WiFi.scanNetworks();
    displayManager.clear();

    if (networksFound == 0) {
        displayManager.drawCenteredText("No networks found", 20, 1);
    } else {
        String networkInfo[30];
        for (int i = 0; i < networksFound; i++) {
            String ssid = WiFi.SSID(i);
            int rssi = WiFi.RSSI(i);
            String encryptionType = WiFi.encryptionType(i) == WIFI_AUTH_OPEN ? "Open" : "Secured";
            String macAddress = WiFi.BSSIDstr(i);

            networkInfo[i] = "SSID " + ssid + "\n\n" +
                             "RSSI " + String(rssi) + " dBm\n\n" +
                             "Type " + encryptionType + "\n\n" +
                             "MAC " + macAddress;
        }

        for (int i = 0; i < networksFound; i++) {
            displayManager.clear();
            displayManager.drawText(0, 0, 1, networkInfo[i]);
            for (int j = 0; j < 30; j++) {
                displayManager.drawProgressBar(j + 1, 30);
                displayManager.update();
                delay(100);
            }
        }
    }
    displayManager.update();
}