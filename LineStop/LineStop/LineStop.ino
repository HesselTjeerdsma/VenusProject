//Define the pins
#define FRONT_IR //smith-trigger circuit?

//global variables

void LineStop() { //function to stop the motors called by interrupt
  
}


void setup() {
  attachInterrupt(digitalPinToInterrupt(FRONT_IR), LineStop, RISING);

}

void loop() {
  // put your main code here, to run repeatedly:
  
}
