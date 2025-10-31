int Buzzer = 6;                   // pin number for the buzzer
int Button = 2;                   // pin number for the button

#include "Arduino_LED_Matrix.h"   // Include the LED_Matrix library
#include "frames.h"               // Include a header file containing some custom icons

ArduinoLEDMatrix matrix;          // Create an instance of the ArduinoLEDMatrix class

uint8_t blank[8][12] = {
  {0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0}
};

uint8_t codeclub[8][12] = {
  {0,0,1,1,1,0,0,0,0,1,1,1},
  {0,1,0,0,0,0,0,0,1,0,0,0},
  {1,0,0,0,0,0,0,1,0,0,0,0},
  {1,0,0,0,0,0,0,1,0,0,0,0},
  {1,0,0,0,0,0,0,1,0,0,0,0},
  {1,0,0,0,0,0,0,1,0,0,0,0},
  {0,1,0,0,0,0,0,0,1,0,0,0},
  {0,0,1,1,1,0,0,0,0,1,1,1}
};
void setup() {
  Serial.begin(115200);           // Initialize serial communication at a baud rate of 115200
  matrix.begin();                 // Initialize the LED matrix
  pinMode(Buzzer, OUTPUT);        // Initialise the Buzzer
  pinMode(Button, INPUT_PULLUP);  // Initialise the Button
}

void loop() {
  if (digitalRead(Button) == 0){
    
    tone(Buzzer, 2000, 500);
    delay(500);
    tone(Buzzer, 1000, 500);
    matrix.renderBitmap(codeclub, 8 , 12);
    delay(500);
    // Turn off the display
    matrix.clear();
    delay(1000);
  }

  // Print the current value of millis() to the serial monitor
  Serial.println(millis());
}
