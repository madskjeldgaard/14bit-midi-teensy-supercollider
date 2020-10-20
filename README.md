This is a simple example of a Teensy 3.2 midi-usb controller sending out 14 bit midi data to a host computer. In the example I use two potentiometers. The midi data is then received by SuperCollider and handled from there.

## The microcontroller

This project is set up using Platformio for a Teensy 3.2 but can easily be modified for other controllers.

Smoothing of the analog signals is handled on the software side using the [ResponsiveAnalogRead](https://github.com/dxinteractive/ResponsiveAnalogRead) library.

The microcontroller itself receives only 13 bits of analog data via it's ADC which is shifted up to fill the entire 14 bit spectrum.

## Receiving 14 bit midi using SuperCollider
You can use 14 bit midi in the [Modality Toolkit Quark](https://github.com/ModalityTeam/Modality-toolkit) even though it isn't as of now documented.

A simpler and very good solution is using [this custom class (FourteenBitCC)](https://gist.github.com/carltesta/bb5065a7b92bab7673237e9cc1c9a612)
