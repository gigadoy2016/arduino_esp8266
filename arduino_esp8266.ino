// Sensor Temperature DHT11 by Arduino No.1 
#include <Wire.h>
#include "DHT.h"
#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
int arudinoID = 1;   //  กำหนด id ของอุปกรณ์
int led = 13;       // เอาไว้แสดงจังหวะการส่งข้อมูลไปที่ Esp8266
int x = 0;
int address_esp8266 = 9;

void setup() {
  Serial.println("DHTxx test!");
  dht.begin();
  Wire.begin();               // กำหนด Address เป็น 10
  Serial.begin(9600);
  pinMode(led, OUTPUT);
}

void loop() {
   float h = dht.readHumidity();
   float t = dht.readTemperature();
   float f = dht.readTemperature(true);
   if (isnan(h) || isnan(t) || isnan(f)) {
     Serial.println("Failed to read from DHT sensor!");
      return;
   }
   digitalWrite(led, HIGH);
   float hi = dht.computeHeatIndex(f, h);
   Serial.print("Humidity: "); 
   Serial.print(h);
   Serial.print(" %\t");
   Serial.print("Temperature: "); 
   Serial.print(t);
   Serial.print(" *C ");
   Serial.print(f);
   Serial.print(" *F\t");
   Serial.print("Heat index: ");
   Serial.print(hi);
   Serial.println(" *F");
   
   String json = "{\"sensor\":{\"id\":"+String(arudinoID)+",\"Hum\":"+String(h)+",\"temp\":"+String(t)+" }}"; 
          
   //Serial.println("---------------------------------------------------------------------------------------");
   //Serial.println(json);          
   //Serial.println("---------------------------------------------------------------------------------------");
   delay(100);
   json = "{'sensor':{'id':1,'Hum':30,'temp':50}}";
   //sendData(address_esp8266, json);
   sendData2(10);
   digitalWrite(led, LOW);
   delay(5000);
}
void sendData(int address , String data) {
  Wire.beginTransmission( address );      //เริ่มสื่อสารที่ address นี้
  Wire.write("{'data':{'id':1}}");                       // ส่งข้อมูลให้ตัวรับ
  Wire.endTransmission();                 // จบการสื่อสาร
  Serial.println("Sent data completed!!");          
}
void sendData2(int address) {
  Wire.beginTransmission( address );      //เริ่มสื่อสารที่ address นี้
  Serial.println("Sent address "+String(address) + " 1"); 
  Wire.write(1);                       // ส่งข้อมูลให้ตัวรับ
  Wire.endTransmission();                 // จบการสื่อสาร
  Serial.println("Sent data completed!!");          
}
