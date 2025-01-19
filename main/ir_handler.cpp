#include "ir_handler.h"

void IRHandler::init() {
    IrReceiver.begin(IR_RECEIVE_PIN, false);  // Инициализация IR приёма
    IrSender.begin(IR_TRANSMIT_PIN); // Инициализация IR передачи
    IrSender.enableIROut(38); // Установка частоты IR передачи 38 kNz
}

void IRHandler::process() {
    displayManager.clear();

    if (IrReceiver.decode()) {
        // Форматирование строки для вывода
        String protocol = String(getProtocolString(IrReceiver.decodedIRData.protocol));
        String addressStr = String(IrReceiver.decodedIRData.address, HEX);
        String commandStr = String(IrReceiver.decodedIRData.command, HEX);
        String rawDataStr = String(IrReceiver.decodedIRData.decodedRawData, HEX);

        // Вывод данных на экран
        displayManager.drawText(0, 2, 1, "Protocol: " + protocol);
        displayManager.drawText(0, 12, 1, "Address: " + addressStr);
        displayManager.drawText(0, 22, 1, "Command: " + commandStr);
        displayManager.drawText(0, 32, 1, "RawData: " + rawDataStr);
        displayManager.update();

        IrReceiver.resume(); // Подготовка приёмника к следующему сигналу
    }
}


void IRHandler::transmit() {
    displayManager.clear();

    IrSender.sendNEC(0xEF00, 0x3, 1);
    IrReceiver.restartAfterSend();

    displayManager.drawCenteredText("Sent: ef00 cmd: 3", SCREEN_HEIGHT - 7, 1);
    displayManager.update();
}
