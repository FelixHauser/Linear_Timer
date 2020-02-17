// WS2812B Strip timer. 
// Maker: Felix Hauser  https://github.com/FelixHauser
// Open Source Project: Copy, distribute but document and attribute credit.

//++++++++++++++++ Define PINS +++++++++++++++++//

#define ENCODER_CW 6  //pin1
#define ENCODER_CCW 5 //pin2
#define ROTARY_BUTTON 8  //pin button

#define BUZZER_PIN 9


//++++++++++++++++ Important customizable settings +++++++++++++++++//

#define NUM_LEDS 37  //size of the LED strip
#define BRIGHTNESS 25

#define ROTARYMAX 60  //Maximum time
#define ROTARYSTEPS 1 //minutes per rotary step

#define ROWS 2
#define COLUMNS 16
#define TIME_CURSOR 6  //where the cursor starts to write after the title (Zeit :")

//++++++++++++++++ Include needed libraries +++++++++++++++++//

#include <FastLED.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <RotaryEncoder.h>


//++++++++++++++++ Define Rotary Encoder Stuff +++++++++++++++++//

#define ROTARYMIN -1 //0
#define START_POSITION 0


#define DEBOUNCE_INTERVAl 10  //debounce interval




//++++++++++++++++ Define LED Strip Stuff +++++++++++++++++//

#define DATA_PIN 12
#define LED_TYPE WS2812B
#define COLOR_ORDER GRB


#define LIGHT_UP_SPEED 25



//++++++++++++++++ Define Countdown Stuff +++++++++++++++++//

#define COUNTDOWN_UPDATE 1*1000



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


//++++++++++++++++ SegeL +++++++++++++++++//

#define PHASES_TIMER " Compact"

#define PHASE1 "     Phase 1    "
#define PHASE2 "     Phase 2    "
#define PHASE3 "     Phase 3    "
#define PHASE4 "     Phase 4    "
#define PHASE5 "     Phase 5    "
#define PHASE6 "     Phase 6    "

#define TIME_PHASE1 5
#define TIME_PHASE2 15
#define TIME_PHASE3 30
#define TIME_PHASE4 5
#define TIME_PHASE5 5
