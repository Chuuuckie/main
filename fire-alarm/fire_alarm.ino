
#include "untGSM.h"
#include "untPump.h"
#include "untBuzzer.h"

unit_GSM GSM_Module;
unit_Pump PUMP;
unit_Buzzer BUZZER;

//int LED_Pin = 7;
const int ALARM_LEVEL1 = 5;
const int ALARM_LEVEL2 = 15;
const int ALARM_LEVEL3 = 25;

long UPTIME = 0;
long set_time = 60; // set total time
long trigger_time = 0;

bool fire_detected = false;

char c;

void setup() {
  delay(3000);
  Serial.println("Fire Detection Started...");
  Serial.begin(9600);
  GSM_Module.Init_GSM("+639151258272"); // Initialize contact number
  PUMP.Init_Pump(6); // Initialize pump pin
  BUZZER.Init_Buzzer(A1); // Initialize buzzer pin
  //pinMode(LED_Pin, OUTPUT);
}

void loop() {
if(Serial.available() > 0){
    c = Serial.read();
    if(c == 'F' || c == 'f'){
      fire_detected = true;
    }
    else if(c == 'O' || c == 'o'){
      fire_detected = false;
    }    
  }

  //timer
  if(fire_detected){
    if(UPTIME != round(millis() / 1000)){
      UPTIME = round(millis() / 1000);
      trigger_time++;      
    }
    //Serial.println(trigger_time);
    if((trigger_time >= ALARM_LEVEL1) && (trigger_time <= ALARM_LEVEL2))
    {
        BUZZER.goBuzz(1);
    }
    else if((trigger_time >= ALARM_LEVEL2) && (trigger_time <= ALARM_LEVEL3))
    {
        BUZZER.goBuzz(2);
        PUMP.goPump();
    }
    else if(trigger_time >= ALARM_LEVEL3){
        BUZZER.goBuzz(3);
        PUMP.goPump();
        GSM_Module.goSendTxt();
      }
  }
  else{
    trigger_time = 0;
    BUZZER.offBuzz();
    PUMP.offPump();
  }
}
