#ifndef BLUETOOTH_MANAGER_H
#define BLUETOOTH_MANAGER_H

#include <BLEDevice.h>      
#include <BLEServer.h>      

class BluetoothManager {
public:
    BluetoothManager();  // Constructor
    void init();  // Initialize Bluetooth and start advertising
    void startAdvertising();  // Start BLE advertising
    void stopAdvertising();   // Stop BLE advertising
    bool isConnected();       // Check if a BLE device is connected

private:
    BLEServer* pServer;       // Pointer to the BLE server instance
    bool deviceConnected;     // Track Bluetooth connection status
    friend class MyCallbacks;
};

class MyCallbacks : public BLEServerCallbacks {
private:
    BluetoothManager* manager;  // Pointer to BluetoothManager

public:
    // Constructor
    MyCallbacks(BluetoothManager* m) : manager(m) {}

    // Override onConnect: Called when a Bluetooth device connects
    void onConnect(BLEServer* pServer) override;

    // Override onDisconnect: Called when a Bluetooth device disconnects
    void onDisconnect(BLEServer* pServer) override;
};

#endif

