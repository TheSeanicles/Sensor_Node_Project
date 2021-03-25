void Bluetooth_Setup(){
  Serial.begin(9600);
  bluetooth_pins.begin(9600);
  Serial.println("HC-05 pairing key is 1234");
  bluetooth_pins.println("");
  bluetooth_pins.println("****\nInitialized\n****");
}
void Bluetooth_Send(){
  bluetooth_pins.print(arduino.temp);
  if (arduino.op_state){
    bluetooth_pins.print(" | CHARGING | ");
  }
  else {
    bluetooth_pins.print(" | SLEEP | ");
  }
  bluetooth_pins.print("Battery Voltage: ");
  float vbattery = arduino.PWM.vBat / 0.1708;
  bluetooth_pins.print(vbattery);
  bluetooth_pins.print("V | ");
  bluetooth_pins.print("Node ID: ");
  bluetooth_pins.println(arduino.node_id);
}
void Bluetooth_Receive(){

}
