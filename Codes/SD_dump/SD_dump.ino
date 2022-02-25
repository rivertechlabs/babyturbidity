#include <SD.h>

File dataFile;

void setup() {
  // Serial
  Serial.begin(9600);

  // SD
  SD.begin(28);

  String buffer;
  buffer.reserve(dataFile.size());
  dataFile = SD.open("test.csv", FILE_READ);
  dataFile.read(buffer, dataFile.size()-1);
  Serial.println(buffer);
  dataFile.close();
}

void loop() {
}
