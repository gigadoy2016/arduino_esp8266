// referance http://www.akexorcist.com/2016/11/firebase-and-esp8266-with-arduino.html
//date: 01/02/2020

#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

#define WIFI_SSID       "Gigadoy2020"
#define WIFI_PASSWORD   "O8o9237579"
#define FIREBASE_HOST "fir-f2fac.firebaseio.com"
//#define FIREBASE_KEY "UMjwdmVFYhrxHfBa5cFqwFCd02OGQ5Omcl28QV3S"
#define FIREBASE_KEY "yMv5WZSXhp0AzLAqNcZiQTOmdPPzjSW0mOyuyHfe"
int count = 0;

void setup() {
  Serial.begin(9600);
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

  // Do something
  Firebase.begin(FIREBASE_HOST, FIREBASE_KEY);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  Firebase.setInt("count", count++);
  Serial.println("Take counter "+ String(count));
  delay(1000);
}
