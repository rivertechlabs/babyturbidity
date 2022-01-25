#include "SPI.h"
#include "Wire.h"
#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"
#include "SenseBoxMCU.h"

Adafruit_SSD1306 display(4);
HDC1080 hdc;

void setup() {
   // power on for all ports
  senseBoxIO.powerAll();
  // senseBoxIO.powerI2C(true);  // only if I2C has not yet power (included in powerAll)
  // delay(1000);                // only if not already done after powerI2C or powerAll
  display.begin(SSD1306_SWITCHCAPVCC, 0x3D);
  display.display();
  delay(100);
  display.clearDisplay();

   // intialize i2c bus
  Wire.begin();

   // initialize Sensors
  hdc.begin();
 
  // setup done
  senseBoxIO.statusGreen();

}

void loop() {
  float temperature = hdc.getTemperature();
  float humidity = hdc.getHumidity();
 
  display.setCursor(0,0); // Startposition links oben
  display.setTextSize(1); // Kleinste Schriftgrösse
  display.setTextColor(WHITE,BLACK);
  display.print("t: "); display.println(temperature);
  display.print("h: "); display.println(humidity);
  display.display();

}
