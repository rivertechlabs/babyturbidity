import grafica.*;

import processing.serial.*;

Serial arduino; // arduino serial port

void setup()
{
  size(500, 350);
  background(150);
  
  arduino = new Serial(this, Serial.list()[0], 9600);
  arduino.bufferUntil('\n');
  
  GPointsArray points = new GPointsArray();
  
  while (arduino.available() > 0)
  {
    String tempHDC = arduino.readStringUntil(',');
    String humHDC = arduino.readStringUntil('\n');
    points.add(float(tempHDC), float(humHDC));
  }
  
  printArray(points);
  
  // Create a new plot and set its position on the screen
  GPlot plot = new GPlot(this, 25, 25);

  // Set the plot title and the axis labels
  plot.setTitleText("SD Diagramm");
  plot.getXAxis().setAxisLabelText("HDC Temperatur");
  plot.getYAxis().setAxisLabelText("HDC Feuchtigkeit");

  // Add the points
  plot.setPoints(points);

  // Draw it!
  plot.defaultDraw();
}
