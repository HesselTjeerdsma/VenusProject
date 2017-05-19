void DetectSample() { 
  bool Sample = false;
  bool Wall = false;
  int Object;
  for (int Steps = 0; Steps < 12; Steps++) {
    servoHead.write(15*Steps);
    delay(1000);
    float UltraSoundTop = sonarTop.convert_cm(sonarTop.ping_median(5)); //pings the distance 5 times, takes the median of close values and converts it to cm
    float UltraSoundBottom = sonarBottom.convert_cm(sonarBottom.ping_median(5)); //pings the distance 5 times, takes the median of close values and converts it to cm 
    if (Sample == false) {
      if (UltraSoundTop < 150 && UltraSoundBottom < 150) {
        Wall = true;
      }
      else if(UltraSoundTop > 150 && UltraSoundBottom < 150) {
        Sample = true;
      }
   }
  if (Wall == true) {
    Object = 2;
  }
  if (Sample == true) {
    Object = 1;
  }
  if (Sample == false && Wall == false) {
      Object = 0;
    }
  if (Object == true) {
    MoveToObject();
  }
   break;
  }
  
 }
