# Linear Timer
 A visual linear timer to use in class as a countdown for the students or any other timing needs.

## Materials

* WS2812 LEDs
* Arduino Nano, UNO or whatever it fits your needs.
* Rotary encoder
* A LCD or OLED Display

## Libraries used

  * FastLED: https://github.com/FastLED/FastLED  (Available through the Arduino Library Manager)
  * RotaryEncoder: https://github.com/FelixHauser/RotaryEncoder (forked from @Mathertel)

## What can it do?

  * Set a time using the encoder and it will start a countdown with a visual feedback: A strip of light will be shortening as time passes.

## Phases Timer

By rotating the encoder to what would be negative values, you enter a 6 phases timer where the timer will begin at phase 1 and the following phase will be triggered at the end of the previous one. Name of the phases and their assigned times are to be changed in configuration.h
