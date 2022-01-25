// !!!! Please know that this code doesn't give you turbidity,
// it doesn't save values to an SD card, and it doesn't display
// anything to an LCD screen. To use those features (SD, LCD)
// you need to merge this code with the other codes provided in the
// course. In order to read turbidity, we will have to calibrate
// our turbidity sensors (that will be next week) ;) 
// For now, just try to get this code to work (it should output 
// some number between 0 and 2048

#include <Wire.h>
#include <Adafruit_ADS1015.h>
// !!!!!!!!you might need some more libraries to get this code to work
// with the sensebox (please just check the other example codes from 
// the course. I think maybe you need:
//#include <SPI.h>
//#include "SenseBoxMCU.h"

// construct an instance of an ADS1015 with the default address (0x48)
// this address is selected when you connect the GND pin to the 
Adafruit_ADS1015 ads;

void setup(void) {
  
    // power on for all Ports
  senseBoxIO.powerAll();
  delay(1000);

  // intialize i2c bus
  Wire.begin();
  
  // initialize console output
  Serial.begin(9600);
  Serial.println("Hello!");
  
  Serial.println("Getting single-ended readings from A0");
  Serial.println("ADC Range: +/- 4.096V (1 bit = 3mV/ADS1015)");

  // initialize the ADS
  ads.begin();
}

void loop(void) {
  int16_t adc0;
  
  adc0 = ads.readADC_SingleEnded(0);
  Serial.print("A0: "); Serial.println(adc0);
  Serial.println();
  
  delay(1000);
}
