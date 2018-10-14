
#include <Servo.h>
#include <Renard.h>


/*
   Yellow: Pin 9
   Red: +5V
   Brown: GND
*/

// Values on the servo that correspond to mouth positions.
const int FULLOPEN = 150;
const int FULLCLOSED = 125;

const int SERVO_MOUTH_PIN = 9;
const int SERVO_HEAD_PIN = 11;
const int EYESPIN = 3;

Servo servoMouth;
Servo servoHead;
Renard renard(Serial, 3);


void setup() {
  // Open serial communications
  Serial.begin(57600);
  pinMode(EYESPIN, OUTPUT);
  servoMouth.attach(SERVO_MOUTH_PIN);
  servoMouth.write(FULLCLOSED);
  servoHead.attach(SERVO_HEAD_PIN);
  servoHead.write(90);
}

void loop() {
  // Read renard
  while (!renard.processInput())
    ;

  //Do Mouth
  int channelValue = renard.channelValue(1);
  int pos = map(channelValue, 0, 255, FULLCLOSED, FULLOPEN);
  servoMouth.write(pos);

  //Do Head
  int channelValueHead = renard.channelValue(3);
  int headPos = 90;
  if(channelValueHead != 0){
    headPos = map(channelValueHead, 0, 255, 0, 180);
  }
  servoHead.write(headPos);

  //Do Eyes
  int eyesValue = renard.channelValue(2);
  analogWrite(EYESPIN, eyesValue);
}

