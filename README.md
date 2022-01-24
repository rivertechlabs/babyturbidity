# 🍼babyturbidity

## Introduction
This repo is dedicated to the baby turbidity sensor. This sensor compromises on accuracy for low-cost. It was developed for a class on environmental sensing based on the Arduino framework.

## BOM

| Item name  | link | Quantity |
| ------------- | ------------- |------------- |
| DF robot turbidity sensor  | https://www.dfrobot.com/product-1394.html  | 2 |
| Adafruit ADS1115 16BIT  | https://www.digikey.ch/de/products/detail/adafruit-industries-llc/1085/5761229  | 2|



This repo contains several items to build the current prototype of the open-source turbidity sensor including:
- The code needed to upload to the ESP32
- CAD files
- Hookup schematics

## Code
Before you begin, you need the ESP-IDF installed on your computer. Please visit the [Espressif website](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/) for more information on installation.

The current code takes 100 frequency measurements and enters deep-sleep for 1min, this can of course be changed. Also, the code isn't beautiful and I apologize but it will get better with time.

## Hookup schematics
<img src="Images/schematic.png" width="700">

## Contact
For questions, please email me at droujko@ifu.baug.ethz.ch or @rivertechjess on Twitter :bird:

-----------------------------------------
## Prototype 1.0
This repo also contains the CAD files for prototype 1.0 of the turbidity sensor (you can use this to 3D print the device in a school project)
