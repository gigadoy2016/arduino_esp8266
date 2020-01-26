// 2020/01/26

#include <Wire.h>
//int address_uno1 = 9;
//int address_uno2 = 10;
void setup()
{
  Wire.begin(9); // NodeMCU เริ่มสื่อสารแบบ I2C
}
void loop()
{
  //sendCommand(address_uno1, 1);
  sendCommand(address_uno2, 0);
  delay(5000);

  //sendCommand(address_uno1, 0);
  sendCommand(address_uno2, 1);
  delay(1000);
}

void sendCommand(int address , int command) {
  Wire.beginTransmission( address ); //เริ่มสื่อสารที่ address นี้
  Wire.write(command); // ส่งข้อมูลให้ตัวรับ
  Wire.endTransmission(); // จบการสื่อสาร
}
