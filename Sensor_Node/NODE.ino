void NODE() {
  switch (state) {
    case states::START:
      if ((Solar_Panel_Active()) && (Battery_monitor() <= 1.74) && (arduino.temp_type != Null)) {
        state = states::CHARGING;
      }
      else if (arduino.temp_type != Null) {
        state = states::SLEEP;
      }
      else {
        bluetooth_pins.println("Enter C or F to set desired Temperature Unit: ");
        while (arduino.temp_type == Null) {
          Bluetooth_Receive();
        }
        state = states::START;
      }
      break;
    case states::CHARGING:
      arduino.op_state = 1;
      int i;
      for (i = 0; i <= (arduino.charging_time / 10); i++) {
        PWM_Generator();
        delay(10);
      }
      arduino.charging_counter++;
      if (arduino.charging_counter == 10){
        state = states::TEMP;
      }
      else{
        state = states::START;
      }
      break;
    case states::SLEEP:
      arduino.op_state = 0;
      Sleep(); //If you are using a bluetooth terminal any input wakes from sleep
      state = states::TEMP;
      break;
    case states::TEMP:
      arduino.temp = Read_Temp();
      state = states::BLUETOOTH;
      break;
    case states::BLUETOOTH:
      Bluetooth_Receive();
      arduino.charging_counter = 0;
      break;
    case states::HALT:
      break;
  }
}
