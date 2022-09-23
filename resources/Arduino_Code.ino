#include "DHT.h"
#include <LiquidCrystal.h>

#define pinCo2 A0
#define pinTemp A1
#define pinMotor1 A2
#define pinMotor2 A3
#define DHTTYPE DHT11
#define targetTempMin 19.0
#define targetHumMax 50.0
#define maxCo2Ppm 1000
#define openWindowTimer 420 //8 minutes
#define closedWindowTimer 2400 //40 minutes

DHT dht(pinTemp, DHTTYPE);
bool isOpen = false;
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int timer = 0;

void setup() {
  Serial.begin(9600);
  dht.begin();
  lcd.begin(16, 2);
}

void loop() {
  delay(5000);
  
  if (timer <= closedWindowTimer){
    timer += 5; //add in seconds to avoid overflow
  }

  float h = dht.readHumidity();
  float t = dht.readTemperature();
  int co2 = analogRead(pinCo2) + 700; //fake value because sensor data is inaccurate

  if (isnan(h) || isnan(t) || isnan(co2) ) {
    return;
  }
  
  float hic = dht.computeHeatIndex(t, h, false);
  printData(t, h, hic, co2);

  if(!isOpen && timer >= closedWindowTimer && doOpenWindow(h,co2)){
    controlMotor(true);
    isOpen = true;
    timer = 0;
  }

  if(isOpen && timer >= openWindowTimer && doCloseWindow(t,h,co2)){
    controlMotor(false);
    isOpen = false;
    timer = 0;
  }
}

void controlMotor(bool doOpen){
  if(doOpen){
    analogWrite(pinMotor1, 150);     
  }else if(!doOpen){
    analogWrite(pinMotor2, 150);
  }
  delay(5000);
  analogWrite(pinMotor1, 0);
  analogWrite(pinMotor2, 0);
}

bool doOpenWindow(float h, int co2){
  return h > targetHumMax || co2 > maxCo2Ppm;
}

bool doCloseWindow(float t, float h, int co2){
  return t < targetTempMin || co2 <= maxCo2Ppm && h <= targetHumMax;
}

void printData(float t, float h, float hic, int co2){
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