#include "SystemSettings.h"

// Constructor
SystemSettings::SystemSettings() {}

// Initialize Preferences
void SystemSettings::init()
{
    preferences.begin("storage", false); // Open preferences with read-write access
}

// ===================== Command Initialization ======================

bool SystemSettings::isCommandInitialized()
{
    return preferences.getBool("cmd_int", false);
}

void SystemSettings::setCommandInitialized(bool status)
{
    preferences.putBool("cmd_init", status);
}

// ===================== WiFi Settings ======================

bool SystemSettings::isWiFiInitialized()
{
    return preferences.getBool("wifi_int", false);
}

void SystemSettings::setWiFiInitialized(bool status)
{
    preferences.putBool("wifi_init", status);
}