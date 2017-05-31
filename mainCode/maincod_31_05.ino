//todo:
//picking up the sample after detection
//retrun to line after too many tries
//actual values


#include <Servo.h> //library for servo control
#include <NewPing.h> //library for using the ultrasonic sensor
#include <String.h>
boolean lineFollow = false; 

//Define the pins
#define FRONT_IR 
#define ECHO_PIN_TOP 9 //ports subject to change
#define TRIGGER_PIN_TOP 9
#define ECHO_PIN_BOTTOM 2
#define TRIGGER_PIN_BOTTOM 3 
#define MAX_DISTANCE 200 //in cm
#define INFRARED_LEFT_1 A0
#define INFRARED_LEFT_2 A1
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
  servoGrab.write(0);
  Serial.begin(9600);
}

void stop() {
  servoRight.writeMicroseconds(1500);
  servoLeft.writeMicroseconds(1500);
}
void DetectSample() {
  int UltraSoundTop = sonarTop.convert_cm(sonarTop.ping_median(5)); //pings the distance 5 times, takes the median of close values and converts it to cm
  int UltraSoundBottom = sonarBottom.convert_cm(sonarBottom.ping_median(5)); //pings the distance 5 times, takes the median of close values and converts it to cm
  bool RockDetected = false;
  bool SampleDetected = false;
  while(RockDetected == false && SampleDetected == false) {
    LineFollow(); 
    if(UltraSoundTop-UltraSoundBottom <= 10) {
      RockDetected = true;
      SampleDetected = false;
    }
    else if(UltraSoundTop-UltraSoundBottom >= 10){ //margin of 10, acutal value defined by testing
      SampleDetected = true;
      RockDetected = false;
    }
   }
    if(SampleDetected == true) {
      stop();
      for(int i; i<50;i++) { //turn robot with fifty steps to detect sample again
        servoRight.write(180);
        delay(50); 
        if(UltraSoundTop-UltraSoundBottom >= 10){ //margin of 10, acutal value defined by testing
          return; 
        }
      }
    }
    while(UltraSoundBottom >= 5) {
     servoLeft.write(180);  // go straight
     servoRight.write(180); 
     delay(50);
     int Tries; //if too long robot needs to return to outer edge because there was no block
     Tries++;
     if(Tries >= 100)
      return;
    }
    
}

void headRight()
{
  servoHead.write(60);
  delay(3000);
}

void headLeft()
{
  servoHead.write(120);
  delay(3000);
}

void LineFollow()
{
  boolean exitLine=false;

if(lineFollow==false){
   if(analogRead(INFRARED_LEFT_1) > 250 && analogRead(INFRARED_LEFT_2) > 250){
      servoLeft.write(180); // LEFT FORWARD //Drive forward
      servoRight.write(0);// RIGHT FORWARD
   }
   if(analogRead(INFRARED_LEFT_2) < 100)
  {
    lineFollow = true;
    
   servoLeft.write(1500);  //Turn right
    servoRight.write(1700);
   
  }
  
}
if( lineFollow==true){
  Serial.println(analogRead(INFRARED_LEFT_1));
  if((analogRead(INFRARED_LEFT_1) < 100))
  {
    
    servoLeft.write(1500);  //Turn right
    servoRight.write(1700);  //
    Serial.println("turnright");
   }


   else if((analogRead(INFRARED_LEFT_2) < 100)&&(analogRead(INFRARED_LEFT_1) > 150))
  {
    servoLeft.write(180);  //Turn left
    servoRight.write(0);  //
    Serial.println("drive");
   }
   
}

}
void loop(){
  float UltraSoundTop = sonarTop.convert_cm(sonarTop.ping_median(5)); //pings the distance 5 times, takes the median of close values and converts it to cm
  float UltraSoundBottom = sonarBottom.convert_cm(sonarBottom.ping_median(5)); //pings the distance 5 times, takes the median of close values and converts it to cm
  
   DetectSample();
/*   Serial.println("IR LEFT 1");
  Serial.println(analogRead(INFRARED_LEFT_1));
  Serial.println("IR LEFT 2");
  Serial.println(analogRead(INFRARED_LEFT_2));
  Serial.println("IR RIGHT");
  Serial.println(analogRead(INFRARED_RIGHT));*/
}

// What needs to be added:
// Find Rock Sample function using the bottom ultrasound sensor
// Detect obstacle function using the top ultrasound sensor
// Moving back to base function
// Grabbing rock sample 
// Proper loop structure such that the robot can act autonomously
