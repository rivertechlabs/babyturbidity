#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "SenseBoxMCU.h"
#include "SHTSensor.h"
#include "SD.h"
#include "wlanCommunicator.h"
#include "SparkFun_SCD30_Arduino_Library.h"

Adafruit_SSD1306 display(4);

// generate objects
HDC1080 hdc;
SHTSensor sht85;
SCD30 scd30;

VEML6070 vml;
TSL45315 lux_sensor;
/*
   getUVI()
   erwartet den Messert des UV-Sensors als Eingabeparameter
   und gibt den entsprechenden Wert auf dem UV-Index zurück
*/
float getUVI(int uv) {
  float refVal = 0.4; // Referenzwert: 0,01 W/m^2 ist äquivalent zu 0.4 als UV-Index
  float uvi = refVal * (uv * 5.625) / 1000;
  return uvi;
}

WLANCommunicator communicator;


// variables to summ up the values (aggregate Data)
double sumTemperature;
double sumHumidity;
double sumTemperatureSHT85;
double sumHumiditySHT85;
double sumTemperatureSCD30;
double sumHumiditySCD30;
double sumCo2_SCD30;
double sumLux;
double sumUV;
double sumUVI;
unsigned int count;
unsigned long now;
unsigned long nextSendAfter;

void setup() {
  // power on for all Ports
  senseBoxIO.powerAll();
  delay(1000);

  // intialize i2c bus
  Wire.begin();
  
  // initialize console output
  Serial.begin(9600);

  // initialize OLED-Display
  display.begin(SSD1306_SWITCHCAPVCC, 0x3D);
  display.display();
  delay(100);
  display.clearDisplay();

  // initialize SD card
  SD.begin(28);
  File dataFileRaw = SD.open("dataRaw.txt", FILE_WRITE);
  // header for File
  dataFileRaw.println("timeSinceStart;timeWiFi;timeWiFiraw;tempHDC;humHDC;tempSHT85;humSHT85;tempSCD30;humSCD30;co2;lux;uv;uvi");
  dataFileRaw.close();
  File dataFileAgg = SD.open("dataAgg.txt", FILE_WRITE);
  // header for File
  dataFileAgg.println("timeSinceStart;timeWiFi;timeWiFiraw;tempHDC;humHDC;tempSHT85;humSHT85;tempSCD30;humSCD30;co2;lux;uv;uvi");
  dataFileAgg.close();

  // initialize Sensors
  hdc.begin();  // sensebox temperature and humidity (HDC)
  sht85.init(); // sensirion temperature and humidity (SHT85)
  scd30.begin(); // sensirion CO2 sensor (SCD30)
  lux_sensor.begin(); // sensebox lux (TSL45315)
  vml.begin(); // sensebox uv (VEML6070)

  // set wifi settings (pre-configured for SSID IoT at ETH)
  // (if executed once, it will not be able to connect to SSID IoT anymore!
  // ->ask Luzia to configure WiFi-Bee again)
  //communicator.setWiFiParameters("SSID", "pwd");

  delay(5000); // for wifi to correctly connect

  nextSendAfter = millis() + 60e3;

  // setup done
  senseBoxIO.statusGreen();
}

void loop() {
  // run repeatedly:

  // read sensor HDC
  float temperature = hdc.getTemperature();
  float humidity = hdc.getHumidity();

  // read sensor SHT85
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

  // If a value for ambient pressure is available, it can be set on the scd30 to improve accuracy
  // In this case uncomment the following line
  // scd30.setAmbientPressure(pressure / 100);
  while (!scd30.dataAvailable()) ;
  float temperatureSCD30 = scd30.getTemperature();
  uint16_t co2_SCD30 = scd30.getCO2();
  float humiditySCD30 = scd30.getHumidity();

  float lux = lux_sensor.getIlluminance();
  float uv  = vml.getUvIntensity();
  float uvi = getUVI(uv);

  // add timestamp since start
  unsigned long timeSinceStart = millis();
  // get internet WiFi time (Unix Time Format)
  unsigned long timeWiFiraw = communicator.getRawInternetTime();
  // get formatet WiFi time
  const char* timeWiFi = communicator.getFormatedInternetTime();

  // display measured values on serial monitor
  Serial.println(timeWiFi);
  Serial.println("temperature HDC/SHT85/SCD30 "); Serial.print(temperature); Serial.print(" / "); Serial.print(temperatureSHT85); Serial.print(" / "); Serial.println(temperatureSCD30);
  Serial.println("humidity HDC/SHT85/SCD30 "); Serial.print(humidity); Serial.print(" / "); Serial.print(humiditySHT85); Serial.print(" / "); Serial.println(humiditySCD30);
  Serial.println("CO2 SCD30 "); Serial.println(co2_SCD30);
  Serial.println("lux/uv/uvi "); Serial.print(lux); Serial.print(" / "); Serial.print(uv); Serial.print(" / "); Serial.println(uvi);
  Serial.println("");
  
  // display measured values
  display.setCursor(0, 0); // start position upper left
  display.setTextSize(1); // smallest textsize
  display.setTextColor(WHITE, BLACK);
  display.println(timeWiFi);
  display.println("temp HDC/SHT85/SCD30 "); display.print(temperature); display.print(" / "); display.print(temperatureSHT85); display.print(" / "); display.println(temperatureSCD30);
  display.println("hum HDC/SHT85/SCD30 "); display.print(humidity); display.print(" / "); display.print(humiditySHT85); display.print(" / "); display.println(humiditySCD30);
  display.print("CO2 SCD30 "); display.println(co2_SCD30);
  display.println("lux/uv/uvi "); display.print(lux); display.print(" / "); display.print(uv); display.print(" / "); display.println(uvi);
  display.display();

  // display measured values on serial
  Serial.println(timeWiFi);
  Serial.println("temp HDC/SHT85/SCD30 "); Serial.print(temperature); Serial.print(" / "); Serial.print(temperatureSHT85); Serial.print(" / "); Serial.println(temperatureSCD30);
  Serial.println("hum HDC/SHT85/SCD30 "); Serial.print(humidity); Serial.print(" / "); Serial.print(humiditySHT85); Serial.print(" / "); Serial.println(humiditySCD30);
  Serial.print("CO2 SCD30 "); Serial.println(co2_SCD30);
  Serial.println("lux/uv/uvi "); Serial.print(lux); Serial.print(" / "); Serial.print(uv); Serial.print(" / "); Serial.println(uvi);
  

  // write SD card
  File dataFileRaw = SD.open("dataRaw.txt", FILE_WRITE);
  dataFileRaw.print(timeSinceStart);
  dataFileRaw.print(";");
  dataFileRaw.print(timeWiFi);
  dataFileRaw.print(";");
  dataFileRaw.print(timeWiFiraw);
  dataFileRaw.print(";");
  dataFileRaw.print(temperature);
  dataFileRaw.print(";");
  dataFileRaw.print(humidity);
  dataFileRaw.print(";");
  dataFileRaw.print(temperatureSHT85);
  dataFileRaw.print(";");
  dataFileRaw.print(humiditySHT85);
  dataFileRaw.print(";");
  dataFileRaw.print(temperatureSCD30);
  dataFileRaw.print(";");
  dataFileRaw.print(humiditySCD30);
  dataFileRaw.print(";");
  dataFileRaw.print(co2_SCD30);
  dataFileRaw.print(";");
  dataFileRaw.print(lux);
  dataFileRaw.print(";");
  dataFileRaw.print(uv);
  dataFileRaw.print(";");
  dataFileRaw.print(uvi);
  dataFileRaw.println();
  dataFileRaw.close();

  count++; // Counter increases with every loop by 1
  // Add up raw data to calculate the mean value later on
  sumTemperature += temperature;
  sumHumidity  += humidity;
  sumTemperatureSHT85 += temperatureSHT85;
  sumHumiditySHT85  += humiditySHT85;
  sumTemperatureSCD30 += temperatureSCD30;
  sumHumiditySCD30  += humiditySCD30;
  sumCo2_SCD30  += co2_SCD30;
  sumLux += lux;
  sumUV += uv;
  sumUVI += uvi;

  now = millis();
  // This section will be executed every minute
  if (now > nextSendAfter) {
    nextSendAfter = now + 60e3;

    // calculate mean value of last minute
    double meanTemperature = sumTemperature / count;
    double meanHumidity = sumHumidity / count;
    double meanTemperatureSHT85 = sumTemperatureSHT85 / count;
    double meanHumiditySHT85 = sumHumiditySHT85 / count;
    double meanTemperatureSCD30 = sumTemperatureSCD30 / count;
    double meanHumiditySCD30 = sumHumiditySCD30 / count;
    double meanCo2_SCD30 = sumCo2_SCD30 / count;
    double meanLux = sumLux / count;
    double meanUV = sumUV / count;
    double meanUVI = sumUVI / count;

    // reset for next minute
    count = 0;
    sumTemperature = 0;
    sumHumidity = 0;
    sumTemperatureSHT85 = 0;
    sumHumiditySHT85 = 0;
    sumTemperatureSCD30 = 0;
    sumHumiditySCD30 = 0;
    sumCo2_SCD30 = 0;
    sumLux = 0;
    sumUV = 0;
    sumUVI = 0;

    // Send mean data to openSenseMap
    /*
      communicator.addMeasurement("SENSOR_ID", meanTemperature);
      communicator.addMeasurement("SENSOR_ID", meanHumidity);
      communicator.addMeasurement("SENSOR_ID", meanTemperatureSHT85);
      communicator.addMeasurement("SENSOR_ID", meanHumiditySHT85);

      communicator.submitValues("SENSE_BOX_ID");
    */
    // Write mean data to a second file on SD Card
    // write SD card
    File dataFileAgg = SD.open("dataAgg.txt", FILE_WRITE);
    dataFileAgg.print(timeSinceStart);
    dataFileAgg.print(";");
    dataFileAgg.print(timeWiFi);
    dataFileAgg.print(";");
    dataFileAgg.print(timeWiFiraw);
    dataFileAgg.print(";");
    dataFileAgg.print(meanTemperature);
    dataFileAgg.print(";");
    dataFileAgg.print(meanHumidity);
    dataFileAgg.print(";");
    dataFileAgg.print(meanTemperatureSHT85);
    dataFileAgg.print(";");
    dataFileAgg.print(meanHumiditySHT85);
    dataFileAgg.print(";");
    dataFileAgg.print(meanTemperatureSCD30);
    dataFileAgg.print(";");
    dataFileAgg.print(meanHumiditySCD30);
    dataFileAgg.print(";");
    dataFileAgg.print(meanCo2_SCD30);
    dataFileAgg.print(";");
    dataFileAgg.print(meanLux);
    dataFileAgg.print(";");
    dataFileAgg.print(meanUV);
    dataFileAgg.print(";");
    dataFileAgg.print(meanUVI);
    dataFileAgg.println();
    dataFileAgg.close();
  }

  // sleep for 1 second
  delay(1000);

}
