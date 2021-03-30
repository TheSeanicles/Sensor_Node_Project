void Bluetooth_Setup() {
  Serial.begin(9600);
  bluetooth_pins.begin(9600);
  Serial.println("HC-05 pairing key is 1234");
  bluetooth_pins.println("");
  bluetooth_pins.println("****\nInitialized\n****");
}
void Bluetooth_Send() {
  bluetooth_pins.print(arduino.temp);
  if (arduino.op_state) {
    if (arduino.temp_type == Celsius) {
      bluetooth_pins.print("C | CHARGING | ");
    }
    else if (arduino.temp_type == Fahrenheit) {
      bluetooth_pins.print("F | CHARGING | ");
    }
  }
  else {
    if (arduino.temp_type == Celsius) {
      bluetooth_pins.print("C | SLEEP | ");
    }
    else if (arduino.temp_type == Fahrenheit) {
      bluetooth_pins.print("F | SLEEP | ");
    }
  }
  bluetooth_pins.print("Battery Voltage: ");
  float vbattery = Battery_monitor() / 0.1708;
  bluetooth_pins.print(vbattery);
  bluetooth_pins.print("V | ");
  bluetooth_pins.print("Node ID: ");
  bluetooth_pins.println(arduino.node_id);
}
void Bluetooth_Receive() {
  if (bluetooth_pins.available() > 0) {
    arduino.bluetooth_read = bluetooth_pins.read();
    Serial.println(arduino.bluetooth_read);
    if (arduino.bluetooth_read == 'C') {
      arduino.temp_type = Celsius;
    }
    if (arduino.bluetooth_read == 'F') {
      arduino.temp_type = Fahrenheit;
    }
  }
  delay(5000);
}
