#include "influxdb.hpp"
#include "SerialPort.hpp"
#include "Parse.h"
#include <fstream>
#include <string>
#include <windows.h>
#include <iostream>
using namespace std;

// Visit https://github.com/orca-zhang/influxdb-c for more test cases

#define TIME_INTERVAL 5000 //Milliseconds

#define WAIT_1s 1000 //Milliseconds

#define DATA_LENGTH 255




int main(void)
{
    WSADATA wsaData;
    int iResult;
    
    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed: %d\n", iResult);
        return 1;
    }
    else {
        cout << "Enter the Influx DB Username: ";
        string username;
        cin >> username;

        cout << "Password: ";
        string password;
        cin >> password;

        const char* portName = "\\\\.\\COM4";

        SerialPort* arduino;

        char receivedString[DATA_LENGTH];

        const char* portName_send = "\\\\.\\COM4";

        //Declare a global object
        SerialPort* arduino_send;

        //Here '\n' is a delimiter 
        const char* sendString = "REQUEST\n";

        arduino = new SerialPort(portName);
        std::cout << "Is receive connected: " << arduino->isConnected() << std::endl;

        arduino_send = new SerialPort(portName_send);
        std::cout << "Is send connected: " << arduino->isConnected() << std::endl;

        if (arduino->isConnected()) {
            Sensor data;

            string resp;

            // query from table
            influxdb_cpp::server_info si_new("192.168.10.104", 8086, "", username, password);
        
            // create_db
            influxdb_cpp::create_db(resp, "Temperature", si_new);

            while (1) {
                int hasRead = arduino->readSerialPort(receivedString, DATA_LENGTH);
                if (hasRead) {
                    std::cout << receivedString << "\n";
                    data = parseLine(receivedString);
                    // send_udp
                    int ret = influxdb_cpp::builder()
                        .meas(data.node_id)
                        .field("Operating State", data.op_state)
                        .field("Temperature", data.temp_value)
                        .field("Battery_Charge", data.battery_voltage)
                        .send_udp("192.168.10.104", 8091);
                }
                else {
                    bool hasWritten;
                    if (portName == portName_send) {
                        hasWritten = arduino->writeSerialPort(sendString, DATA_LENGTH);
                    }
                    else {
                        hasWritten = arduino_send->writeSerialPort(sendString, DATA_LENGTH);
                    }
                    if (hasWritten) {
                        std::cout << "Data Requested" << std::endl;
                    }
                    else {
                        std::cerr << "Data was not written!" << std::endl;
                    }
                }
                Sleep(TIME_INTERVAL);
            }
        }
        else {
            cout << "Arduino not connected." << endl;
        }
        return 0;
    }
}
