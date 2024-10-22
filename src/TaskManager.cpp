#include "TaskManager.h"
#include "WiFiManager.h"
#include "BluetoothManager.h"
#include "LEDManager.h"
#include "PinConfig.h"
#include <Arduino.h>

WiFiManager wifiManager;
BluetoothManager bluetoothManager;
LEDManager ledManager(RED_LED_PIN, BLUE_LED_PIN);

// Initialize task handles to NULL
TaskManager::TaskManager() : wifiTaskHandle(NULL), btTaskHandle(NULL), ledTaskHandle(NULL) {}

// Start all tasks (WiFi, Bluetooth, and optionally LED)
void TaskManager::startTasks()
{
    // Create WiFi task
    xTaskCreate(
        wifiTask,       // Task function
        "WiFi Task",    // Name of the task
        4096,           // Stack size (adjust based on task complexity)
        NULL,           // Parameters (none for now)
        1,              // Priority (1 is default, increase for more critical tasks)
        &wifiTaskHandle // Handle to the created task
    );

    // Create Bluetooth task
    xTaskCreate(
        bluetoothTask,
        "Bluetooth Task",
        4096,
        NULL,
        1,
        &btTaskHandle);

    // Create LED task
    xTaskCreate(
        ledTask,
        "LED Task",
        1024,
        (void *)&isPowered,
        1,
        &ledTaskHandle);
}

// Stop all tasks (WiFi, Bluetooth, and optionally LED)
void TaskManager::stopTasks()
{
    // Delete the WiFi task
    if (wifiTaskHandle != NULL)
    {
        vTaskDelete(wifiTaskHandle);
        wifiTaskHandle = NULL;
    }

    // Delete the Bluetooth task
    if (btTaskHandle != NULL)
    {
        vTaskDelete(btTaskHandle);
        btTaskHandle = NULL;
    }

    // Optional: Delete LED task
    if (ledTaskHandle != NULL)
    {
        vTaskDelete(ledTaskHandle);
        ledTaskHandle = NULL;
    }
}

// WiFi Task function: Manages WiFi connections in the background
void TaskManager::wifiTask(void *pvParameters)
{
    wifiManager.init();

    while (true)
    {
        wifiManager.connectToStoredWiFi();
        vTaskDelay(10000 / portTICK_PERIOD_MS);
    }
}

// Bluetooth Task function: Handles Bluetooth communication
void TaskManager::bluetoothTask(void *pvParameters)
{
    bluetoothManager.init();
    while (true)
    {
        if (bluetoothManager.isConnected())
        {
            continue;
        }
        else
        {
            // No device connected, keep advertising
            bluetoothManager.startAdvertising();
        }

        vTaskDelay(5000 / portTICK_PERIOD_MS); // Check connection status every 5 seconds
    }
}

// LED Task function: Manage LED status (e.g., WiFi and Bluetooth status indicators)
void TaskManager::ledTask(void *pvParameters)
{
    bool *isPowered = (bool *)pvParameters;

    ledManager.setupLEDs();
    while (true)
    {
        if (bluetoothManager.isConnected())
        {
            ledManager.setBlueLED(true);
        }
        else
        {
            ledManager.setBlueLED(false);
        }

        if (*isPowered)
        {
            ledManager.setRedLED(true);
        }
        else
        {
            ledManager.setRedLED(false);
        }

        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}
