#include <SenseBoxMCU.h>
#include <SHTSensor.h>

HDC1080 hdc;
SHTSensor sht85;

void setup() {
  // power on for all ports
  senseBoxIO.powerAll();

  delay(1000);

  // intialize i2c bus
  Wire.begin();

  // initialize console output
  Serial.begin(9600);

  // initialize Sensors
  hdc.begin();
  sht85.init();

  // optimize SHT Sensor for fastest measurements
  sht85.setAccuracy(SHT_ACCURACY_LOW);

  // setup done
  senseBoxIO.statusGreen();
}

void loop() {
  Serial.print("Temperatur: ");
  Serial.println(hdc.getTemperature());
  Serial.print("Feuchtigkeit: ");
  Serial.println(hdc.getHumidity());
  // TODO this should be done with an interruption instead
  while ( !sht85.readSample() ) {} // wait for measurements
  // sht85 received measurements
  Serial.print("Temperatur SH: ");
  Serial.println(sht85.getTemperature());
  Serial.print("Feuchtigkeit SH: ");
  Serial.println(sht85.getHumidity());

  delay(1000);
}
