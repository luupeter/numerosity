
// constants won't change
const int trig = 2; //from camera trig
const int heatlaser = 3; //TTL to thorLab healting laser
const int laseronset = 30; //when the laser first turns on in seconds
const int laserontime = 3; //how long the laser burn for in seconds

// Variables will change:
int trigPushCounter = 0;   // counter for the number of trigger presses
int trigstate = 0;         // current state of the trigger
int lastTrigState = 0;     // previous state of the trigger

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 57600 bits per second:
  Serial.begin(57600);
  // make the hamatrig's pin an input:
  pinMode (trig, INPUT); // initialize camera trigger as as input
  pinMode (heatlaser, OUTPUT); // initialize pin 3 as output
}

void loop() {
  // put your main code here, to run repeatedly:
  // read the input pin:
  int trigstate = digitalRead(trig);  //for serial port
  Serial.println(trigstate);
  if (trigstate != lastTrigState) {
    // if the state has changed, increment the counter
    if (trigstate == HIGH) {
      trigPushCounter++;
    } 
  }
  lastTrigState = trigstate;

//turn on heating laser for x amount of time then turn off
  if (trigPushCounter == ((26 * laseronset))) { 
    digitalWrite (heatlaser, HIGH);
  }
  //turns heating off
  else if (trigPushCounter == ((26 * laseronset)+(26 * laserontime))) {
    digitalWrite (heatlaser, LOW);
    trigPushCounter = 0;     //reset counter
  }
}
