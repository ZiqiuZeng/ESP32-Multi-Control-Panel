#include "WiFiManager.h"
#include <WiFi.h>
#include <Preferences.h>

Preferences preferences; // Create Non-Volatile Memory

// Load stored default credentials from non-volatile memory
WiFiManager::WiFiManager()
{
    loadStoredCredentials();
}

// Set ESP32 as station
void WiFiManager::init()
{
    WiFi.mode(WIFI_STA);
}

/*
============================================================
    CREDENTIALS MANAGEMENT SECTION
============================================================
*/

// Save credentials to non-volatile memory
void WiFiManager::saveCredentials()
{
    preferences.begin("wifi-creds", false);
    preferences.putInt("cred_count", credentials.size());

    int i = 0;
    for (const auto &pair : credentials)
    {
        preferences.putString(("ssid_" + String(i)).c_str(), pair.first);
        preferences.putString(("password_" + String(i)).c_str(), pair.second);
        i++;
    }

    preferences.end();
}

// Load credentials from non-volatile memory
void WiFiManager::loadStoredCredentials()
{
    preferences.begin("wifi-creds", true);
    int credentialCount = preferences.getInt("cred_count", 0);

    for (int i = 0; i < credentialCount; i++)
    {
        String ssid = preferences.getString(("ssid_" + String(i)).c_str());
        String password = preferences.getString(("password_" + String(i)).c_str());
        credentials[ssid] = password;
    }

    preferences.end();
}

// Add new WiFi credentials
void WiFiManager::addWiFiCredential(const char *ssid, const char *password)
{
    credentials[ssid] = password;
    Serial.printf("Added WiFi credentials for SSID: %s", ssid);
}

// Remove WiFi Credentials
void WiFiManager::removeWiFiCredential(const char *ssid)
{
    if (credentials.erase(ssid))
    {
        Serial.printf("Removed WiFi credentials for SSID: %s\n", ssid);
    }
    else
    {
        Serial.printf("SSID: %s not found in stored credentials.\n", ssid);
    }
}

// List all stored WiFi Credentials
void WiFiManager::listStoredCredentials()
{
    Serial.println("Stored WiFi credentials:");
    int i;
    for (const auto &pair : credentials)
    {
        Serial.printf("%d: SSID: %s\n", i + 1, pair.first.c_str());
        i++;
    }
}

/*
============================================================
    WIFI CONNECTION SECTION
============================================================
*/

// Check if there are any available WiFi networks
bool WiFiManager::isWiFiAvailable()
{
    return WiFi.scanNetworks() > 0;
}

// Try connecting to stored WiFi credentials in order of signal strength
void WiFiManager::connectToStoredWiFi()
{
    scanForNetworks();

    for (const auto &available : availables)
    {
        auto it = credentials.find(available.ssid);
        if (it != credentials.end())
        {
            const String &password = it->second;
            Serial.printf("Attempting to connect to %s\n", available.ssid.c_str());
            connectToSelectedWiFi(available.ssid, password);
        }
    }
}

void WiFiManager::connectToSelectedWiFi(const String ssid, const String password)
{
    WiFi.begin(ssid.c_str(), password.c_str());
    int retryCount = 0;

    while (WiFi.status() != WL_CONNECTED && retryCount < 5)
    {
        vTaskDelay(1000 / portTICK_PERIOD_MS); // Non-blocking delay
        retryCount++;
        Serial.printf("Connecting to %s, attempt %d...\n", ssid.c_str(), retryCount);
    }

    Serial.printf("Connection to %s failed :(");
}

// Scan accessible networks
void WiFiManager::scanForNetworks()
{
    Serial.println("Scanning starts... Please Wait...");

    availables.clear(); // Clear previous scan results

    int networkCount = WiFi.scanNetworks();

    if (!isWiFiAvailable())
    {
        Serial.println("No Networks Found :(");
    }

    for (int i; i < networkCount; i++)
    {
        AvailableWiFi network = {WiFi.SSID(i),
                                 WiFi.RSSI(i)};
        availables.push_back(network);
    }

    // Sort by signal strength (RSSI), strongest first
    std::sort(availables.begin(), availables.end(), [](const AvailableWiFi &a, const AvailableWiFi &b)
              { return a.rssi > b.rssi; });
}

// Detect Wifi status
bool WiFiManager::isConnected()
{
    return WiFi.status() == WL_CONNECTED;
}

// Reconnect to WiFi
void WiFiManager::reconnect()
{
    if (!isConnected())
    {
        connectToStoredWiFi();
    }
}

// Disconnect to WiFi
void WiFiManager::disconnect()
{
    WiFi.disconnect();
}
