#include <Servo.h>
Servo servoHead;
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

void loop() {
  // put your main code here, to run repeatedly:
headLeft();
headRight();

Serial.println(servoHead.read());
Serial.println("grab: ");
Serial.println(servoGrab.read());
servoGrab.write(-270);
delay(3000);
forward();
delay(500);
turnLeft();
delay(500);
turnRight();
delay(500);
backWard();
delay(500);
stop();
servoGrab.write(90);
delay(3000);
}
