#ifndef TASK_MANAGER_H
#define TASK_MANAGER_H

#include "WiFiManager.h"
#include "BluetoothManager.h"
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

class TaskManager
{
public:
    bool isPowered;
    TaskManager();                                 // Constructor to initialize the TaskManager
    void startTasks();                             // Starts all tasks
    void stopTasks();                              // Stops all tasks
    static void wifiTask(void *pvParameters);      // WiFi management task
    static void bluetoothTask(void *pvParameters); // Bluetooth management task
    static void ledTask(void *pvParameters);       // LED management task (example)

private:
    TaskHandle_t wifiTaskHandle; // Task handle for WiFi
    TaskHandle_t btTaskHandle;   // Task handle for Bluetooth
    TaskHandle_t ledTaskHandle;  // Task handle for LED (optional)
};

#endif