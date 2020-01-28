// WS2812B Strip timer. 
// Maker: Felix Hauser  https://github.com/FelixHauser
// Open Source Project: Copy, distribute but document and attribute credit.


//++++++++++++++++ Important customizable settings +++++++++++++++++//

#define NUM_LEDS 37  //size of the LED strip
#define BRIGHTNESS 25

#define ROTARYMAX 60  //Maximum time
#define ROTARYSTEPS 1 //minutes per rotary step

#define ROWS 2
#define COLUMNS 16
#define TIME_CURSOR 7  //where the cursor starts to write on the 2nd line

//++++++++++++++++ Include needed libraries +++++++++++++++++//

#include <FastLED.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <RotaryEncoder.h>


//++++++++++++++++ Define LCD Stuff +++++++++++++++++//

const int  en = 2, rw = 1, rs = 0, d4 = 4, d5 = 5, d6 = 6, d7 = 7, bl = 3;  // pinout
const int i2c_addr = 0x27;    //I2C Address - change if reqiuired



//++++++++++++++++ Define Rotary Encoder Stuff +++++++++++++++++//

#define ROTARYMIN 0
#define START_POSITION 0

#define ENCODER_CW 6  //pin1
#define ENCODER_CCW 5 //pin2

#define ROTARY_BUTTON 8  //pin button
#define DEBOUNCE_INTERVAl 10  //debounce interval



//++++++++++++++++ Define LED Strip Stuff +++++++++++++++++//

#define DATA_PIN 2  
#define LED_TYPE WS2812B
#define COLOR_ORDER GRB


#define LIGHT_UP_SPEED 25

CRGB leds[NUM_LEDS]; 


//++++++++++++++++ Define Countdown Stuff +++++++++++++++++//

#define COUNTDOWN_UPDATE 10*1000



//++++++++++++++++ Set Some Colors +++++++++++++++++//

#define RED 0xFF0000
#define GREEN 0x008000
#define BLUE 0x0000FF
#define BLACK 0x000000

#define YELLOW 0xFFFF00
#define LIGHT_BLUE 0xADD8E6
#define GREEN_YELLOW 0xADFF2F
#define VIOLET 0xEE82EE
#define PINK 0xFFC0CB