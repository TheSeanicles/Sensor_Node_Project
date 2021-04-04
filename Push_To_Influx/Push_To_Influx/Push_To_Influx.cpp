#include "influxdb.hpp"
#include "Parse.h"
#include <fstream>
#include <string>
#include<windows.h>
#include <iostream>
using namespace std;

// Visit https://github.com/orca-zhang/influxdb-c for more test cases

#define Sleep_Time 10000 //Milliseconds


int main(int argc, char const* argv[])
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
        cout << "Enter the data file name without the .txt suffix: ";

        string file_name;
        cin >> file_name;
        file_name += ".txt";

        ifstream data_file(file_name);

        if (data_file.is_open()) {

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

            string line;
            while (getline(data_file, line)) {
                line += ' ';
                data = parseLine(line);
                // send_udp
                int ret = influxdb_cpp::builder()
                    .meas(data.node_id)
                    .field("Operating State", data.op_state)
                    .field("Temperature", data.temp_value)
                    .field("Battery_Charge", data.battery_voltage)
                    .send_udp("192.168.10.104", 8091);
                Sleep(Sleep_Time);
            }
        }
        else {
            cout << "File " << file_name << " not found" << endl;
        }
        return 0;
    }
}
