//optical sensor
#include "variant.h"
#include <due_can.h>

#define TEST1_CAN0_TX_PRIO       15

int analogPin = A3; 
int val = 0;  // variable to store the value read
int v_max = 1002;
int v_min = 64;

float percision = 1000.0;
void setup() {
  
  Serial.begin(9600);  //  setup serial
  
}

void loop() {
  val = analogRead(analogPin);
  float dis_map = map(val, v_min, v_max, 2400, 7600);
  float distance = dis_map / percision;
  Serial.println(distance); 

  Can0.begin(CAN_BPS_250K);
  Can1.begin(CAN_BPS_250K);
  
  CAN_FRAME output; 
  output.id = 0x20;
  output.length = 4;
  output.data.low = dis_map;
  CAN.sendFrame(output);
  delay(20);
  
  Can0.disable();
  Can1.disable();

  Serial.print("\nEnd of test");
}
