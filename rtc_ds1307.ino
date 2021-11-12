/*
 * dev: Anderson Roberto de Aguiar
 * cidade: Presidente Prudente - SP
 * date: 12/11/2021
 * 
 * Código fonte: Exemplo de comunicação com o shield RTC-DS1307
 * 
 * Analog in: pin4 SDA, pin5 SCL
*/

#include<Wire.h>

#define RTCAddress 0x68

byte bcd2dec(byte val){
  return((val / 16 * 10) + (val % 16));
}

byte dec2bcd(byte val){
  return ((val / 10 * 16) + (val % 10));
}

void setTime(byte second, byte minute, byte hour, byte day, byte date, byte month, byte year){
  Wire.beginTransmission(RTCAddress);
  Wire.write(0);
  Wire.write(dec2bcd(second));
  Wire.write(dec2bcd(minute));
  Wire.write(dec2bcd(hour));
  Wire.write(dec2bcd(day));
  Wire.write(dec2bcd(date));
  Wire.write(dec2bcd(month));
  Wire.write(dec2bcd(year));
  Wire.endTransmission();
}

void readTime(byte *second, byte *minute, byte *hour, byte *day, byte *date, byte *month, byte *year){
  Wire.beginTransmission(RTCAddress);
  Wire.write(0);
  Wire.endTransmission();
  Wire.requestFrom(RTCAddress, 7);
  *second=bcd2dec(Wire.read() & 0x7F);
  *minute=bcd2dec(Wire.read());
  *hour=bcd2dec(Wire.read() & 0x3F);
  *day=bcd2dec(Wire.read());
  *date=bcd2dec(Wire.read());
  *month=bcd2dec(Wire.read());
  *year=bcd2dec(Wire.read());
}

void displayTime(){
  byte second, minute, hour, day, date, month, year;
  readTime(&second, &minute, &hour, &day, &date, &month, &year);
  Serial.print(day);
  Serial.print(" - ");
  Serial.print(hour);
  Serial.print(":");
  Serial.print(minute);
  Serial.print(":");
  Serial.print(second);
  Serial.print(" ");
  Serial.print(date);
  Serial.print("/");
  Serial.print(month);
  Serial.print("/");
  Serial.print(year);
  Serial.println(" ");
}

void setup() {
  Wire.begin();
  Serial.begin(9600);
  //setTime(0,22,19,5,12,11,21);
}

void loop() {
  displayTime();
  delay(1000);
}
