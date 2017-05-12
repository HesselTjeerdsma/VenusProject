#include <Servo.h>

Servo servoLeft;
Servo servoRight;
Servo servoGrab;


void setup() {
  // put your setup code here, to run once:

  servoLeft.attach(12);
  servoRight.attach(13);
  servoGrab.attach(11);
  servoLeft.write(90);
  servoRight.write(90);
    servoGrab.write(-270);

}

void turnLeftDegree(int degree){
  float delayTime;
  delayTime=degree*6.248;

  servoLeft.write(180);
  servoRight.write(180);

  delay(delayTime);

  servoLeft.writeMicroseconds(1500);
  servoRight.writeMicroseconds(1500);
}

void turnLeftDegree(int degree){
  float delayTime;
  delayTime=degree*6.248;

  servoLeft.write(0);
  servoRight.write(0);

  delay(delayTime);

  servoLeft.writeMicroseconds(1500);
  servoRight.writeMicroseconds(1500);
}

void loop() {
  // put your main code here, to run repeatedly:\

turnLeftDegree(360);
delay(2000);

}
