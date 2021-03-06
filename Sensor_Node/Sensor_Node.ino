//Load functions
#include <SoftwareSerial.h>

//Initialize Variables
enum Temperature { Celsius, Fahrenheit, Null };

struct _pins{
  int temp;
  int solar;
  int Vout;
  int Vbat;
  int PWM;
};
typedef struct _pins pins;

struct _PWM{
  int pulseSig; // .5 duty cycle in the arduino PWM range 0-255 (113)
  int pwmMax;
  int pwmMin;
  float vRef; // calculated with voltage divider of 10V output
  float vBat; // this will measure the battery output for constant voltage supply
  float vOUT;
  int VoutValue; // store the 10bit number that arduino reads for Vout
  int vBatValue;
  float vDif;
  float vHold;
  float v;
  int i;
  int counter;
  float fPWM;
};
typedef struct _PWM PWM;

struct _Arduino{
  pins pins;
  PWM PWM;
  float temp;
  Temperature temp_type;
  int charging_counter;
  unsigned int charging_time;
  String bluetooth_read;
  int node_id;  //Assigned by MASTER NODE not yet developed
  bool op_state; //CHARGING 1 or SLEEP 0
  char device_type[10]; //So far just NODE might add later
};
typedef struct _Arduino Arduino;


Arduino ArduinoConstruct(){
  Arduino arduino;
  //Pin configuration
  arduino.pins.temp = A0;
  arduino.pins.solar = A1;
  arduino.pins.Vout = A2;
  arduino.pins.Vbat = A3;
  arduino.pins.PWM = 3;
  //PWM configuration
  arduino.PWM.pulseSig = 127; //  duty cycle in the arduino PWM range 0-255
  arduino.PWM.pwmMax = 225;
  arduino.PWM.pwmMin = 25;
  arduino.PWM.vRef = 1.708f; // calculated with voltage divider of 10V output
  arduino.PWM.vOUT;
  arduino.PWM.vDif = 0.0952f;
  arduino.PWM.v = 0.0;
  arduino.PWM.i = 0;
  arduino.PWM.counter = 50;
  arduino.PWM.fPWM = 113.0f;
  //Assorted Variables
  arduino.charging_time = 30000; // 30sec
  arduino.charging_counter = 0;
  arduino.node_id = 1;
  arduino.temp_type = Celsius;
  return arduino;
}

Arduino arduino = ArduinoConstruct();

SoftwareSerial bluetooth_pins(4, 5); // RX | TX

enum class states {START, CHARGING, TEMP, SLEEP, BLUETOOTH, HALT};
states state = states::START;

void setup() {
  Bluetooth_Setup();
  PWM_Start();
}

void loop() {
  NODE();
}
