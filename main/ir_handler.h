#ifndef IR_HANDLER_H
#define IR_HANDLER_H

#include <IRremote.hpp>

#include "config.h"
#include "display.h"

class IRHandler {
public:
    void init();
    void receiver();
    void receiver_resume();
    void transmit();

private:
    String data;
};

extern IRHandler irHandler;

#endif // IR_HANDLER_H
