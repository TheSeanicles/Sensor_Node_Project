void Bluetooth_Setup(){
  Serial.begin(9600);
  bluetooth_pins.begin(9600);
  Serial.println("HC-05 pairing key is 1234");
  bluetooth_pins.println("");
  bluetooth_pins.println("****\nInitialized\n****");
}
void Bluetooth_Send(float output, bool state, int id){
  bluetooth_pins.print(output);
  if (state){
    bluetooth_pins.print(" | CHARGING | ");
  }
  else if(!state){
    bluetooth_pins.print(" | SLEEP | ");
  }
  else{
    bluetooth_pins.print(" | NULL | ");
  }
  bluetooth_pins.println(id);
}
void Bluetooth_Receive(){
  
}
