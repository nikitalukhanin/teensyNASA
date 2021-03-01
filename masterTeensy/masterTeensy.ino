#include <Wire.h>

#define NODE 2
#define PAYLOAD_SIZE 4

char buffer[4];
char nodeReceive[PAYLOAD_SIZE];
 
void setup() {
  Serial.begin(9600);
  Wire.begin();
  Serial.println("For talon type 't'\nFor stepper type 's'\nIf talon type a value from 200 to 380\nIf stepper type a number between 100 to 300\n*************************"); // so I can keep track of what is loaded
}

void loop() {
  int index; 
  
  Wire.requestFrom(NODE, PAYLOAD_SIZE);    // request data from node#
   if (Wire.available() == PAYLOAD_SIZE) { // if data size is avaliable from nodes
     for (int i = 0; i < PAYLOAD_SIZE; i++) nodeReceive[i] = Wire.read();  // get nodes data
     nodeReceive[4] = '\0';
     Serial.print(nodeReceive);   // print nodes data
     Serial.println(" Executed");
  }

  while (Serial.available()) {
    index = Serial.readBytesUntil('\n', buffer, 5);  //newline or max of 5 chars
    buffer[index] = '\0';
    
    Serial.println(buffer);  //so you can see the captured String

    Wire.beginTransmission(NODE); //address is queued for checking if the slave is present
    for (int i=0; i<4; i++)
      {
        Wire.write(buffer[i]);  //data bytes are queued in local buffer
        //Serial.println(buffer[i]);  //so you can see the captured String
      }
    Wire.endTransmission(); //all the above queued bytes are sent to slave on ACK handshaking
  }
}
