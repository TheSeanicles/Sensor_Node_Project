//Load functions
#include <SoftwareSerial.h>

//Initialize Variables
SoftwareSerial bluetooth_pins(4, 5); // RX | TX

int temp_Pin = A0;
int solar_Pin = A1;
int Vout_Pin = A2;
int Vbat_Pin = A3;
int PWM_Pin = 3;
float vBat;
float temp;
unsigned int charging_time = 30000;

int node_id = 0; //Assigned by MASTER NODE not yet developed
bool op_state ; //CHARGING 1 or SLEEP 0
char device_type[10] = {"NODE"}; //So far just NODE or MASTER

void setup() {
  Bluetooth_Setup();
  PWM_Start();
}

void loop() {
  if (device_type[10] = "NODE"){
    NODE();
  }
}
