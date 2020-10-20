#include "Arduino.h"
#include <ResponsiveAnalogRead.h>

#define LEDPIN 13
#define POT_PIN1 14
#define POT_PIN2 15

/* Set analog resolution */
#define RESOLUTION 8192

// 14 bit midi is achieved by sending two midicc signals, one "low" combined
// with one 32 midicc's later called high
// Here we just define the lower ones
#define LOWCC1 16
#define LOWCC2 17

#define HIGHCC1 LOWCC1 + 32
#define HIGHCC2 LOWCC2 + 32

/* Pot value storage */
int pot1val = 0;
int pot2val = 0;

/* Set up read pins */
ResponsiveAnalogRead pot1(POT_PIN1, true);
ResponsiveAnalogRead pot2(POT_PIN2, true);

void setup() {
  /* resolution */
  analogReadResolution(13);

  /* smooth input values */
  analogReadAveraging(16);

  /* Set up smooth potentiometer readings */
  pot1.setAnalogResolution(RESOLUTION);

  // Enabling sleep will cause values to take less time to stop changing and
  // potentially stop changing more abruptly, where as disabling sleep will
  // cause values to ease into their correct position smoothly.
  // On by default
  /* pot1.disableSleep(); */

  // edge snap ensures that values at the edges of the spectrum (0 and 8192) can
  // be easily reached when sleep is enabled
  // On by default
  /* pot1.disableEdgeSnap(); */

  pot2.setAnalogResolution(RESOLUTION);

  /* Turn internal led on on boot */
  pinMode(LEDPIN, OUTPUT);
  digitalWrite(LEDPIN, HIGH);
}

void readPots() {
  pot1.update();

  if (pot1.hasChanged()) {
    // Shift up from ADC's 13 bits to Midi 14 bit
    pot1val = pot1.getValue() << 1;

    usbMIDI.sendControlChange(HIGHCC1, pot1val & 0x7F, 1);
    usbMIDI.sendControlChange(LOWCC1, (pot1val >> 7) & 0x7F, 1);
  }

  pot2.update();
  if (pot2.hasChanged()) {
    pot2val = pot2.getValue() << 1;

    usbMIDI.sendControlChange(HIGHCC2, pot2val & 0x7F, 1);
    usbMIDI.sendControlChange(LOWCC2, (pot2val >> 7) & 0x7F, 1);
  }
}

void loop() {
  readPots();
  delay(10);
}
