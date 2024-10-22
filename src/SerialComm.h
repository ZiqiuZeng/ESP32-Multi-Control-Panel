#ifndef SERIAL_COMM_H
#define SERIAL_COMM_H

class SerialComm
{
public:
    SerialComm();
    void init(long baudRate); // Initialize serial communication
    void hanldeSerialInput(); // Handle incoming serial input

private:
     
};

#endif
