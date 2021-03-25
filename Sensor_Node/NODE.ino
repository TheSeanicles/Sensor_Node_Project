void NODE(){
  enum class states {START, CHARGING, TEMP, SLEEP, BLUETOOTH, HALT};
    states state = states::START;
    while (state != states::HALT){
      switch (state){
      case states::START:
        if ((Solar_Panel_Active()) && (Battery_monitor() <= 1.74)){
          state = states::CHARGING;
        }
        else{
          state = states::SLEEP;
        }
        break;
      case states::CHARGING:
        arduino.op_state = 1;
        // get the current battery voltage
        int i;
        for (i=0; i <= (arduino.charging_time / 250); i++){
          PWM_Generator();
          delay(250);
        }
          state = states::TEMP;
        break;
      case states::SLEEP:
        arduino.op_state = 0;
        Sleep(); //If you are using a bluetooth terminal any input wakes from sleep
        //delay(1000); //If no terminal Un comment the delay() and comment the sleep function
        state = states::TEMP;
        break;
      case states::TEMP:
        arduino.temp = Read_Temp();
        state = states::BLUETOOTH;
        break;
      case states::BLUETOOTH:
        Bluetooth_Send();
        state = states::START;
        break;
      case states::HALT:
        break;
      }
    }
}
