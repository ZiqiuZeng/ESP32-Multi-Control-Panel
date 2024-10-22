#ifndef SYSTEM_SETTINGS_H
#define SYSTEM_SETTINGS_H

#include <Preferences.h>

class SystemSettings
{
public:
    SystemSettings();
    void init();

private:

    // Command Initialization
    bool isCommandInitialized();
    void setCommandInitialized(bool status);

    // WiFi Settings
    bool isWiFiInitialized();
    void setWiFiInitialized(bool status);

    String getWiFiSSID();
    String getWiFiPassword();

    void addWiFiCred(const String& ssid, const String& password);  
    void removeWiFiCred();


    Preferences preferences; // Object for handling non-volatile storage
};

#endif