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

#define but_down 32
#define but_enter 34
#define but_up 35
uint8_t adr_counter = 0x00;

void setup() {
    CONSOLE_SERIAL.begin(115200);
    
    CONSOLE_SERIAL.println("ESP32 Start");
    pinMode(but_up,INPUT_PULLUP);
    pinMode(but_down,INPUT_PULLUP);
    pinMode(but_enter,INPUT_PULLUP);
    /*
    CONSOLE_SERIAL.print("PZEM Current Address:");     CONSOLE_SERIAL.print(pzem1.readAddress(), HEX);
    
    // Change PZEM Address here.
    pzem1.setAddress(0x02);

    CONSOLE_SERIAL.print("PZEM New Address:");     CONSOLE_SERIAL.print(pzem1.readAddress(), HEX);
*/
}

void loop() {
//    CONSOLE_SERIAL.println("new");
    
    if (digitalRead(but_up)==HIGH){
        adr_counter++;
        CONSOLE_SERIAL.print("new address: ");
        CONSOLE_SERIAL.println(adr_counter,HEX);
        delay(250);
    }
    if (digitalRead(but_down)==HIGH){
        adr_counter--;
        CONSOLE_SERIAL.print("new address: ");
        CONSOLE_SERIAL.println(adr_counter,HEX);
        delay(250);
    }
    if (digitalRead(but_enter)==HIGH){
        CONSOLE_SERIAL.print("selected address: ");
        CONSOLE_SERIAL.print(adr_counter,HEX);
        
        CONSOLE_SERIAL.print(" PZEM Current Address:");     CONSOLE_SERIAL.print(pzem1.readAddress(), HEX);
    
        // Change PZEM Address here.
        pzem1.setAddress(adr_counter);

        CONSOLE_SERIAL.print(" PZEM New Address:");     CONSOLE_SERIAL.println(pzem1.readAddress(), HEX);

        //        adr_counter=0;
        delay(250);
    }
}
