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

void setup() {
  // put your setup code here, to run once:
  servoHead.attach(10);
  servoLeft.attach(12);
  servoRight.attach(13);
  servoGrab.attach(11);
  servoHead.write(90);
  servoGrab.write(90);
  Serial.begin(9600);
  //attachInterrupt(digitalPinToInterrupt(FRONT_IR), LineStop, RISING);
}

float readIR(AmountRuns, SensorPin) { //reads average of IR sensors first int, second int the sensor
  int IRValues;
  for (int i = 0; i < AmountRuns; i++) {
    IRValues = IRValues + analogRead(SensorPin);
  }
  IRValueMedian = IRValues/AmountRuns;
}

void headRight(void){
  servoHead.write(60);
  delay(3000);
}

void headLeft(void){
  servoHead.write(120);
  delay(3000);
}

void forward(void){
  servoLeft.writeMicroseconds(1300);
  servoRight.writeMicroseconds(1700);
  
}

void turnLeft(void){
  servoLeft.writeMicroseconds(1300);
  servoRight.writeMicroseconds(1500);
}

void turnRight(void){
  servoLeft.writeMicroseconds(1500);
  servoRight.writeMicroseconds(1700);
}

void stop(void){
  servoLeft.writeMicroseconds(1500);
  servoRight.writeMicroseconds(1500);
}

void backWard(void){
  servoLeft.writeMicroseconds(1700);
  servoRight.writeMicroseconds(1300);
}

void AvoidObstacle() {
    
  if (InfraRedRight == 100 ) {// Wherever HIGH is mentioned, it means that it is detecting black tape (a function to obtain this 'detection' has still to be written)
        if (InfraRedLeft == 100) { 
            backWard();
            delay(1500); // TO BE DEFINED BY TESTING: an appropriate distance has to be driven backwards, in case black tape is monitored on both sides of the front of the robot
          }
          if(InfraRedLeft == 500) {
            turnLeft();
            delay(1500); // TO BE DEFINED BY TESTING: this delay time has to be sufficient so that it turns 90° to the left
          }
        }
  if (InfraRedLeft == 100)
          {if (InfraRedRight == 100)
          {backWard();
          delay(1500); // TO BE DEFINED BY TESTING: an appropriate distance has to be driven backwards, in case black tape is monitored on both sides of the front of the robot
          }
          if(InfraRedRight == 500)
          {
          turnRight();
          delay(1500); // TO BE DEFINED BY TESTING: this delay time has to be sufficient so that it turns 90° to the right
          }
        }
  if (UltraSoundTop < 15)
  {
    turnRight();
    delay(); // TO BE DEFINED BY TESTING: this delay should be to turn the robot for example 45°
             // The AvoidObstacle function should be looped, this way it checks again after turning 45° to the right, if it then doesnt detect anymore then it can carry on with movement
   if (UltraSoundTop < 15)
   {turnLeft();
   delay(); // This delay should be 2x as much as the delay to turnRight, this way it checks if there is an option to avoid the obstacle by driving to the left of it.
   } 
  } 
}

void loop() {
  float UltraSoundTop = sonarTop.convert_cm(sonarTop.ping_median(5)); //pings the distance 5 times, takes the median of close values and converts it to cm
  float UltraSoundBottom = sonarBottom.convert_cm(sonarBottom.ping_median(5)); //pings the distance 5 times, takes the median of close values and converts it to cm
  Serial.print("distance sensor top: ");
  Serial.println(UltraSoundTop);
  //Serial.print("distance sensor Bottom: ");
  //Serial.println(UltraSoundBottom);
  delay(1000);

}

