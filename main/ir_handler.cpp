#include "ir_handler.h"

void IRHandler::init() {
    IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);  // Инициализация IR приёма
}

void IRHandler::process() {
    if (IrReceiver.decode()) {
        Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX); // Вывод "старых" данных
        IrReceiver.printIRResultShort(&Serial); // Вывод данных
        IrReceiver.printIRSendUsage(&Serial);   // Вывод команды для отправки данных
        IrReceiver.resume(); // Продолжение приёма
    }
}
