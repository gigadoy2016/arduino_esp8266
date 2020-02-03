#include <Wire.h>
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include "DHT.h"

#define DHTPIN 4
#define DHTTYPE DHT22
#define WIFI_SSID       "Gigadoy2020"
#define WIFI_PASSWORD   "O8o9237579"
#define FIREBASE_HOST "fir-f2fac.firebaseio.com"
//#define FIREBASE_KEY "UMjwdmVFYhrxHfBa5cFqwFCd02OGQ5Omcl28QV3S"
#define FIREBASE_KEY "yMv5WZSXhp0AzLAqNcZiQTOmdPPzjSW0mOyuyHfe"


int count = 0;
DHT dht(DHTPIN, DHTTYPE);     //Setup DHT22
String JSON = "";
void setup() {
  Serial.begin(9600); /* begin serial for debug */
  Wire.begin(D1, D2); /* join i2c bus with SDA=D1 and SCL=D2 of NodeMCU */
/*
  Serial.println(WiFi.localIP());
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  Firebase.begin(FIREBASE_HOST, FIREBASE_KEY);*/
}
void loop() {
    Wire.beginTransmission(8); /* begin with device address 8 */
    Wire.endTransmission();    /* stop transmitting */
    Wire.requestFrom(8, 13); /* request & read data of size 13 from slave */
    
    String DATA ="";
    while(Wire.available()){
       char c = Wire.read();
       DATA += c;
    }
    Serial.println("");
    splitData(DATA);
    delay(5000);

    Wire.beginTransmission(9); /* begin with device address 8 */
    Wire.endTransmission();    /* stop transmitting */
    Wire.requestFrom(9, 13); /* request & read data of size 13 from slave */
    
    String DATA2 ="";
    while(Wire.available()){
       char c = Wire.read();
       DATA2 += c;
    }
    Serial.println("");
    splitData(DATA2);
    delay(5000);

    String DATA3 ="";
    float h = dht.readHumidity();
    float t = dht.readTemperature();
    float f = dht.readTemperature(true);
    if (isnan(h) || isnan(t) || isnan(f)) {
      Serial.println("Failed to read from DHT sensor!");
      return;
    }
    float hi  = dht.computeHeatIndex(f, h);
    DATA3 = "3,"+String(h)+","+String(t);
    Serial.println("");
    splitData(DATA3);
    delay(5000);
}

void splitData(String DATA){
  String ID = "";
  String temp = "";
  String humi = "";
  ID = DATA.substring(0,1);
  humi = DATA.substring(2,7);
  temp = DATA.substring(8);
  //Serial.print("ID:"+ID);
  //Serial.print("    humi:"+humi);
  //Serial.println("    temp:"+temp);

  Firebase.setString("now/node_1/humi/",humi);
  Firebase.setString("now/node_1/temp/",temp);
  JSON = "{\"id\":"+ID+",\"Hum\":"+humi+",\"temp\":"+temp+" }"; 
  Serial.println(JSON);
}
