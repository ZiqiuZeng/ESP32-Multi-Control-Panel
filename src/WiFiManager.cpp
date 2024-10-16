#include "WiFiManager.h"
#include <WiFi.h>
#include <Preferences.h>

Preferences preferences;  // Create a Preferences object

// Load stored default credentials from non-volatile memory
WiFiManager::WiFiManager() {
    loadDefaultCredentials();
}

// Set ESP32 as station
void WiFiManager::init() {
    WiFi.mode(WIFI_STA);  
}

// Scan accessible networks
void WiFiManager::scanNetworks() {
    int n = WiFi.scanNetworks();
    Serial.println("Scanning... Please Wait...");
    if (n == 0) {
        Serial.println("No networks found");
    } else {
        for (int i = 0; i < n; i++) {
            Serial.printf("%d: %s (%d dBm)\n", i + 1, WiFi.SSID(i).c_str(), WiFi.RSSI(i));
        }
    }
}

// Connect ESP32 to the selected network
void WiFiManager::connectToNetwork(int selectedNetwork) {
    this->selectedNetwork = selectedNetwork;
    WiFi.begin(WiFi.SSID(selectedNetwork).c_str());

    int retryCount = 0;
    while (WiFi.status() != WL_CONNECTED && retryCount < 5) {
        delay(1000);
        retryCount++;
        Serial.printf("Attempting to connect... %d\n", retryCount);
    }

    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("Successfully connected to WiFi");
        Serial.println(WiFi.localIP());
    } else {
        Serial.println("Failed to connect");
    }
}

// Connect ESP32 to default network
void WiFiManager::connectToDefault() {
    WiFi.begin(defaultSSID, defaultPassword);

    int retryCount = 0;
    while (WiFi.status() != WL_CONNECTED && retryCount < 5) {
        delay(1000);
        retryCount++;
        Serial.printf("Connecting to default network... %d\n", retryCount);
    }

    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("Successfully connected to default WiFi");
        Serial.println(WiFi.localIP());
    } else {
        Serial.println("Failed to connect to default WiFi");
    }
}

// Detect Wifi status
bool WiFiManager::isConnected() {
    return WiFi.status() == WL_CONNECTED;
}

// Reconnect to WiFi
void WiFiManager::reconnect() {
    if (!isConnected()) {
        WiFi.reconnect();
    }
}

// Disconnect to WiFi
void WiFiManager::disconnect() {
    WiFi.disconnect();
}

// Load default credentials from non-volatile storage
void WiFiManager::loadDefaultCredentials() {
    preferences.begin("wifi-creds", true);  // Open preferences in read-only mode
    defaultSSID = preferences.getString("ssid", "default_ssid").c_str();
    defaultPassword = preferences.getString("password", "default_password").c_str();
    preferences.end();
}

// Save new default credentials to non-volatile storage
void WiFiManager::saveDefaultCredentials(const char* ssid, const char* password) {
    preferences.begin("wifi-creds", false);  // Open preferences in read-write mode
    preferences.putString("ssid", ssid);
    preferences.putString("password", password);
    preferences.end();
    
    // Update default credentials in memory
    defaultSSID = ssid;
    defaultPassword = password;
    Serial.println("Default WiFi credentials updated");
}
