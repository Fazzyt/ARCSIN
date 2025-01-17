#ifndef IR_HANDLER_H
#define IR_HANDLER_H

#define USE_IRREMOTE_HPP_AS_PLAIN_INCLUDE
#include <IRremote.hpp>

#include "config.h"
#include "display.h"

class IRHandler {
public:
    void init();
    void process();

};

extern IRHandler irHandler;

#endif // IR_HANDLER_H
