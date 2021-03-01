#include<Wire.h>
#include <Servo.h>
#include <SpeedyStepper.h>

#define SERVOPIN 9
#define MOTOR_STEP_PIN 6
#define MOTOR_DIRECTION_PIN 5
#define PAYLOAD_SIZE 4
#define NODE_ADDRESS 2  // Change this unique address for each I2C slave node

Servo talon;
SpeedyStepper stepper;

int stepperValue;
int talonValue;

char returnData[4];

void setup()
{
  talon.attach(SERVOPIN);
  stepper.connectToPins(MOTOR_STEP_PIN, MOTOR_DIRECTION_PIN);
    
  Wire.begin(NODE_ADDRESS);  // Activate I2C network
  Serial.begin(9600);
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent); // Request attention of master node
}

void loop()
{
  //3 lines take up all the time in the loop, just the nature of sending data unless I find some eeprom exploit
  stepper.setSpeedInStepsPerSecond(100);
  stepper.setAccelerationInStepsPerSecondPerSecond(100);
  stepper.moveRelativeInSteps(stepperValue);
  
  talon.write(talonValue);
}

void receiveEvent(int howmany) //howmany = Wire.write()executed by Master
{
  byte incomingData[4];
  char intData[2];
  for (int i = 0; i < howmany; i++)
  {
    incomingData[i] = Wire.read();
  }
  
  for (int i = 0; i < howmany; i++) {
    returnData[i] = incomingData[i];
  }
  returnData[4] = '\0';
  
  for (int i = 0; i < 3; i++) {
    intData[i] = incomingData[i + 1];
  }
  if(incomingData[0] == 's'){
    stepperValue = atoi(intData)-200; //convert readString into a number
    //Serial.println("stepper"); //so you can see the integer
    //Serial.println(stepperValue); //so you can see the integer
  }
  if(incomingData[0] == 't'){
    talonValue = atoi(intData)-200; //convert readString into a number
    Serial.println("talon"); //so you can see the integer
    Serial.println(talonValue); //so you can see the integer
  }
}

void requestEvent()
{
  Wire.write(returnData, PAYLOAD_SIZE);
  Serial.println(returnData);
}
