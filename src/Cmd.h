#ifndef CMD_H
#define CMD_H

// Enum defining the preset commands compatible with serial communication

enum SerialCmd
{
    STATUS, // Check for system status
    REBOOT, // Reboot the system
    RESET,  // Reset the system
};

#endif