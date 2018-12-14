#include <SoftwareSerial.h>

SoftwareSerial gsm(10, 11); //Rx, Tx

class unit_GSM{
  public:
    void Init_GSM(String number);
    void goSendTxt();
  private:
    String number = "";
};

void unit_GSM::Init_GSM(String fnumber){
  number = fnumber;
  gsm.begin(9600);
}

void unit_GSM::goSendTxt(){
  Serial.println("SMS Sending Module");
  return;
  gsm.println("AT+CMGF=1");
  delay(50);
  gsm.println("AT+CMGS=\"" + number + "\"\r");
  delay(50);
  String SMS = "WARNING: Fire Detected!";
  gsm.println(SMS);
  delay(50);
  gsm.println((char)26);
  Serial.println("Warning message sent!");
}
