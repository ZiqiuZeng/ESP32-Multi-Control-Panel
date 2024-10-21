#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

#include <vector>
#include <map>

struct AvailableWiFi
{
    String ssid;
    int rssi; // Signal strength
};

/**
 * WiFiManager handles WiFi operations such as connecting, disconnecting, and scanning for networks.
 * It uses FreeRTOS tasks to perform WiFi operations without blocking the main loop.
 */
class WiFiManager
{
public:
    WiFiManager(); // Constructor with default credentials loaded from non-volatile storage

    void init();                                                          // Initialize WiFi
    bool isWiFiAvailable();                                               // Check if WiFi available
    void connectToStoredWiFi();                                           // Connect to stored WiFi credentials
    void connectToSelectedWiFi(const String ssid, const String password); // Connect to selected WiFi network

    void scanForNetworks();     // Scan for available networks
    void promptForWiFiConfig(); // Prompt user to add WiFi credentials

    bool isConnected(); // Check if the device is connected to WiFi
    void reconnect();   // Reconnect to WiFi if the connection is lost
    void disconnect();  // Disconnect from WiFi

    void listStoredCredentials();                                   // List all stored WiFi credentials
    void addWiFiCredential(const char *ssid, const char *password); // Add new WiFi credentials
    void removeWiFiCredential(const char *ssid);

private:
    std::map<String, String> credentials;
    std::vector<AvailableWiFi> availables;

    int currentCredentialIndex; // Track current credential being attempted

    void loadStoredCredentials(); // Load credentials from non-volatile storage
    void saveCredentials();       // Save all credentials to non-volatile storage
};

#endif
