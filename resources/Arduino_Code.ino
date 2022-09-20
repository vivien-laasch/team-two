#include "DHT.h"

#define pin01 A0
#define pin02 A1
#define pinSensor A2
#define DHTTYPE DHT11 

DHT dht(pinSensor, DHTTYPE);
int state = 0;

void setup() {
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  delay(5000);
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t) ) {
    return;
  }
  float hic = dht.computeHeatIndex(t, h, false);


  if(hic > 25 && state == 0){
    Serial.println("state is 0");
    for(int i = 0; i<255; i++){
      analogWrite(pin01, i);
      analogWrite(pin02, 0);
      delay(5);
    }    
    state = 1;
    
  }else if(hic < 25 && state == 1){
     Serial.println("state is 1");
     for(int i = 0; i<255; i++){
      analogWrite(pin01, 0);
      analogWrite(pin02, i);
      delay(5);
     }
     state = 0;
     
  }else{
    analogWrite(pin01, 0);
    analogWrite(pin02, 0);
  }

Serial.println(hic);

  String data = "{\"Humidity\": ";
  data.concat(h);
  data.concat(", \"Temperature\": ");
  data.concat(t);
  data.concat("}");

  Serial.println(data);
}
