
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
  servoHead.attach(11);
  servoLeft.attach(13);
  servoRight.attach(12);
  servoGrab.attach(10);
  servoHead.write(74);
  servoGrab.write(270);
  Serial.begin(9600);
  delay(1000);
}

void booyah(){
  if (analogRead(INFRARED_LEFT_1) < 150 && analogRead(INFRARED_RIGHT) > 150){      
      servoLeft.writeMicroseconds(1500);  //Turn right
      servoRight.writeMicroseconds(1700);
      delay(500);}
  if (analogRead(INFRARED_LEFT_1) > 150 && analogRead(INFRARED_RIGHT) > 150){
     servoLeft.writeMicroseconds(1600);  //forward
     servoRight.writeMicroseconds(1400);}
  if (analogRead(INFRARED_RIGHT) < 150 && analogRead(INFRARED_LEFT_1) > 150){      
      servoLeft.writeMicroseconds(1300);  //Turn LEFT
      servoRight.writeMicroseconds(1500);
    delay(500);}
  if (analogRead(INFRARED_RIGHT) < 150 && analogRead(INFRARED_LEFT_1) < 150){
     servoLeft.writeMicroseconds(1400);  //backward
     servoRight.writeMicroseconds(1600);
   delay(500);      
   servoLeft.writeMicroseconds(1300);  //Turn LEFT
     servoRight.writeMicroseconds(1500);
    delay(500);
   }
}

void duck()
{
servoLeft.writeMicroseconds(1500);// Stops
servoRight.writeMicroseconds(1500);

int Top = sonarTop.ping_cm();
int Bot = sonarBottom.ping_cm();

if (Bot < 20)
  {servoLeft.write(1300);  //Turn LEFT
      servoRight.write(1500);
      delay(100);
   }
      if(Bot > 20)
    {servoLeft.write(1600);  //forward
     servoRight.write(1400);delay(100);
    }
}

void booyahduck(){ int a = 1;
  while(a == 1){ 
  int Top = sonarTop.ping_cm();
  int Bot = sonarBottom.ping_cm();
  
  if (analogRead(INFRARED_LEFT_1) < 100 && analogRead(INFRARED_RIGHT) > 100 || Top < 20 )
  {      
      servoLeft.writeMicroseconds(1500);  //Turn right
      servoRight.writeMicroseconds(1700);
      delay(500);
  }
  if (analogRead(INFRARED_LEFT_1) > 100 && analogRead(INFRARED_RIGHT) > 100 && Top > 20 && Bot > 10)
    {
     servoLeft.writeMicroseconds(1600);  //forward
     servoRight.writeMicroseconds(1400);
  }
  if (analogRead(INFRARED_RIGHT) < 100 && analogRead(INFRARED_LEFT_1) > 100){      
      
      Serial.println(analogRead(INFRARED_RIGHT));
      servoLeft.writeMicroseconds(1300);  //Turn LEFT
      servoRight.writeMicroseconds(1500);
      
    delay(500);}
  if (analogRead(INFRARED_RIGHT) < 100 && analogRead(INFRARED_LEFT_1) < 100){
     servoLeft.writeMicroseconds(1400);  //backward
     servoRight.writeMicroseconds(1600);
   delay(500);      
   servoLeft.writeMicroseconds(1300);  //Turn LEFT
     servoRight.writeMicroseconds(1500);
    delay(500);
   }
  if (analogRead(INFRARED_LEFT_1) > 100 && analogRead(INFRARED_RIGHT) > 100 && Top > 20 && Bot < 10 && Bot != 0)
    {
     servoLeft.writeMicroseconds(1500);  //STOP
     servoRight.writeMicroseconds(1500);
     delay(1000);
     servoLeft.writeMicroseconds(1300);  //Turn LEFT
     servoRight.writeMicroseconds(1500);
     /*
     if(analogRead(INFRARED_LEFT_1) > 100 && analogRead(INFRARED_RIGHT) > 100 && Top > 20 && Bot < 10 && (Top-Bot) > 20 && Bot != 0){
     servoHead.write(0);
     delay(100);
     servoGrab.write(-270);      //open grabber
     delay(100);
     servoLeft.writeMicroseconds(1600);  //forward
     servoRight.writeMicroseconds(1400);
     delay(2000);
     servoGrab.write(160);    // close grabber
     servoHead.write(74);
     Serial.println("hoi");
     a = 2;*/}
    if (analogRead(INFRARED_LEFT_1) > 100 && analogRead(INFRARED_RIGHT) > 100 && Top > 20 && Bot < 10 && Bot == 0){Serial.println("Error 420: WASTED");} 
  }}
void loop()
{booyahduck();
 delay(5000);
}

