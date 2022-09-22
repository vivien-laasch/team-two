#include "DHT.h"
#include <LiquidCrystal.h>

#define pinMotor1 A2
#define pinMotor2 A3
#define pinTemp A1
#define pinCo2 A0
#define DHTTYPE DHT11 

DHT dht(pinTemp, DHTTYPE);
int state = 0;
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  Serial.begin(9600);
  dht.begin();
  lcd.begin(16, 2);
}

void loop() {
  delay(5000);
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  int co2 = analogRead(pinCo2);

  if (isnan(h) || isnan(t) || isnan(co2) ) {
    return;
  }
  
  float hic = dht.computeHeatIndex(t, h, false);


  if(hic > 25 && state == 0){
    Serial.println("state is 0");
    for(int i = 0; i<255; i++){
      analogWrite(pinMotor1, i);
      analogWrite(pinMotor2, 0);
      delay(5);
    }    
    state = 1;
    
  }else if(hic < 25 && state == 1){
     Serial.println("state is 1");
     for(int i = 0; i<255; i++){
      analogWrite(pinMotor1, 0);
      analogWrite(pinMotor2, i);
      delay(5);
     }
     state = 0;
     
  }else{
    analogWrite(pinMotor1, 0);
    analogWrite(pinMotor2, 0);
  }


  String data = "{\"Humidity\": ";
  data.concat(h);
  data.concat(", \"Temperature\": ");
  data.concat(t);
  data.concat(", \"HeatIndex\": ");
  data.concat(hic);
  data.concat(", \"Co2\": ");
  data.concat(co2);
  data.concat("}");

  Serial.println(data);
}