/*

Code for running multi level IR illumination system
  Input: TTL on D5 and D4
  Output: analog signal from DAC as function D5/D4 combination

  Version one:
    DAC outputs two levels of voltage, based on presence of input on D4 (INP1)
    This allows wiring main FScope arduino and IR LED

*/

#include <Wire.h>
#include <Adafruit_MCP4725.h>

Adafruit_MCP4725 dac;
int INP1 = 4; // D4 input
int INP2 = 5; // D5 input

// FScope #1 settings -- comment if uploading for FScope#2
// 0-110-170-240 on camera with 20ms Exposure, bin 1x 
int dac_very_high = 148; // brightness level of IR LED at D5 HIGH input
int dac_high = 120; // brightness level of IR LED at HIGH input, ~66% of dynamic range
int dac_low  = 95; // brightness level of IR LED at LOW input, ~50% of dynamic range

// FScope #2 settings -- comment if uploading for FScope#1
//<<<<<<< .mine
//int dac_very_high = 170; // brightness level of IR LED at D5 HIGH input
//int dac_high = 120; // brightness level of IR LED at HIGH input, ~66% of dynamic range
//int dac_low  = 70; // brightness level of IR LED at LOW input, ~50% of dynamic range
//||||||| .r50
//int dac_very_high = 250; // brightness level of IR LED at D5 HIGH input
//int dac_high = 200; // brightness level of IR LED at HIGH input, ~66% of dynamic range
//int dac_low  = 150; // brightness level of IR LED at LOW input, ~50% of dynamic range
//=======
//// 0-100-16-240 counts on camera with 20ms exposure, 20ms interval, bin 1x
//int dac_very_high = 670; // brightness level of IR LED at D5 HIGH input
//int dac_high = 510; // brightness level of IR LED at HIGH input, ~66% of dynamic range
//int dac_low  = 350; // brightness level of IR LED at LOW input, ~50% of dynamic range
//>>>>>>> .r60

void setup() {

  Serial.begin(9600);
  Serial.println("["+String(millis()/1000) + "] Booting up...");

  dac.begin(0x62);
  pinMode (INP1, INPUT);
  pinMode (INP2, INPUT);

  dac.setVoltage(dac_very_high, false);
  delay(2000);
  dac.setVoltage(dac_high, false);
  delay(2000);
  dac.setVoltage(dac_low, false);
  delay(2000);
  dac.setVoltage(0, false);
  delay(2000);

  Serial.println("["+String(millis()/1000) + "] Starting loop: D4 triggers DAC to go from " + String(dac_low) +" to "+String(dac_high) + " to " + String(dac_very_high));
  Serial.println("THIS IS MultiLEVEL Arduino, NOT THE RIGHT ONE FOR TR01 EXPERIMENTS");
}


void loop() {


  if(digitalRead(INP1)==HIGH){
    if(digitalRead(INP2)==HIGH){
      dac.setVoltage(dac_very_high, false);
      Serial.println("Set VERY HIGH");
    }else{
      dac.setVoltage(dac_high, false);
      Serial.println("Set HIGH");
    }
  }else{
    dac.setVoltage(dac_low, false);
      Serial.println("Set LOW");
  }

}
