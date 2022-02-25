#include "SenseBoxMCU.h"
#include "SHTSensor.h"
 
HDC1080 hdc;
SHTSensor sht85;
 
void setup() {
  // power on for all ports
  senseBoxIO.powerAll();
  //sht85.init(); // don't need this because previous line powers on all I2C ports
  delay(1000);
 
  // intialize i2c bus
  Wire.begin();
 
  // initialize console output
  Serial.begin(9600);
 
  // initialize Sensors
  hdc.begin();
  sht85.init();
 
  // setup done
  senseBoxIO.statusGreen();
}
 
void loop() {
  // put your main code here, to run repeatedly:
  float temperature = hdc.getTemperature();
  float humidity = hdc.getHumidity();
  float temperatureSHT85;
  float humiditySHT85;
  
  if ( sht85.readSample() ) {
    temperatureSHT85 = sht85.getTemperature();
    humiditySHT85 = sht85.getHumidity();
  } else {
  // Set a value which indicates it is invalid.
    temperatureSHT85 = 0.0;
    humiditySHT85 = 0.0;
  }
  
  Serial.print("Temperatur: ");
  Serial.println(temperature);
  Serial.print("Feuchtigkeit: ");
  Serial.println(humidity);
  Serial.print("Temperatur SH: ");
  Serial.println(temperatureSHT85);
  Serial.print("Feuchtigkeit SH: ");
  Serial.println(humiditySHT85);
 
}
