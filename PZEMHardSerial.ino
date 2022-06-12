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
PZEM004Tv30 pzem1(PZEM_SERIAL, PZEM_RX_PIN, PZEM_TX_PIN, 0x01);
PZEM004Tv30 pzem2(PZEM_SERIAL, PZEM_RX_PIN, PZEM_TX_PIN, 0x02);
#endif

void setup() {
    // Debugging Serial port
    CONSOLE_SERIAL.begin(115200);

    CONSOLE_SERIAL.println("ESP32 Start");
    CONSOLE_SERIAL.print("PZEM1 Current Address:");     CONSOLE_SERIAL.print(pzem1.readAddress(), HEX);
    CONSOLE_SERIAL.print(" PZEM2 Current Address:");     CONSOLE_SERIAL.println(pzem2.readAddress(), HEX);
    
    // pzem1.setAddress(0x01);
    // CONSOLE_SERIAL.print("PZEM1 New Address:");     CONSOLE_SERIAL.print(pzem1.readAddress(), HEX);

    // Uncomment in order to reset the internal energy counter
    // pzem1.resetEnergy()
}

void loop() {
    // Print the custom address of the PZEM
    CONSOLE_SERIAL.print("PZEM1 Address:");     CONSOLE_SERIAL.println(pzem1.readAddress(), HEX);     
    // Read the data from the sensor
    float pzem1_voltage = pzem1.voltage();
    float pzem1_current = pzem1.current();
    float pzem1_power = pzem1.power();
    float pzem1_energy = pzem1.energy();
    float pzem1_frequency = pzem1.frequency();
    float pzem1_pf = pzem1.pf();

    // Check if the data is valid
    if(isnan(pzem1_voltage)){
        CONSOLE_SERIAL.println("Error reading voltage");
    } else if (isnan(pzem1_current)) {
        CONSOLE_SERIAL.println("Error reading current");
    } else if (isnan(pzem1_power)) {
        CONSOLE_SERIAL.println("Error reading power");
    } else if (isnan(pzem1_energy)) {
        CONSOLE_SERIAL.println("Error reading energy");
    } else if (isnan(pzem1_frequency)) {
        CONSOLE_SERIAL.println("Error reading frequency");
    } else if (isnan(pzem1_pf)) {
        CONSOLE_SERIAL.println("Error reading power factor");
    } else {

        // Print the values to the Serial console
        CONSOLE_SERIAL.print("Voltage: ");      CONSOLE_SERIAL.print(pzem1_voltage);      CONSOLE_SERIAL.println("V");
        CONSOLE_SERIAL.print("Current: ");      CONSOLE_SERIAL.print(pzem1_current);      CONSOLE_SERIAL.println("A");
        CONSOLE_SERIAL.print("Power: ");        CONSOLE_SERIAL.print(pzem1_power);        CONSOLE_SERIAL.println("W");
        CONSOLE_SERIAL.print("Energy: ");       CONSOLE_SERIAL.print(pzem1_energy,3);     CONSOLE_SERIAL.println("kWh");
        CONSOLE_SERIAL.print("Frequency: ");    CONSOLE_SERIAL.print(pzem1_frequency, 1); CONSOLE_SERIAL.println("Hz");
        CONSOLE_SERIAL.print("PF: ");           CONSOLE_SERIAL.println(pzem1_pf);

    }

    // Print the custom address of the PZEM
    CONSOLE_SERIAL.print("PZEM2 Address:");     CONSOLE_SERIAL.println(pzem2.readAddress(), HEX); 
    
    // Read the data from the sensor
    float pzem2_voltage = pzem2.voltage();
    float pzem2_current = pzem2.current();
    float pzem2_power = pzem2.power();
    float pzem2_energy = pzem2.energy();
    float pzem2_frequency = pzem2.frequency();
    float pzem2_pf = pzem2.pf();


    // Check if data is valid
    if(isnan(pzem2_voltage)){
        CONSOLE_SERIAL.println("Error reading voltage");
    } else if (isnan(pzem2_current)) {
        CONSOLE_SERIAL.println("Error reading current");
    } else if (isnan(pzem2_power)) {
        CONSOLE_SERIAL.println("Error reading power");
    } else if (isnan(pzem2_energy)) {
        CONSOLE_SERIAL.println("Error reading energy");
    } else if (isnan(pzem2_frequency)) {
        CONSOLE_SERIAL.println("Error reading frequency");
    } else if (isnan(pzem2_pf)) {
        CONSOLE_SERIAL.println("Error reading power factor");
    } else {

        // Print the values to the Serial console
        CONSOLE_SERIAL.print("Voltage: ");      CONSOLE_SERIAL.print(pzem2_voltage);      CONSOLE_SERIAL.println("V");
        CONSOLE_SERIAL.print("Current: ");      CONSOLE_SERIAL.print(pzem2_current);      CONSOLE_SERIAL.println("A");
        CONSOLE_SERIAL.print("Power: ");        CONSOLE_SERIAL.print(pzem2_power);        CONSOLE_SERIAL.println("W");
        CONSOLE_SERIAL.print("Energy: ");       CONSOLE_SERIAL.print(pzem2_energy,3);     CONSOLE_SERIAL.println("kWh");
        CONSOLE_SERIAL.print("Frequency: ");    CONSOLE_SERIAL.print(pzem2_frequency, 1); CONSOLE_SERIAL.println("Hz");
        CONSOLE_SERIAL.print("PF: ");           CONSOLE_SERIAL.println(pzem2_pf);

    }

    CONSOLE_SERIAL.println();
    delay(2000);
}
