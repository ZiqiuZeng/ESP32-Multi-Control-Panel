#include "BluetoothManager.h"
#include <Arduino.h>

BluetoothManager::BluetoothManager() : deviceConnected(false), pServer(nullptr) {}

// Initialize Bluetooth, create the BLE server, and set up connection/disconnection callbacks
void BluetoothManager::init()
{
    BLEDevice::init("ESP32_Bluetooth"); // Initialize the BLE device handle

    pServer = BLEDevice::createServer(); // Create the BLE server

    // Set the callbacks
    pServer->setCallbacks(new MyCallbacks(this));

    startAdvertising(); // Start BLE advertising
}

// Start BLE advertising to make the ESP32 discoverable
void BluetoothManager::startAdvertising()
{
    pServer->getAdvertising()->start(); // Start BLE advertising
    Serial.println("Bluetooth advertising started");
}

// Stop BLE advertising
void BluetoothManager::stopAdvertising()
{
    pServer->getAdvertising()->stop(); // Stop BLE advertising
    Serial.println("Bluetooth advertising stopped");
}

// Return the connection status
bool BluetoothManager::isConnected()
{
    return deviceConnected;
}

// Override onConnect
void MyCallbacks::onConnect(BLEServer *pServer)
{
    Serial.println("Bluetooth device connected!");
    manager->deviceConnected = true;
}

// Override onDisconnect
void MyCallbacks::onDisconnect(BLEServer *pServer)
{
    Serial.printf("Bluetooth device disconnected!");
    manager->deviceConnected = false;
}
