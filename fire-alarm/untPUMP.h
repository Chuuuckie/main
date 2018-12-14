class unit_Pump{
  public:
    void Init_Pump(int Pump_Pin);
    void goPump();
    void offPump();
  private:
    int Pump_Pin = 0;
};

void unit_Pump::Init_Pump(int aPump_Pin){
  Pump_Pin = aPump_Pin;
  pinMode(Pump_Pin, OUTPUT);
}

void unit_Pump::goPump(){
  digitalWrite(Pump_Pin, LOW);
  //Serial.println("Sprinkler Activated");
}

void unit_Pump::offPump(){
  digitalWrite(Pump_Pin, HIGH);
}
