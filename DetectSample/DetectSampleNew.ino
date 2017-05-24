void DetectSample() {
  
  while(RockDetected == false && SampleDetected == false) {
    bool RockDetected = false;
    bool SampleDetected = false;
    int UltraSoundTop = sonarTop.convert_cm(sonarTop.ping_median(5)); //pings the distance 5 times, takes the median of close values and converts it to cm
    int UltraSoundBottom = sonarBottom.convert_cm(sonarBottom.ping_median(5)); //pings the distance 5 times, takes the median of close values and converts it to cm 
    if(UltraSoundTop-UltraSoundBottom <= 10) {
      RockDetected = true;
      SampleDetected = false;
    }
    else if(UltraSoundTop-UltraSoundBottom >= 10){ //margin of 10, acutal value defined by testing
      SampleDetected = true;
      RockDetected = false;
    }
   }
  }
    if(SampleDetected == true) {
      stop();
      for(int i; i<50;i++) { //turn robot with fifty steps to detect sample again
        ServoRight.write(180);
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
    
void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
