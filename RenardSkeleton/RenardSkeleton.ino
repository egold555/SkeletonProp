
#include <Servo.h>
#include <Renard.h>


/*
   Yellow: Pin 9
   Red: +5V
   Brown: GND
*/

//new bootloader

// Values on the servo that correspond to mouth positions.
const int FULLOPEN = 36;
const int FULLCLOSED = 18;

const int SERVO_MOUTH_PIN = 9;
const int SERVO_HEAD_PIN = 11;
const int EYES_PIN = 3;
const int SERVO_EYE_PIN = 10;

Servo servoMouth;
Servo servoHead;
Servo servoEyes;
Renard renard(Serial, 4);

//Reverse left and right on the skeleton, useful for when the parrot is on his right sholder. If so, make it true
const boolean reverseLeftAndRightHead = true;

void setup() {
  // Open serial communications
  Serial.begin(57600);
  pinMode(EYES_PIN, OUTPUT);

  servoMouth.attach(SERVO_MOUTH_PIN);
  servoMouth.write(FULLCLOSED);
  servoHead.attach(SERVO_HEAD_PIN);
  servoHead.write(90);

  servoEyes.attach(SERVO_EYE_PIN);
  servoEyes.write(89);

}

void loop() {
  // Read renard
  while (!renard.processInput())
    ;

  //Do Mouth
  int channelValueMouth = renard.channelValue(1);
  int posMouth = map(channelValueMouth, 0, 255, FULLCLOSED, FULLOPEN);
  servoMouth.write(posMouth);



  //Do Eyes Servo
  int channelValueEyes = renard.channelValue(3);
  int eyesPos = 89;
  if (channelValueEyes != 0) {
    eyesPos = map(channelValueEyes, 0, 255, 0, 180);
  }
  servoEyes.write(eyesPos);

  

  //Do Eyes
  int eyesValue = renard.channelValue(2);
  analogWrite(EYES_PIN, eyesValue);

  

  //Do Head
  int channelValueHead = renard.channelValue(4);
  int headPos = 90;
  if (channelValueHead != 0) {
    if(reverseLeftAndRightHead){
        headPos = map(channelValueHead, 0, 255, 180, 0);
    }
    else {
        headPos = map(channelValueHead, 0, 255, 0, 180);
    }
    
  }
  servoHead.write(headPos);

}
