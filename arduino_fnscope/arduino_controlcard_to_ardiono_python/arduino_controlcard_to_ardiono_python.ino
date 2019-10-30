
// digital pin 2 has a the hamamatsu triggering input
int trig = 2;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 57600 bits per second:
  Serial.begin(9600);
  // make the hamatrig's pin an input:
  pinMode (trig, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  // read the input pin:
  int trigstate = digitalRead(trig);
   Serial.println(trigstate);
}
