int LeftRight=0;//line on left equals 1, line on the right equals 2, no line following equals 0
boolean exitLine=false;

if(LeftRight==0){
  if(INFRARED_LEFT_2==HIGH){
    turnLeft();
        LeftRight=1;
  }
  else if(INFRARED_RIGHT_2==HIGH){
    turnLeft();
    LeftRight=2;
  }
}
else if(LeftRight==1 && exitLine==false){
  if(INFRARED_LEFT_1==HIGH && INFRARED_LEFT_2==HIGH){
      turnRight();
    }
  else if(INFRARED_lEFT_2==LOW){
      turnLeft();
    }
  else if(INFRARED_LEFT_1==LOW && INFRARED_LEFT_2==HIGH){
    forward();
  }
}
else if(LeftRight==2 && exitLine==false){
  if(INFRARED_RIGHT_1==HIGH && INFRARED_RIGHT_2==HIGH){
    turnLeft();
    }
  else if(INFRARED_RIGHT_2==LOW){
    turnRight();
    }
  else if(INFRARED_RIGHT_1==LOW && INFRARED_RIGHT_2==HIGH){
    forward();
  }
}
else if(exitLine==true){
  if(INFRARED_lEFT_2==LOW && INFRARED_RIGHT_2==LOW){
    exitLine=false;
    LeftRight=0;
  }
}

