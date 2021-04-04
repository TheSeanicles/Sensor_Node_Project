#include "influxdb.hpp"
#include "SerialPort.hpp"
#include "Parse.h"
#include <fstream>
#include <string>
#include <windows.h>
#include <iostream>
using namespace std;

// Visit https://github.com/orca-zhang/influxdb-c for more test cases

#define TIME_INTERVAL 30000 //Milliseconds

#define DATA_LENGTH 255

const char* portName = "\\\\.\\COM9";

SerialPort* arduino;

char receivedString[DATA_LENGTH];


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
        arduino = new SerialPort(portName);
        std::cout << "Is connected: " << arduino->isConnected() << std::endl;


        if (arduino->isConnected()) {

            cout << "Enter the Influx DB Username: ";
            string username;
            cin >> username;

            cout << "Password: ";
            string password;
            cin >> password;

            Sensor data;

            string resp;

            // query from table
            influxdb_cpp::server_info si_new("192.168.10.104", 8086, "", username, password);
        
            // create_db
            influxdb_cpp::create_db(resp, "Temperature", si_new);
            
            int hasRead = arduino->readSerialPort(receivedString, DATA_LENGTH);
            if (hasRead) std::cout << receivedString << "\n";
            else std::cerr << "Error occured reading data" << "\n";

            while (1) {
                data = parseLine(receivedString);
                // send_udp
                int ret = influxdb_cpp::builder()
                    .meas(data.node_id)
                    .field("Operating State", data.op_state)
                    .field("Temperature", data.temp_value)
                    .field("Battery_Charge", data.battery_voltage)
                    .send_udp("192.168.10.104", 8091);
                Sleep(TIME_INTERVAL);
            }
        }
        else {
            cout << "Arduino not connected." << endl;
        }
        return 0;
    }
}
