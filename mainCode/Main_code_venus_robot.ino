

#include <Servo.h> //library for servo control
#include <NewPing.h> //library for using the ultrasonic sensor
#include <String.h>

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

void DriveF(int distance)
{
  float delayTime;
  delayTime = distance*6.248;

  servoLeft.write(0);
  servoRight.write(180);

  delay(delayTime);

  servoLeft.writeMicroseconds(1500);
  servoRight.writeMicroseconds(1500);
}
void DriveB(int distance)
{
  float delayTime;
  delayTime = distance*6.248;

  servoLeft.write(180);
  servoRight.write(0);

  delay(delayTime);

  servoLeft.writeMicroseconds(1500);
  servoRight.writeMicroseconds(1500);
}

void LineFollow()
{
  boolean LineFollow=false; //line on left equals 1, no line following equals 0
  boolean exitLine=false;
  int t=0;
  Serial.println(INFRARED_LEFT_1);
    Serial.println(INFRARED_LEFT_2);
    Serial.println(analogRead(A42));
if(LineFollow==false)
{
  if(analogRead(INFRARED_LEFT_2) < 150)
  {
    //turnLeftDegree(); // is this necessary?
    LineFollow=true;
  }
  else if(analogRead(INFRARED_RIGHT)< 150){
    //turnRightDegree();
    servoLeft.write(180);
    servoRight.write(0);
    delay(200);
    while(!(analogRead(INFRARED_LEFT_2)<150)){
    if(t<99999){
    servoLeft.write(0);
    servoRight.write(90);
    t++;}
    
  
    else if(t>=99999){
      loop();
    }
    }
    LineFollow=true;
  }
  else if(analogRead(INFRARED_LEFT_1) > 250 && analogRead(INFRARED_LEFT_2) > 250){
    servoLeft.write(0);
  servoRight.write(180);
}
else if(LineFollow==true && exitLine == false)
{
  if(analogRead(INFRARED_LEFT_1) < 150 && analogRead(INFRARED_LEFT_2) < 150)
  {
      turnRightDegree(5);  //Distance itself a bit from the border
   }
  else if(analogRead(INFRARED_LEFT_2) > 250) //If it 'lost' the tape
  {
      turnLeftDegree(5);
  }
  else if(analogRead(INFRARED_LEFT_1)>250 && analogRead(INFRARED_LEFT_2) < 150)
  {
    DriveF(3);
  }
}

else if(exitLine==true)
{
  if(analogRead(INFRARED_LEFT_2)> 250 && analogRead(INFRARED_RIGHT) > 250)
  {
    exitLine = false;
    LineFollow=false;
  }
}

}
}

void loop() 
{
  float UltraSoundTop = sonarTop.convert_cm(sonarTop.ping_median(5)); //pings the distance 5 times, takes the median of close values and converts it to cm
  float UltraSoundBottom = sonarBottom.convert_cm(sonarBottom.ping_median(5)); //pings the distance 5 times, takes the median of close values and converts it to cm
  Serial.print("distance sensor top: ");
  Serial.println(UltraSoundTop);
  //Serial.print("distance sensor Bottom: ");
  //Serial.println(UltraSoundBottom);
  delay(1000);
 LineFollow();

}

// What needs to be added:
// Find Rock Sample function using the bottom ultrasound sensor
// Detect obstacle function using the top ultrasound sensor
// Moving back to base function
// Grabbing rock sample 
// Proper loop structure such that the robot can act autonomously
