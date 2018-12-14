class unit_Buzzer{
  public:
    void Init_Buzzer(int Buzz_Pin);
    void goBuzz(int ALevel);
    void offBuzz();
  private:
    int UPTIME = 0;
    int Buzz_Pin = 0;
};

void unit_Buzzer::Init_Buzzer(int aBuzz_Pin){
  Buzz_Pin = aBuzz_Pin;
  pinMode(Buzz_Pin, OUTPUT);
}

void unit_Buzzer::goBuzz(int ALevel){  
  if(ALevel == 1)
  {
    analogWrite(Buzz_Pin, 255);    
    delay(100);
    analogWrite(Buzz_Pin, 10);    
    delay(50);
    analogWrite(Buzz_Pin, 5);
    delay(10);    
  }else
  if(ALevel == 2)
  {
    analogWrite(Buzz_Pin, 255);    
    delay(50);
    analogWrite(Buzz_Pin, 199);    
    delay(25);
    analogWrite(Buzz_Pin, 0);
    delay(5);    
  }else
  if(ALevel == 3)
  {
    analogWrite(Buzz_Pin, 255);    
    delay(25);
    analogWrite(Buzz_Pin, 150);    
    delay(7);
    analogWrite(Buzz_Pin, 0);
    delay(1);    
  }
  //Serial.println("Alarm Activated");
}

void unit_Buzzer::offBuzz(){
  analogWrite(Buzz_Pin, 0);
}
