void DetectSample()
{ 
  for (int Steps = 0; Steps < 12; Steps = Steps++)
  {
  servoHead.write(15*Steps);
  delay(1000);
  float UltraSoundTop = sonarTop.convert_cm(sonarTop.ping_median(5)); //pings the distance 5 times, takes the median of close values and converts it to cm
  float UltraSoundBottom = sonarBottom.convert_cm(sonarBottom.ping_median(5)); //pings the distance 5 times, takes the median of close values and converts it to cm 
  
  Sample = 0;
  Wall = 0;
  
  if (Sample == 0)
   {
    if (UltraSoundTop < 150 && UltraSoundBottom < 150)
    Wall = 1;
    else if (UltraSoundTop > 150 && UltraSoundBottom < 150)
    Sample = 1;
   }
  if (Wall == 1)
  {
    Object = 2;
  }
  if (Sample == 1)
  {
    Object = 1;
  }
  if (Sample == 0 && Wall == 0)
  {Object = 0;}
  if (Object == 1)
  {MoveToObject;
   break;
  }
  
 }
