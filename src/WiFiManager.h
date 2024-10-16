#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

class WiFiManager {
public:
    WiFiManager();  // Constructor with default credentials loaded from non-volatile storage
    void init();  // Initialize WiFi
    void scanNetworks();  // Scan for available networks
    void connectToNetwork(int selectedNetwork);  // Connect to selected WiFi network
    bool isConnected();  // Check if the device is connected to WiFi
    void reconnect();  // Reconnect to WiFi if the connection is lost
    void disconnect();  // Disconnect from WiFi
    void connectToDefault();  // Connect to the default WiFi network
    void loadDefaultCredentials();  // Load stored default credentials
    void saveDefaultCredentials(const char* ssid, const char* password);  // Save credentials to non-volatile storage
    
private:
    const char* defaultSSID;      // Default WiFi SSID
    const char* defaultPassword;  // Default WiFi password
    int selectedNetwork;          // Store the selected network
};

#endif

