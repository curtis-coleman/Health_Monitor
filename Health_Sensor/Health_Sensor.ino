#include <EEPROM.h>
#include <LLAPSerial.h>

#define DEVICE_ID "MO"
#define INTERVAL_MESSAGES 3000

LLAPSerial LLAP(Serial);

void setup()
{
    Serial.begin(115200);

    LLAP.begin(DEVICE_ID);
}

void loop()
{
    static int i = 0;
    static unsigned long timeout = millis() + INTERVAL_MESSAGES;

    // You will need this if AUTO_SERIAL_EVENT is not defined
    // and your node needs to receive messages or uses dynamic addressing (like this one)
    LLAP.SerialEvent();

    // Avoid using "delay" as it will interfere with serial data
    if (timeout < millis()) {
        LLAP.sendMessage("VAL", i++);
        timeout = millis() + INTERVAL_MESSAGES;
    }
}
