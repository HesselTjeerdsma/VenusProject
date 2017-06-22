#include <Servo.h> //library for servo control
#include <NewPing.h> //library for using the ultrasonic sensor
#include <String.h>
boolean lineFollow = false;
int t=0;

//Define the pins
#define FRONT_IR 
#define ECHO_PIN_TOP 9 //ports subject to change
#define TRIGGER_PIN_TOP 9
#define ECHO_PIN_BOTTOM 2
#define TRIGGER_PIN_BOTTOM 3 
#define MAX_DISTANCE 2000 //in cm
#define INFRARED_LEFT_1 A0
#define INFRARED_LEFT_2 A1
#define INFRARED_RIGHT A2
#define INFRARED_BOTTOM A5



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
  servoLeft.attach(12);
  servoRight.attach(13);
  servoGrab.attach(11);
  
  servoHead.write(90);
  servoGrab.write(-270);
  Serial.begin(9600);
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
    t=0;
   servoLeft.write(1500);  //Turn right
    servoRight.write(1700);
   
  }
  if((analogRead(INFRARED_RIGHT)<100)||(analogRead(INFRARED_BOTTOM)<100)){
    servoLeft.write(0);
    servoRight.write(180);
    delay(500);
    servoLeft.write(180);
    servoRight.write(180);
    delay(750);
    servoLeft.write(180);
    servoRight.write(0);
  }
  
}
if( lineFollow==true && exitLine==false){
  Serial.println(analogRead(INFRARED_LEFT_1));
  if((analogRead(INFRARED_LEFT_1) < 100))
  {
    
    servoLeft.write(1500);  //Turn right
    servoRight.write(1700);  //
    Serial.println("turnright");
   }

   if((analogRead(INFRARED_LEFT_1) > 250)&&(analogRead(INFRARED_LEFT_2) > 250)&&(analogRead(INFRARED_RIGHT) > 150) ){
    servoLeft.write(1500);
    servoRight.write(1300);
   }
   else if((analogRead(INFRARED_LEFT_2) < 100)&&(analogRead(INFRARED_LEFT_1) > 150))
  {
    servoLeft.write(180);  
    servoRight.write(0);  //
    Serial.println("drive");
   }
   
}

}

/*
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
  
}*/

void LocateLab(){

  int topIR = A3;
  int previousIR = 0; 
  int maxIR = 0;
  
  for (int i = 0; i < 100; i++){
    if(analogRead(topIR) > previousIR){
      maxIR = analogRead(topIR);
    }
    
    Serial.print("Current Max: ");
    Serial.print(maxIR);
    Serial.print(" Current Reading: ");
    Serial.println(analogRead(topIR));
    
    previousIR = analogRead(topIR);
    servoLeft.writeMicroseconds(1600);
    servoRight.writeMicroseconds(1600);
    delay(50);
  }

  Serial.print("Max found! ");
  Serial.println(maxIR);
  
  do{
    
    servoLeft.writeMicroseconds(1600);
    servoRight.writeMicroseconds(1600);
    
  }while(analogRead(topIR) < (maxIR*0.9));

  servoLeft.writeMicroseconds(1500);
  servoRight.writeMicroseconds(1500);

  Serial.println("Found lab!");
  delay(5000);
  
}

void GotoLab(){

  int topIR = A3;
  int UltraSoundTop;
  obstacle:
  
  // LocateLab(); // Find direction of lab

  // Go forward until lab wall 
  do{
    
    servoLeft.writeMicroseconds(1400);
    servoRight.writeMicroseconds(1600);
    
    UltraSoundTop = sonarTop.convert_cm(sonarTop.ping_median(2));
    Serial.println(UltraSoundTop);
    Serial.println("Going to lab!");
    
    // Wall or obstacle blocking the way
    
    if(UltraSoundTop < 15){
      break;
    }
        
  } while(1);

  Serial.println("I am at lab!");
  servoLeft.writeMicroseconds(1500);
  servoRight.writeMicroseconds(1500);
  delay(1000);
  servoHead.write(180);
  delay(1000);

  do{

    something:
    UltraSoundTop = sonarTop.convert_cm(sonarTop.ping_median(2));
    Serial.println(UltraSoundTop);
    servoLeft.writeMicroseconds(1600);
    servoRight.writeMicroseconds(1600);

    Serial.println("Turning perpendicular!");
      
  }while(UltraSoundTop > 20);
  if(UltraSoundTop < 10){goto something;}

  servoLeft.writeMicroseconds(1500);
  servoRight.writeMicroseconds(1500);
  delay(2000);

  do{

    UltraSoundTop = sonarTop.convert_cm(sonarTop.ping_median(2));
    Serial.println(UltraSoundTop);
    servoLeft.writeMicroseconds(1600);
    servoRight.writeMicroseconds(1600);

    Serial.println("Turning perpendicular again!");
      
  }while(UltraSoundTop < 60);
  
  /*
  for(int i = 0; i < 11; i++){
    UltraSoundTop = sonarTop.convert_cm(sonarTop.ping_median(2));
    if(UltraSoundTop > 20){goto something;}
    delay(100);
  }*/
  
  servoLeft.writeMicroseconds(1500);
  servoRight.writeMicroseconds(1500);
  Serial.println("Done!");
  Serial.println(UltraSoundTop);
  delay(1000);
  
  int maintainDist = 25;

  // Follow wall and enter lab

  do{
    Serial.println("Following wall now!");
    UltraSoundTop = sonarTop.convert_cm(sonarTop.ping_median(2));
    Serial.println(UltraSoundTop);
    servoLeft.writeMicroseconds(1500);
    servoRight.writeMicroseconds(1500);
    //delay(500);
    
    if(analogRead(INFRARED_BOTTOM) < 100){break;}
    
    if(UltraSoundTop > maintainDist*0.9 && UltraSoundTop < maintainDist*1.1){ // distance between robot and wall is maintained, go forward
      Serial.println("Distance maintained..");
      servoLeft.writeMicroseconds(1400);
      servoRight.writeMicroseconds(1600);
      
    } else if(UltraSoundTop < maintainDist*0.9){ // distance decreased so robot swaying to left, turn right to compensate
      Serial.println("Distance decreasing.. Turning right..");
      servoLeft.writeMicroseconds(1600);
      servoRight.writeMicroseconds(1600);
      delay(30);
      servoLeft.writeMicroseconds(1400);
      servoRight.writeMicroseconds(1600);
      delay(20);
      
    } else if(UltraSoundTop > maintainDist*1.1 && UltraSoundTop < maintainDist*2){ // distance increased so robot swaying to right, turn left to compensate 
      Serial.println("Distance increasing.. Turning left..");
      servoLeft.writeMicroseconds(1400);
      servoRight.writeMicroseconds(1400);
      delay(30);
      servoLeft.writeMicroseconds(1400);
      servoRight.writeMicroseconds(1600);
      delay(20);

    } else { // robot reached edge of lab
      Serial.println("Corner reached.. Turning 90 degrees left.. ");
      servoLeft.write(0);
      servoRight.write(180);
      delay(75);
    
      servoLeft.writeMicroseconds(1400);
      servoRight.writeMicroseconds(1400);
      delay(100);

      servoLeft.write(0);
      servoRight.write(180);
      delay(50);
    }
    
  }while(1);
  servoLeft.writeMicroseconds(1400);
  servoRight.writeMicroseconds(1600);
  delay(500);
  servoLeft.writeMicroseconds(1500);
  servoRight.writeMicroseconds(1500);
  
  // do{LineFollow();} while(analogRead(INFRARED_BOTTOM) > 150); // Follow ramp until second edge
  
  // drop rock sample
  //do{LineFollow();} while(analogRead(INFRARED_FRONT) > 150); // Follow ramp line until entrance to lab
   
}

void Lab(){

int UltraSoundTop;
int maintainDist = 30;

  // Follow wall and enter lab

  servoHead.write(90);
  delay(500);
   
  do{
    
    servoLeft.writeMicroseconds(1400);
    servoRight.writeMicroseconds(1600);
    
    UltraSoundTop = sonarTop.ping_cm();
    Serial.println(UltraSoundTop);
    Serial.println("Going to lab!");
    
    // Wall or obstacle blocking the way
    
    if(UltraSoundTop < 30){
      break;
    }
        
  } while(1);

  Serial.println("I am at lab!");
  servoLeft.writeMicroseconds(1500);
  servoRight.writeMicroseconds(1500);
  delay(1000);
  servoHead.write(180);

  servoLeft.writeMicroseconds(1600);
  servoRight.writeMicroseconds(1600);
  delay(500);
  servoLeft.writeMicroseconds(1500);
  servoRight.writeMicroseconds(1500);
  delay(50);
  
  do{

    int UltraSoundTopBefore = sonarTop.ping_cm(); 
    int UltraSoundBottom = sonarTop.ping_cm();
    int USmin = 1000;

    for(int i = 180; i > 135; i--){
      servoHead.write(i);
      delay(10); 
      UltraSoundTop = sonarTop.ping_cm();
      if(UltraSoundTop < USmin){USmin = UltraSoundTop;} 
    }
    
    servoHead.write(180);
    delay(500);

    Serial.print("UltraSoundTopBefore: ");
    Serial.print(UltraSoundTopBefore);
    Serial.print(" USmin: ");
    Serial.println(USmin);

    if(UltraSoundTopBefore > 100){UltraSoundTopBefore = 100;}
    if(USmin > 100){USmin = 100;}
    
    //if(analogRead(INFRARED_BOTTOM) < 100 || analogRead(INFRARED_LEFT_1) < 100 || analogRead(INFRARED_LEFT_2) < 100){break;}
    //if(UltraSoundTopBefore - UltraSoundBottom > 50 || UltraSoundBottom - UltraSoundTopBefore > 50){break;}

    if(UltraSoundTopBefore > 50 && USmin > 50){
      servoLeft.writeMicroseconds(1400);
      servoRight.writeMicroseconds(1400);
      delay(150);  
    }
     
    if(UltraSoundTopBefore > USmin){ // distance decreased so robot swaying to left, turn right to compensate
      Serial.println("Distance decreasing.. Turning right..");
      
      servoLeft.writeMicroseconds(1600);
      servoRight.writeMicroseconds(1600);
      delay(150);
      servoLeft.writeMicroseconds(1400);
      servoRight.writeMicroseconds(1600);
      delay(300);
      
    } else { // distance increased so robot swaying to right, turn left to compensate 
      Serial.println("Distance increasing.. Turning left..");
      servoLeft.writeMicroseconds(1400);
      servoRight.writeMicroseconds(1400);
      delay(150);
      servoLeft.writeMicroseconds(1400);
      servoRight.writeMicroseconds(1600);
      delay(300);

      if(UltraSoundTop > maintainDist*0.9 && UltraSoundTop < maintainDist*1.1){ // distance between robot and wall is maintained, go forward
        Serial.println("Distance maintained..");
        servoLeft.writeMicroseconds(1400);
        servoRight.writeMicroseconds(1600);
        delay(200);
      
      } else if(UltraSoundTop < maintainDist*0.9){ // distance decreased so robot swaying to left, turn right to compensate
        Serial.println("Distance decreasing.. Turning right..");
        servoLeft.writeMicroseconds(1600);
        servoRight.writeMicroseconds(1600);
        delay(100);
        servoLeft.writeMicroseconds(1400);
        servoRight.writeMicroseconds(1600);
        delay(200);
      
      } else if(UltraSoundTop > maintainDist*1.1){ // distance increased so robot swaying to right, turn left to compensate 
        Serial.println("Distance increasing.. Turning left..");
        servoLeft.writeMicroseconds(1400);
        servoRight.writeMicroseconds(1400);
        delay(100);
        servoLeft.writeMicroseconds(1400);
        servoRight.writeMicroseconds(1600);
        delay(200);

      }

    } 
    
    servoLeft.writeMicroseconds(1500);
    servoRight.writeMicroseconds(1500);
    delay(50);
    
  }while(1);

  servoLeft.writeMicroseconds(1400);
  servoRight.writeMicroseconds(1400);
  delay(500);
  servoLeft.writeMicroseconds(1400);
  servoRight.writeMicroseconds(1600);
  delay(1500);
  servoLeft.writeMicroseconds(1500);
  servoRight.writeMicroseconds(1500);
  delay(10000); 
 
}

void loop() 
{
 
Lab();

/*
  int IRmin = 1000;
  int m;
 
 servoLeft.writeMicroseconds(1600);
 servoRight.writeMicroseconds(1600);
 delay(50);

 Serial.println(analogRead(A3));
 
 if(analogRead(A3) < 50){
  servoLeft.writeMicroseconds(1500);
  servoRight.writeMicroseconds(1500);
  delay(50);

  for(int m = 0 ; m < 6 ; m++ ){

    servoHead.write(120);
    delay(500);
 
    for(int i = 120; i > 60; i--){
      servoHead.write(i);
      delay(10); 
      if(analogRead(A3) < IRmin){IRmin = analogRead(A3);} 
    }

    servoHead.write(90);
    delay(500);
    
  }
  if(m == 5){
  
    Serial.println("I FOUND THE LAB!!!!!!!!!!!!!!!!!!");
    delay(10000); 
      
  }
 }
 */

}

