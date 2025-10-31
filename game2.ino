unsigned long newMillis = 0, oldMillis = 0; // variables to store timing
unsigned long interval = 700;     // speed of game
int Button = 2;                   // pin number for the button
int Buzzer = 6;                   // pin number for the buzzer
bool running = true;              // variable to store status of the game
int x = 0;                        // starting poistion of the LED bar on the matrix

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

uint8_t skull[8][12] = {            // a skull image for the loser screen
  {0,0,0,1,1,1,1,1,0,0,0,0},
  {0,0,1,1,1,1,1,1,1,0,0,0},
  {0,1,1,1,1,1,1,1,1,1,0,0},
  {0,1,1,1,0,1,1,0,1,1,0,0},
  {0,1,1,1,0,1,1,0,1,1,0,0},
  {0,0,1,1,1,0,1,1,1,0,0,0},
  {0,0,0,1,1,1,1,1,0,0,0,0},
  {0,0,0,1,0,1,0,1,0,0,0,0}
};


// function to update a column of the blank frame
void draw_column(int offset, int onoff){
  for (int y = 0+offset; y<=7-offset; y++){        // set LEDs in column x to be on or off
    blank[y][x] = onoff;
  } 
}

void setup() {
  Serial.begin(115200);           // Initialize serial communication at a baud rate of 115200
  matrix.begin();                 // Initialize the LED matrix
  pinMode(Buzzer, OUTPUT);
  pinMode(Button, INPUT_PULLUP);
}

void loop() {
    if (digitalRead(Button) == 0){ // if the button is pressed...
    running = false;
    if (x == 5){                      // if the right line was lit...      
      tone(Buzzer, 2000, 500);          // make a happy noise
      matrix.loadFrame(happy);          // show a happy face
      delay(700);
      matrix.clear();                   // clear the matrix
      interval = (interval * 0.85);     // speed things up
      running = true;
    } else {                          // if not...
      matrix.renderBitmap(skull,8,12);  // loser image
      tone(Buzzer, 200, 700);           // sad noises
      delay(700);
      tone(Buzzer, 100, 1000);
      
    }
  }

  newMillis = millis(); // the number of seconds since the board started running this program

  // if the program been running for longer than the interval...
  if (newMillis - oldMillis >= interval && running == true){ 
    oldMillis = newMillis;              // reset oldMillis value
    draw_column(0,0);                   // clear column x
    matrix.renderBitmap(blank,8,12);    // load the frame onto LED matrix

    switch (x) {
      case 11:
        x = 0;
        draw_column(1,1);
        break;
      case 4:
        x++;
        draw_column(0,1);
        break;
      default:
        x++;
        draw_column(1,1);
        break;
    }
    matrix.renderBitmap(blank,8,12);  // load the frame onto LED matrix
    tone(Buzzer, 1000, 50);           // friendly beep

  }
}
