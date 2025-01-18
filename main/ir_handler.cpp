#include "ir_handler.h"

void IRHandler::init() {
    IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);  // Инициализация IR приёма
    IrSender.begin(IR_TRANSMIT_PIN); // Инициализация IR передачи
    IrSender.enableIROut(38); // Установка частоты IR передачи 38 kNz
}

void IRHandler::process() {
    displayManager.clear();

    if (IrReceiver.decode()) {
        // Получение данных от приёмника
        uint16_t address = (IrReceiver.decodedIRData.decodedRawData >> 16) & 0xFFFF; // Старшие 16 бит (адрес)
        uint16_t command = IrReceiver.decodedIRData.decodedRawData & 0xFFFF; // Младшие 16 бит (команда)

        // Вывод данных на экран
        String protocol = String(IrReceiver.decodedIRData.protocol);
        String addressStr = String(address, HEX);
        String commandStr = String(command, HEX);

        displayManager.drawText(0, 10, 1, "Protocol: " + protocol);
        displayManager.drawText(0, 16, 1, "Address: " + addressStr);
        displayManager.drawText(0, 22, 1, "Command: " + commandStr);
        displayManager.update();
        
        IrReceiver.resume(); // Подготовка приёмника к следующему сигналу
    }
}

void IRHandler::transmit() {
    displayManager.clear();

    IrSender.sendNEC(0xEF00 & 0xFF, 0x3);

    displayManager.drawCenteredText("send: 200", SCREEN_HEIGHT - 7, 1);
    displayManager.update();
}