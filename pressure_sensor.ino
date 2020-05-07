#include<SPI.h>
float p_max = 15.0;
float p_min = 0.0;
int out_min = 1638; // 10%
int out_max = 14745; // 90%

void setup() {
  // put your setup code here, to run once:
  pinMode(7, OUTPUT);
  Serial.begin(9600);
  delay(25);
  SPI.setClockDivider(SPI_CLOCK_DIV8);
  SPI.begin();
  digitalWrite(SS,HIGH);
}

void loop() {
  byte buf[2];
  // put your main code here, to run repeatedly:
  byte Mastersend,Mastereceive;

  digitalWrite(SS, LOW);
  buf[0] = SPI.transfer(Mastersend); 
  buf[1] = SPI.transfer(Mastersend);
  byte b3 = SPI.transfer(Mastersend);
//  byte b4 = SPI.transfer(Mastersend);
  
  uint16_t total_byte = (buf[0] << 8) | buf[1]; 
  uint16_t temp = b3 << 3;
  int total = total_byte;
//  Serial.println((b1<<8)|b2,BIN);
//  Serial.println(total_byte, BIN);
//  Serial.println(total);
  double pre = (total-out_min)*(p_max-p_min)/(out_max-out_min)+p_min;
//  Serial.println(pre);
  double psi_to_pa = 6894.75729;
  Serial.println(pre*psi_to_pa+101325);
//  Serial.println(buf[0], BIN);
//  Serial.println(buf[1], BIN);
//  Serial.write(buf, sizeof(buf));
  //Serial.println();
  analogWrite();
  float degr = temp*200.0/2047.0-50;
//  Serial.println(degr);
  digitalWrite(SS, HIGH);
  
  delay(30);
}
