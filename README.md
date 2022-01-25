# 🍼babyturbidity

## Introduction
This repo is dedicated to the baby turbidity sensor. This sensor compromises on accuracy for low-cost. It was developed for a class on environmental sensing based on the Arduino framework.

## BOM

| Item name  | link | Quantity |
| ------------- | ------------- |------------- |
| DF robot turbidity sensor  | https://www.dfrobot.com/product-1394.html  | 2 |
| Adafruit ADS1115 16BIT  | https://www.digikey.ch/de/products/detail/adafruit-industries-llc/1085/5761229  | 2 |
| senseBox MCU | https://sensebox.de/en/products-parts.html | 1 |
| GPS receiver | https://sensebox.shop/product/gps | 1 |
| SD bee | https://sensebox.shop/product/sd-bee | 1 |
| Illumination sensor (option - this data was already provided for the students) | https://sensebox.shop/product/licht-sensor | 1 |
| Battery pack | | 1 |
| AA batteries | | 3 |

## Code
The senseBox uses the Arduino framework so the Arduino library is a good place to start with example codes for [SD card usage](https://github.com/arduino-libraries/SD). Or the Adafruit library for the [ADC](https://github.com/adafruit/Adafruit_ADS1X15). SenseBox also has example codes for each of their products. But I have also included the (very basic) code that we uploaded to this turbidity sensor.

## Hookup schematics
<img src="Calibration/calibration_figure.png" width="700">

## Contact
For questions, please email me at droujko@ifu.baug.ethz.ch or @rivertechjess on Twitter :bird:
