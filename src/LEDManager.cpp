#include "LEDManager.h"

// Constructor to initialize LED pins
LEDManager::LEDManager(int redPin, int bluePin) : redPin(redPin), bluePin(bluePin) {}

// Set up the LED pins as output
void LEDManager::setupLEDs()
{
    pinMode(redPin, OUTPUT);
    pinMode(bluePin, OUTPUT);
}

// Control the red LED based on power status
void LEDManager::setRedLED(bool state)
{
    digitalWrite(redPin, state ? HIGH : LOW);
}

// Control the blue LED based on Bluetooth connection
void LEDManager::setBlueLED(bool state)
{
    digitalWrite(bluePin, state ? HIGH : LOW);
}

// Update red LED based on power status
void LEDManager::updateRedLED(bool isPowered)
{
    setRedLED(isPowered);
}

// Update blue LED based on Bluetooth connection
void LEDManager::updateBlueLED(bool bluetoothConnected)
{
    setBlueLED(bluetoothConnected);
}
