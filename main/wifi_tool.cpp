#include "wifi_tool.h"

void WIFI_TOOL::checkNetworksAsync() {
    static int step = 0;
    static unsigned long lastUpdate = 0;
    static int networksFound = -1;
    static int currentNetwork = 0;
    static int progress = 0;
    static String networkInfo[30];

    unsigned long now = millis();

    if (step == 0) {
        displayManager.clear();
        displayManager.drawCenteredText("Scanning WiFi...", 10, 1);
        displayManager.update();
        networksFound = WiFi.scanNetworks();

        if (networksFound == 0) {
            displayManager.clear();
            displayManager.drawCenteredText("No networks found", 20, 1);
            displayManager.update();
            step = -1;
        } else {
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
            step = 1;
            currentNetwork = 0;
            progress = 0;
            lastUpdate = now;
        }
    } else if (step == 1) {
        if (now - lastUpdate > 100) {
            displayManager.clear();
            displayManager.drawText(0, 0, 1, networkInfo[currentNetwork]);
            displayManager.drawProgressBar(progress + 1, 30);
            displayManager.update();

            progress++;
            lastUpdate = now;

            if (progress >= 30) {
                progress = 0;
                currentNetwork++;
                if (currentNetwork >= networksFound) {
                    step = -1;
                }
            }
        }
    } else if (step == -1) {
        step = 0;
    }
}
