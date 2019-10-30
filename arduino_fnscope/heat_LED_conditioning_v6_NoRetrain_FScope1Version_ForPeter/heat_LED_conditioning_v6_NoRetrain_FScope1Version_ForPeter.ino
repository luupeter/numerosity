/*

Condition fish to associate LED light with heat (pain)

Essentially repeat of adult assay #1, but for larvae

LED control: TTL-level trigger digital signal on/off 5V
Heat control: analog modulation (level to be determined), but still binary on/off

Based on the reaction time of the fish, it looks like a reasonable time interval for the experiment might be:
  Training:
    (a) laser off, LED off for 2.5 minutes
    (b) laser on, LED off for 15 seconds
    (c) laser on, LED on for 15 seconds (since it takes ~5 seconds for the fish to respond
  (d) repeat a-c 15 times // 2:25*10~25
  wait 0 minutes
  Testing:
    (a) laser off, LED off for 2.5minutes
    (b) laser off, LED on for 30 seconds
  (c) repeat a and b 5 times 



Add habituation phase:
  Habituation before training -- same as testing
    (a) laser off, LED off for 2 minutes
    (b) laser off, LED on for 25 seconds
  (c) repeat a and b 10 times // 2:25*5~12min
wait 5 min

*/
#include <Wire.h>
#include <Adafruit_MCP4725.h>

Adafruit_MCP4725 dac;
// Change this for appropriate level when using with FScope#2:
#define laserVoltage 4095
//How to calculate laserVoltage for FScope#1: DesireCurrent/150mA/V*4095/5V

//Nose Directed Test -- 600 mA, corresponds to 2457 laserVoltage

#define ITI 2 // minutes between test/trainings
#define pausing 0 // minutes between phases
#define CSLen 8 // seconds for conditioned stimulus (LED)
#define USLen 2 // seconds for unconditioned stimulus (heating laser)
#define waitLen 28 // minutes for wait period

int LED = 4; // standard pin for LEDs
int OUT2 = 5; // digital pin 2
int OUT3 = 6; // digital pin to drive 2nd IR level independently from LED

void setup() {
  Serial.begin(9600);

    display_Running_Sketch();

  dac.begin(0x62);
  pinMode (LED, OUTPUT);
  digitalWrite (LED, LOW);
  pinMode (OUT2, OUTPUT);
  digitalWrite (OUT2, LOW);
    pinMode (OUT3, OUTPUT);
  digitalWrite (OUT3, LOW);
  dac.setVoltage(0, false);

  //training(1); // REMOVE THAT LINE
  
  Serial.println("["+String(millis()/1000) + "] This is FScope One (1) main behavioral Arduino. Waiting 1 minute. Turn video recording ON now.");
//AUSTIN
waitMinute(1);
}
//MEMORY RETENTION
void loop() {
  
  testing("Habituation",20); // habituation
  //waitMinute(pausing);
  training(10);  // Training block 1
  
  waitMinute(waitLen); // Training block 2
  training(10);
  
  waitMinute(waitLen);
  testing("Testing1",5); // testing
  
  training(10) ; // retraining
  //finish
  Serial.println("["+String(millis()/1000) + "] Sweet dreams...");
  while(1){}
  
}

void testing(String msg, int rep_num){
  for(int rep=0;rep<rep_num;rep++){
    Serial.println("["+String(millis()/1000) + "] "+msg+" rep #" + String(rep) + "/" + String(rep_num));
    digitalWrite(LED, HIGH);
    digitalWrite(OUT3, HIGH);
    waitSecond(CSLen+USLen);
    digitalWrite(LED, LOW);
    digitalWrite(OUT3, LOW);

    waitMinute(ITI);        

  }
}



void training(int rep_num){
  for(int rep=0;rep<rep_num;rep++){
    Serial.println("["+String(millis()/1000) + "] Training rep #" + String(rep) + "/" + String(rep_num));

    digitalWrite(LED, HIGH);
    digitalWrite(OUT3, HIGH);
    waitSecond(CSLen);
    digitalWrite(OUT2, HIGH);
    dac.setVoltage(laserVoltage, false);

    waitSecond(USLen);
    
    digitalWrite(LED, LOW);
    digitalWrite(OUT3, LOW);
    dac.setVoltage(0, false);
    digitalWrite(OUT2, LOW);

    waitMinute(ITI);        

  }
  
}

void waitMinute(int mins){
  for(int i=0;i<mins;i++){
    Serial.println("["+String(millis()/1000) + "] waitMinute "+ String(i)+"/"+String(mins));
    waitSecond(60);
  }
}

void waitSecond(int secs){
  for(int j=0;j<secs;j++){
    delay(1000);
  }
}


// displays at startup the Sketch running in the Arduino
// source: https://forum.arduino.cc/index.php?topic=118605.0
void display_Running_Sketch (void){
  String the_path = __FILE__;
  int slash_loc = the_path.lastIndexOf('/');
  String the_cpp_name = the_path.substring(slash_loc+1);
  int dot_loc = the_cpp_name.lastIndexOf('.');
  String the_sketchname = the_cpp_name.substring(0, dot_loc);

  Serial.print("\nArduino is running Sketch: ");
  Serial.println(the_sketchname);
  Serial.print("Compiled on: ");
  Serial.print(__DATE__);
  Serial.print(" at ");
  Serial.print(__TIME__);
  Serial.print("\n");
}
