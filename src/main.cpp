#include "Arduino.h"
#define LEDPIN 13
#define POT_PIN1 14
#define POT_PIN2 15

/* Pot value storage */
const int numPots = 2;
int pots[numPots] = {0, 0};
int potsOld[numPots] = {0, 0};

/* Set up pins */

void setup() {
  /* pin configuration */
  pinMode(POT_PIN1, INPUT);
  pinMode(POT_PIN2, INPUT);

  /* resolution */
  analogReadResolution(13);

  /* smooth input values */
  analogReadAveraging(16);

  /* Turn internal led on on boot */
  pinMode(LEDPIN, OUTPUT);
  digitalWrite(LEDPIN, HIGH);
}

void readPots() {
  for (int potNum = 0; potNum < numPots; ++potNum) {

    switch (potNum) {
    case 0:
      // Shift up from ADC's 13 bits to Midi 14 bit
      pots[potNum] = analogRead(POT_PIN1) << 1;

      if (pots[potNum] != potsOld[potNum]) {
        usbMIDI.sendControlChange(48, pots[potNum] & 0x7F, 1);
        usbMIDI.sendControlChange(16, (pots[potNum] >> 7) & 0x7F, 1);
      }

      break;
    case 1:
      pots[potNum] = analogRead(POT_PIN2) << 1;

      if (pots[potNum] != potsOld[potNum]) {
        usbMIDI.sendControlChange(49, pots[potNum] & 0x7F, 1);
        usbMIDI.sendControlChange(17, (pots[potNum] >> 7) & 0x7F, 1);
      }

      break;
    }
  }
}

void loop() {
  readPots();
  delay(1);
}
