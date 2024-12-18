// wifi.h
#ifndef WIFI_TOOL_H
#define WIFI_TOOL_H

#include <WiFi.h>
#include "display.h"

class WIFI_TOOL {
public:
    void checkNetworks();
};

extern WIFI_TOOL wifi_tool;

#endif