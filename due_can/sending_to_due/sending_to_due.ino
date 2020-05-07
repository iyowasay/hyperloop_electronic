#include "variant.h"
#include <due_can.h>

#define TEST1_CAN_COMM_MB_IDX    0
#define TEST1_CAN_TRANSFER_ID    0x32
#define TEST1_CAN0_TX_PRIO       15
#define CAN_MSG_DUMMY_DATA       0x55AAEE22

// CAN frame max data length
#define MAX_CAN_FRAME_DATA_LEN   8

//Leave defined if you use native port, comment if using programming port
// #define Serial SerialUSB
float CAN_MSG_1 = 0;
float percision = 10000;
float nn = 0;

void setup()
{
  CAN_FRAME output;
  // start serial port at 9600 bps:
  Serial.begin(9600);
  //while (Serial.available() == 0);
}
void loop(){
  // Initialize CAN0 and CAN1, baudrate is 500kb/s
  Can0.begin(CAN_BPS_250K);
  Can1.begin(CAN_BPS_250K);
  
  //only allow this one frame ID through. 
  Can1.watchFor(TEST1_CAN_TRANSFER_ID);
  
  //delay(30);  // Wait for second canbus port to receive the frame
  
  float k = 5.34;
  
  while(1){
//    while (Serial.available() > 0){
//      nn = Serial.parseFloat();
//      nn = nn*percision;
//      Serial.println(nn);
//      delay(50);
//    }
//    k = k+0.001;
 //   CAN_FRAME output, incoming; 
//    output.id = 0x20;
//    output.length = 4;
//   // output.data.low = nn;
//    output.data.low = k*percision;
//    CAN.sendFrame(output);

    while (Can1.available() == 0) {
      Serial.println("Nooo");
    }
    CAN_FRAME incoming;
    Can1.read(incoming);
    float ans = incoming.data.low;
    //Serial.println(incoming.data.low, DEC);
    Serial.println(ans/percision, 4);
    //Serial.print(incoming.data.high, HEX); high = 0
    delay(20);
    }
  
  // Read the received data from CAN1 mailbox 0
  Can0.disable();
  Can1.disable();

  Serial.print("\nEnd of test");
  while (1) {
  }
}
