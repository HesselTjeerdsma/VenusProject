#include <Servo.h> //library for servo control
#include <NewPing.h> //library for using the ultrasonic sensor
#include <String.h>

//Define the pins
#define FRONT_IR 
#define ECHO_PIN_TOP 9 //ports subject to change
#define TRIGGER_PIN_TOP 9
#define ECHO_PIN_BOTTOM 2
#define TRIGGER_PIN_BOTTOM 3 
#define MAX_DISTANCE 2000 //in cm
#define INFRARED_LEFT_1 A1
#define INFRARED_LEFT_2 A0
#define INFRARED_RIGHT A2



NewPing sonarTop(TRIGGER_PIN_TOP, ECHO_PIN_TOP, MAX_DISTANCE); //setup function for distance-sensor-TOP
NewPing sonarBottom(TRIGGER_PIN_BOTTOM, ECHO_PIN_BOTTOM, MAX_DISTANCE); //setup function for distance-sensor-BOTTOM

Servo servoHead; //definition of servos
Servo servoLeft;
Servo servoRight;
Servo servoGrab;

void setup() 
{
  //SETUP CODE, runs once
  servoHead.attach(10);
  servoLeft.attach(13);
  servoRight.attach(12);
  servoGrab.attach(11);
  servoHead.write(90);
  servoGrab.write(90);
  Serial.begin(9600);
}

void booyah()
{
  if (analogRead(INFRARED_LEFT_1) < 150){      
      servoLeft.write(1500);  //Turn right
      servoRight.write(1700);
      delay(500);}
  if (analogRead(INFRARED_LEFT_1) > 150){
     servoLeft.write(1600);  //forward
     servoRight.write(1400); }
  if (analogRead(INFRARED_RIGHT) < 150){      
      servoLeft.write(1300);  //Turn LEFT
      servoRight.write(1500); }
  if (analogRead(INFRARED_RIGHT) > 150){
     servoLeft.write(1600);  //forward
     servoRight.write(1400); }
}
void duck(){int Top = sonarTop.ping_cm();
int Bot = sonarBottom.ping_cm();
if (Bot < 20){servoLeft.write(1300);  //Turn LEFT
      servoRight.write(1500);
      delay(100);}
      if(Bot > 10){servoLeft.write(1600);  //forward
     servoRight.write(1400);delay(100);}}
void loop(){booyah();int Top = sonarTop.ping_cm();
int Bot = sonarBottom.ping_cm();duck();
}

