//Load functions
#include <SoftwareSerial.h>

//Initialize Variables
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
};
typedef struct _PWM PWM;

struct _Arduino{
  pins pins;
  PWM PWM;
  float temp;
  unsigned int charging_time; 
  int node_id;  //Assigned by MASTER NODE not yet developed
  bool op_state; //CHARGING 1 or SLEEP 0
  char device_type[10]; //So far just NODE might add later
};
typedef struct _Arduino Arduino;


SoftwareSerial bluetooth_pins(4, 5); // RX | TX

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
  arduino.PWM.vRef = 1.16; // calculated with voltage divider of 10V output 
  arduino.PWM.vOUT;
  arduino.PWM.vDif = 0.1708;
  arduino.PWM.v = 0.0;
  arduino.PWM.i = 0;
  arduino.PWM.counter = 50;
  //Assorted Variables
  arduino.charging_time = 30000;
  arduino.node_id=0;
  return arduino;
}

Arduino arduino = ArduinoConstruct();

void setup() {
  Bluetooth_Setup();
  PWM_Start();
}

void loop() {
  NODE();
}
