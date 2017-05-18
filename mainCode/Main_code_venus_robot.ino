#include <Servo.h> //library for servo control
#include <NewPing.h> //library for using the ultrasonic sensor

//Define the pins
#define FRONT_IR 
#define ECHO_PIN_TOP 9 //ports subject to change
#define TRIGGER_PIN_TOP 9
#define ECHO_PIN_BOTTOM 2
#define TRIGGER_PIN_BOTTOM 3 
#define MAX_DISTANCE 200 //in cm

NewPing sonarTop(TRIGGER_PIN_TOP, ECHO_PIN_TOP, MAX_DISTANCE); //setup function for distance-sensor-TOP
NewPing sonarBottom(TRIGGER_PIN_BOTTOM, ECHO_PIN_BOTTOM, MAX_DISTANCE); //setup function for distance-sensor-BOTTOM

Servo servoHead; //definition of servos
Servo servoLeft;
Servo servoRight;
Servo servoGrab;

void setup() 
{
  //SETUP CODE, runs once
  servoHead.attach:(10);
  servoLeft.attach(12);
  servoRight.attach(13);
  servoGrab.attach(11);
  servoHead.write(90);
  servoGrab.write(90);
  Serial.begin(9600);
}

int readIR(AmountRuns, SensorPin) 
{ //reads average of IR sensors first int, second int the sensor
  int IRValues;
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
  int LeftRight=0; //line on left equals 1, line on the right equals 2, no line following equals 0
  boolean exitLine=false;

if(LeftRight==0)
{
  if(INFRARED_LEFT_2 == 100)
  {
    //turnLeftDegree(); // is this necessary?
    LeftRight=1;
  }
  else if(INFRARED_RIGHT_2== 100){
    //turnRightDegree();
    LeftRight=2;
  }
}
else if(LeftRight==1 && exitLine == false)
{
  if(INFRARED_LEFT_1 == 100 && INFRARED_LEFT_2 == 100)
  {
      turnRightDegree(5);  //Distance itself a bit from the border
   }
  else if(INFRARED_lEFT_2== 500) //If it 'lost' the tape
  {
      turnLeftDegree(5);
  }
  else if(INFRARED_LEFT_1== 500 && INFRARED_LEFT_2== 100)
  {
    DriveF(3);
  }
}
else if(LeftRight==2 && exitLine==false)
{
  if(INFRARED_RIGHT_1== 100 && INFRARED_RIGHT_2== 100)
  {
    turnLeftDegree(5);
  }
  else if(INFRARED_RIGHT_2== 500)
  {
    turnRightDegree(5);
  }
  else if(INFRARED_RIGHT_1== 500 && INFRARED_RIGHT_2== 100)
  {
    DriveF(3);
  }
}
else if(exitLine==true)
{
  if(INFRARED_lEFT_2== 500 && INFRARED_RIGHT_2== 500)
  {
    exitLine = false;
    LeftRight=0;
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

}

// What needs to be added:
// Find Rock Sample function using the bottom ultrasound sensor
// Detect obstacle function using the top ultrasound sensor
// Moving back to base function
// Grabbing rock sample 
// Proper loop structure such that the robot can act autonomously
