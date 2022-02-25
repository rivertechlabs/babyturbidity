#include <SD.h>
#include <SenseBoxMCU.h>

HDC1080 hdc;
File dataFile;

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
  dataFile = SD.open("test.csv", FILE_WRITE);
  dataFile.println("tempHDC,humHDC");
  dataFile.close();
}

void loop() {
  dataFile = SD.open("test.csv", FILE_WRITE);
  dataFile.print(hdc.getTemperature());
  dataFile.print(",");
  dataFile.print(hdc.getHumidity());
  dataFile.println();
  dataFile.close();
}
