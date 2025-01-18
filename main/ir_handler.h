#ifndef IR_HANDLER_H
#define IR_HANDLER_H

#include <IRremote.hpp>

#include "config.h"
#include "display.h"

class IRHandler {
public:
    void init();
    void process();
    void transmit();
    void stop_receiver();
    void start_receiver();

private:
    String data;
};

extern IRHandler irHandler;

#endif // IR_HANDLER_H
