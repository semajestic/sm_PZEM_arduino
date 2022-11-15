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
#define PZEM_RX_PIN 19//16
#define PZEM_TX_PIN 22//17
#endif

#define PZEM_SERIAL Serial2
#define CONSOLE_SERIAL Serial
PZEM004Tv30 pzem1(PZEM_SERIAL, PZEM_RX_PIN, PZEM_TX_PIN);
#endif

#define but_up 35
#define but_down 32
#define but_enter 34
#define led_green 18
#define led_red 5
uint8_t adr_counter = 0x00;

void setup() {
    CONSOLE_SERIAL.begin(115200);
    //PZEM_SERIAL.begin(115200,SERIAL_8N1,17,16);
    
    CONSOLE_SERIAL.println("ESP32 Start");
    pinMode(but_up,INPUT);
    pinMode(but_down,INPUT);
    pinMode(but_enter,INPUT);
    pinMode(led_green, OUTPUT);
    pinMode(led_red, OUTPUT);

    for (int i=0;i<5;i++){
      digitalWrite(led_green,HIGH);
      digitalWrite(led_red,HIGH);
      delay(100);
      digitalWrite(led_green,LOW);
      digitalWrite(led_red,LOW);
      delay(100);
    }
    digitalWrite(led_green,HIGH);
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
        digitalWrite(led_red, HIGH);
        adr_counter++;
        CONSOLE_SERIAL.print("new address: ");
        CONSOLE_SERIAL.println(adr_counter,HEX);
        delay(250);
        digitalWrite(led_red, LOW);
    }
    if (digitalRead(but_down)==HIGH){
        digitalWrite(led_red, HIGH);
        adr_counter--;
        CONSOLE_SERIAL.print("new address: ");
        CONSOLE_SERIAL.println(adr_counter,HEX);
        delay(250);
        digitalWrite(led_red, LOW);
    }
    if (digitalRead(but_enter)==HIGH){
        //digitalWrite(led_red, HIGH);
        CONSOLE_SERIAL.print("selected address: ");
        CONSOLE_SERIAL.println(adr_counter,HEX);
        
        CONSOLE_SERIAL.print("PZEM Current Address:");     
        CONSOLE_SERIAL.println(pzem1.readAddress(), HEX);
    
        // Change PZEM Address here.
        pzem1.setAddress(adr_counter);

        CONSOLE_SERIAL.print("PZEM New Address:");     
        int newaddr = pzem1.readAddress();
        CONSOLE_SERIAL.println(newaddr, HEX);
        
        adr_counter=0;
        
        for (int i=0;i<newaddr;i++){
            digitalWrite(led_red, HIGH);
            delay(250);
            digitalWrite(led_red, LOW);
            delay(250);
        }
        
    }
}
