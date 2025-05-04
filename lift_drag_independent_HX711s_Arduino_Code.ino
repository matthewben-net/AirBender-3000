#include "HX711.h"

HX711 scale_drag;
HX711 scale_lift;

// Define pins for each HX711
uint8_t dataPin_drag = 6;
uint8_t clockPin_drag = 7;

uint8_t dataPin_lift = 2;
uint8_t clockPin_lift = 3;

float drag;
float lift;


void setup()
{
  Serial.begin(115200);

  scale_drag.begin(dataPin_drag, clockPin_drag);
  scale_lift.begin(dataPin_lift, clockPin_lift);

  // Set calibration for drag load cell
  scale_drag.set_offset(792489);
  scale_drag.set_scale(389.399719);  
  
  scale_lift.set_offset(114174);
  scale_lift.set_scale(406.546539);

  //  reset the scales to zero = 0
  scale_drag.tare();
  scale_lift.tare();
}


void loop()
{
  // Read the values
  drag = scale_drag.get_units(5);  // average 5 readings
  lift = scale_lift.get_units(5);

  // Output to serial
  Serial.print("Load Cell 1: ");
  Serial.print(drag);
  Serial.print("\t");

  Serial.print("Load Cell 2: ");
  Serial.println(lift);

  delay(250);
}
