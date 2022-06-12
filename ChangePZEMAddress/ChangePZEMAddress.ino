/*
Copyright (c) 2021 Jakub Mandula

Example of using one PZEM module with Hardware Serial interface.
================================================================

If desired, a HardwareSerial handle can be passed to the constructor
which will then be used for the communication with the module.

Note that ESP32 HardwareSerial must also be provided with the RX and TX
pins.

*/
#include <Arduino.h>
#include "PZEM004Tv30.h"

#if defined(ESP32)
/*************************
 *  ESP32 initialization
 * ---------------------
 * 
 * The ESP32 HW Serial interface can be routed to any GPIO pin 
 * Here we initialize the PZEM on Serial2 with RX/TX pins 16 and 17
 */
#if !defined(PZEM_RX_PIN) && !defined(PZEM_TX_PIN)
#define PZEM_RX_PIN 16
#define PZEM_TX_PIN 17
#endif

#define PZEM_SERIAL Serial2
#define CONSOLE_SERIAL Serial
PZEM004Tv30 pzem1(PZEM_SERIAL, PZEM_RX_PIN, PZEM_TX_PIN);
#endif

void setup() {
    CONSOLE_SERIAL.begin(115200);

    CONSOLE_SERIAL.println("ESP32 Start");

    CONSOLE_SERIAL.print("PZEM Current Address:");     CONSOLE_SERIAL.print(pzem1.readAddress(), HEX);
    
    // Change PZEM Address here.
    pzem1.setAddress(0x02);

    CONSOLE_SERIAL.print("PZEM New Address:");     CONSOLE_SERIAL.print(pzem1.readAddress(), HEX);

}

void loop() {

}