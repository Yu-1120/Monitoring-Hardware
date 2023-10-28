#include <Arduino.h>
#include <DHT.h>
#include <DHT_U.h>
#define DHTPIN 12   
#define DHTTYPE DHT11  
DHT dht(DHTPIN, DHTTYPE);  
void setup() {
  Serial.begin(115200);
  dht.begin(); 
}

void loop()
{ 
  float h = dht.readHumidity();   
  float t = dht.readTemperature(); 
  Serial.print("相对湿度: ");   
  Serial.print(h);
  Serial.println(" %RH");
  Serial.print("温度: ");
  Serial.print(t);
  Serial.println(" °C");
  delay(1000);
}
