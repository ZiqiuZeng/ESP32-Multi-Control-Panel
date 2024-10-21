#ifndef LED_MANAGER_H
#define LED_MANAGER_H

#include <Arduino.h>

/**
 * LEDManager handles LED operations such as turning on/off LEDs based on power and Bluetooth connection status.
 */
class LEDManager
{
public:
    LEDManager(int redPin, int bluePin);         // Constructor to initialize LED pins
    void setupLEDs();                            // Set up LEDs as output
    void setRedLED(bool state);                  // Control red LED
    void setBlueLED(bool state);                 // Control blue LED
    void updateRedLED(bool isPowered);           // Update Red LED based on power status
    void updateBlueLED(bool bluetoothConnected); // Update Blue based on Bluetooth connection

private:
    int redPin;
    int bluePin;
};

#endif