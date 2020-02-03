// 2020/01/26

#include <Wire.h>
int led = 13;       // เอาไว้แสดงจังหวะการส่งข้อมูลไปที่ Esp8266


void setup(){
    pinMode(LED_BUILTIN, OUTPUT);
    Wire.begin();                // NodeMCU เริ่มสื่อสารแบบ I2C
   // Wire.onReceive(receiveEvent); // register event
    Serial.begin(9600);           // start serial for output
    //pinMode(LED2, OUTPUT);
    //digitalWrite(LED2, LOW);
}

void loop(){
    digitalWrite(LED_BUILTIN, HIGH);
    delay(1000);
    
    Wire.requestFrom(10, 6);    // request 6 bytes from slave device #8
    // slave may send less than requested
    while (Wire.available()){
      char c = Wire.read(); // receive a byte as character
      Serial.print(c);         // print the character
    }
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
}
void receiveEvent( int bytes ){
    Serial.println("----------------------------------------------"); 
    int x = Wire.read();                // อ่านค่า ที่ส่งมาจาก Arduino
    Serial.println(x); 
}
