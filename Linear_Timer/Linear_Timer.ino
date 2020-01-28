// WS2812B Strip timer. 
// Maker: Felix Hauser  https://github.com/FelixHauser
// Open Source Project: Copy, distribute but document and attribute credit.

#include "Configuration.h"



unsigned long previousMillis;
unsigned long currentMillis;
bool countDown=false;
unsigned long timerLength;
unsigned long timerUpdated;
unsigned long countDownenMs;

RotaryEncoder encoder(ENCODER_CW, ENCODER_CCW, ROTARY_BUTTON, DEBOUNCE_INTERVAl); //declare encoder object

LiquidCrystal_I2C lcd(i2c_addr, en, rw, rs, d4, d5, d6, d7, bl, POSITIVE);  //declare LCD object

void setup(){
  
  Serial.begin(115200);
    
  FastLED.addLeds<LED_TYPE, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(  BRIGHTNESS );
  
  encoder.setPosition(START_POSITION / ROTARYSTEPS);

  // Set LCD type as 16 char, 2 rows
  lcd.begin(COLUMNS,ROWS);
  lcd.clear();
  lcd.setCursor(4,0);
  lcd.print("Minuten:");
  lcd.setCursor(TIME_CURSOR,1);
  lcd.print(" 0");
  delay(100);
} 


void loop() {

  
  encoder.tick();

  // get the current physical position and calc the logical position
  int newPos = encoder.getPosition() * ROTARYSTEPS;

  if (newPos < ROTARYMIN) {
    encoder.setPosition(ROTARYMIN / ROTARYSTEPS);
    newPos = ROTARYMIN;
    
    
  } else if (newPos > ROTARYMAX) {
    encoder.setPosition(ROTARYMAX / ROTARYSTEPS);
    newPos = ROTARYMAX;
    
  } 

  updateScreen(newPos);

  if (encoder.update() && encoder.read()==LOW) encoderPressed(newPos);
    
  if (countDown==true) timerDown();
  
}




void updateScreen(int printPosition){

  lcd.setCursor(TIME_CURSOR,1);
  lcd.print(timeString(printPosition));
  
  }




void doSomenthingWithLeds(int fromLed, int toLed, bool wait, bool increment, long color){
  
  for (int i=fromLed; i<toLed; i++){    
        leds[i]=color; 
        if (wait==true) delay(LIGHT_UP_SPEED);
        if (increment==true) FastLED.show();        
      }
             
      if (increment==false)FastLED.show();

  }




void encoderPressed(int newPosition){


      doSomenthingWithLeds(0, NUM_LEDS, true, true, BLUE);

      doSomenthingWithLeds(0, NUM_LEDS, false, false, GREEN);

      timerLength=millis(); //starting time    
      countDownenMs = 60*newPosition*1000L;   // countdown time in ms
      previousMillis=0;
      countDown=true;
  
  }




void timerDown(){

  currentMillis=millis();

  if (currentMillis-previousMillis>=COUNTDOWN_UPDATE){  // update that every X seconds


    previousMillis = currentMillis;
     
    unsigned long temporal =previousMillis-timerLength; //time remaining
     
    unsigned long ledsRestar=map(temporal, 0, countDownenMs, 0, 37);  //leds corresponding to the time already passed

    doSomenthingWithLeds((NUM_LEDS-ledsRestar), NUM_LEDS, false, false, BLACK);

    if (ledsRestar>=NUM_LEDS){  // if the countdown has come to an end...

      countDown=false;

      lcd.setCursor(TIME_CURSOR,1);
      lcd.print("Done!");
   
      }
    
    }
  
}




String timeString (int minutes){

  String foo="";
  
  if (minutes>=10){
    
    foo=minutes;
    
    }else{
      
      foo=" "+minutes;
      
      }

  return foo;
  
  }
