// Sensor Temperature DHT11 by Arduino No.1 
#include <Wire.h>
#include "DHT.h"
#define DHTPIN 2
#define DHTTYPE DHT22


DHT dht(DHTPIN, DHTTYPE);     //Setup DHT22
int arudinoID = 1;            //  กำหนด id ของอุปกรณ์
int PIN       = 13;           // แสดง Status การทำงานของบอร์ด
int count     = 0;            // แสดงจำนวนรอบการทำงาน
int address   = 9;            //join i2c bus with address 8
String DATA   = "";

void setup() {
    Wire.begin(address);
    Wire.onRequest(requestEvent); /* register request event */
    Serial.begin(9600);           /* start serial for debug */
}

void loop() {
    float h = dht.readHumidity();
    float t = dht.readTemperature();
    float f = dht.readTemperature(true);
    if (isnan(h) || isnan(t) || isnan(f)) {
      Serial.println("Failed to read from DHT sensor!");
      return;
    }
    float hi  = dht.computeHeatIndex(f, h);
    //json      = "{\"id\":"+String(arudinoID)+",\"Hum\":"+String(h)+",\"temp\":"+String(t)+" }"; 
    DATA = String(arudinoID)+","+String(h)+","+String(t);
    Serial.println(DATA);
    delay(5000);
}

// function that executes whenever data is requested from master
void requestEvent() {
    Wire.write(DATA.c_str());  /*send string on request */
}
