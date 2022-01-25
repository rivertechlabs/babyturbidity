#include "SD.h"
#include "SenseBoxMCU.h"

HDC1080 hdc;

void setup() {
  // power on for all ports
  senseBoxIO.powerAll();
  delay(1000);
 
  // intialize i2c bus
  Wire.begin();
 
  // initialize Sensors
  hdc.begin();
 
  // setup done
  senseBoxIO.statusGreen();
  
  SD.begin(28);
  File dataFile = SD.open("test.txt", FILE_WRITE);
  dataFile.println("tempHDC;humHDC;");
  dataFile.close();

}

void loop() {
  float temperature = hdc.getTemperature();
  float humidity = hdc.getHumidity();
  File dataFile = SD.open("test.txt", FILE_WRITE);
  dataFile.println(temperature);
  dataFile.print(";");
  dataFile.print(humidity);
  dataFile.print(";");
  dataFile.close();

}
