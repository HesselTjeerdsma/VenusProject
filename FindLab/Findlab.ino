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
#define INFRARED_FRONT A4



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
  servoLeft.attach(12);
  servoRight.attach(13);
  servoGrab.attach(10);
  servoHead.write(90);
  servoGrab.write(270);
  Serial.begin(9600);
}

int readIR(int AmountRuns, int SensorPin) 
{ //reads average of IR sensors first int, second int the sensor
  int IRValues;
  int IRValueMedian;
    for (int i = 0; i < AmountRuns; i++) 
    {
      IRValues = IRValues + analogRead(SensorPin);
      delay(200);
    }
  IRValueMedian = IRValues/AmountRuns;
  return IRValueMedian;
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

void turnLeftDegree(int degree)
{
  float delayTime;
  delayTime = degree*6.248;

  servoLeft.write(180);
  servoRight.write(180);

  delay(delayTime);

  servoLeft.writeMicroseconds(1500);
  servoRight.writeMicroseconds(1500);
}

void turnRightDegree(int degree)
{
  float delayTime;
  delayTime = degree*6.248;

  servoLeft.write(0);
  servoRight.write(0);

  delay(delayTime);

  servoLeft.writeMicroseconds(1500);
  servoRight.writeMicroseconds(1500);
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

void LocateLab(){

  int topIR = A3;
  int previousIR = 0;
  
  do{   
    previousIR = analogRead(topIR);
    turnLeftDegree(10);    
  }while(analogRead(topIR) >= previousIR);
  
  do{   
    previousIR = analogRead(topIR);
    turnRightDegree(10);    
  }while(analogRead(topIR) >= previousIR);
  
  turnLeftDegree(10);
  
}

void LocateLabButMaybeBetter(){

  int topIR = A3;
  int previousIR = 0; 
  int maxIR = 0;
  
  for (int i = 0; i < 360; i = i + 10){
    if(analogRead(topIR) >= previousIR){
      maxIR = analogRead(topIR);
    }
  previousIR = analogRead(topIR);
  turnLeftDegree(10);
  }
  
  do{turnLeftDegree(10);}while(analogRead(topIR) < (maxIR*0.9));
  
}

void GotoLab(){

  int topIR = A3;
  obstacle:
  LocateLab(); // Find direction of lab

  // Go forward until lab wall
   
  do{
    servoLeft.write(0);
    servoRight.write(180);
    delay(10);
    float UltraSoundTop = sonarTop.convert_cm(sonarTop.ping_median(5));
    
    if(UltraSoundTop < 10 || analogRead(INFRARED_FRONT) < 150){ // Wall or obstacle blocking the way
      if(analogRead(topIR) < 800){ // If IR too low, mountain found
          //AvoidObstacle();
          goto obstacle;
      }
      break; 
    }   
  } while(1);
  
  servoLeft.writeMicroseconds(1500);
  servoRight.writeMicroseconds(1500);
  headLeft();

  float USprevious = 1000;
  float UltraSoundTop;
  float UltraSoundBottom;
  float maintainDist;
  
  // Turn robot parallel to wall, by minimizig distance
  
  for (int i = 0; i < 360; i = i + 10){ 
    float UltraSoundTop = sonarTop.convert_cm(sonarTop.ping_median(5));
    if(UltraSoundTop <= USprevious){
      float maintainDist = UltraSoundTop;
    }
  USprevious = UltraSoundTop;
  turnRightDegree(10);
  }
  
  do{turnRightDegree(10); float UltraSoundTop = sonarTop.convert_cm(sonarTop.ping_median(5));}while(UltraSoundTop > (maintainDist*1.1));
  maintainDist = sonarTop.convert_cm(sonarTop.ping_median(5));

  // Follow wall and enter lab

  do{
    float UltraSoundTop = sonarTop.convert_cm(sonarTop.ping_median(5));
    float UltraSoundBottom = sonarBottom.convert_cm(sonarBottom.ping_median(5));
    
    if(UltraSoundTop > maintainDist*0.9 && UltraSoundTop < maintainDist*1.1){ // distance between robot and wall is maintained, go forward
      servoLeft.write(0);
      servoRight.write(180);
      delay(10);
      
    } else if(UltraSoundTop < maintainDist*0.9){ // distance decreased so robot swaying to left, turn right to compensate
      turnRightDegree(10);
      servoLeft.write(0);
      servoRight.write(180);
      delay(10);
      
    } else if(UltraSoundTop > maintainDist*1.1 && UltraSoundTop < maintainDist*2){ // distance increased so robot swaying to right, turn left to compensate 
      turnRightDegree(10);
      servoLeft.write(0);
      servoRight.write(180);
      delay(10);
      
    } else { // robot reached edge of lab
      servoLeft.write(0);
      servoRight.write(180);
      delay(50);
      
      turnLeftDegree(90);

      servoLeft.write(0);
      servoRight.write(180);
      delay(50);

      float UltraSoundTop = sonarTop.convert_cm(sonarTop.ping_median(5));
      float UltraSoundBottom = sonarBottom.convert_cm(sonarBottom.ping_median(5));

      if(UltraSoundTop > UltraSoundBottom*2){ // check if new edge is wall or entrance
        turnLeftDegree(90);
        headRight();
        do{
          servoLeft.write(0);
          servoRight.write(180);
          delay(50);
          
        } while(analogRead(INFRARED_FRONT) > 150);   
        break;
      }
    }
    
  }while(1);

  do{LineFollow();} while(analogRead(INFRARED_FRONT) > 150); // Follow ramp until second edge
  
  // drop rock sample
  turnRightDegree(180);
  do{LineFollow();} while(analogRead(INFRARED_FRONT) > 150); // Follow ramp line until entrance to lab
   
}

void loop() 
{
  float UltraSoundTop = sonarTop.convert_cm(sonarTop.ping_median(5)); //pings the distance 5 times, takes the median of close values and converts it to cm
  float UltraSoundBottom = sonarBottom.convert_cm(sonarBottom.ping_median(5)); //pings the distance 5 times, takes the median of close values and converts it to cm
  //Serial.print("distance sensor top: ");
  //Serial.println(UltraSoundTop);
  //Serial.print("distance sensor Bottom: ");
  //Serial.println(UltraSoundBottom);

}

// What needs to be added:
// Find Rock Sample function using the bottom ultrasound sensor
// Detect obstacle function using the top ultrasound sensor
// Moving back to base function
// Grabbing rock sample 
// Proper loop structure such that the robot can act autonomously
