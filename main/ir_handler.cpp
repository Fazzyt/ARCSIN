#include "ir_handler.h"

void IRHandler::init() {
    IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);  // Инициализация IR приёма
    IrSender.begin(IR_TRANSMIT_PIN);// Инициализация IR передачи
}

void IRHandler::process() {
    displayManager.clear();
    if (IrReceiver.decode()) {
        // Получение протокола
        String protocol = String(IrReceiver.decodedIRData.protocol);
        String data = String(IrReceiver.decodedIRData.decodedRawData, HEX);

        // Вывод данных и протокола на экран
        displayManager.drawText(0, 10, 1, "Protocol: " + protocol);
        displayManager.drawText(0, 20, 1, "HEX code: " + data);
        displayManager.update();

        IrReceiver.resume();
    }
}

void IRHandler::transmit() {
    IrSender.sendNEC(0xEF00, 0x3);
}