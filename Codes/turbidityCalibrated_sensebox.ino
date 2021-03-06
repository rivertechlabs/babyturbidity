// !!!! Please know that this code doesn't give you turbidity,
// it doesn't save values to an SD card, and it doesn't display
// anything to an LCD screen. To use those features (SD, LCD)
// you need to merge this code with the other codes provided in the
// course.
  
#include <Wire.h>
#include <Adafruit_ADS1015.h>

// construct an instance of an ADS1015 with the default address (0x48)
Adafruit_ADS1015 ads;

void setup(void) {
  Serial.begin(9600);
  Serial.println("Hello!");
  
  Serial.println("Getting single-ended readings from A0");
  Serial.println("ADC Range: +/- 4.096V (1 bit = 3mV/ADS1015)");

  ads.begin();
}

void loop(void) {
  int16_t adc0;
  
  adc0 = ads.readADC_SingleEnded(0);
  Serial.print("A0: "); Serial.println(adc0);

  // The following equation needs to be changed to YOUR NTU=f(bit) equation
  // found from your own calibration. Follow the calibration methodology
  // in the calibration.pdf document.
  float ntu = -1120.4*square(adc0)+5742.3*adc0-4352.9;

  Serial.print ("Sensor Output (V):");Serial.println (voltage);
  Serial.print ("Turbidity (NTU):");Serial.println (ntu);
  Serial.println();
  
  delay(1000);
}
