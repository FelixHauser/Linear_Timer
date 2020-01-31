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
long newPos;
long oldPos;

RotaryEncoder encoder(ENCODER_CW, ENCODER_CCW, ROTARY_BUTTON, DEBOUNCE_INTERVAl); //declare encoder object

const int  en = 2, rw = 1, rs = 0, d4 = 4, d5 = 5, d6 = 6, d7 = 7, bl = 3;  // pinout
const int i2c_addr = 0x27;    //I2C Address - change if reqiuired
LiquidCrystal_I2C lcd(i2c_addr, en, rw, rs, d4, d5, d6, d7, bl, POSITIVE);  //declare LCD object


CRGB leds[NUM_LEDS]; //declare LED strip object 


void setup(){
  
  Serial.begin(9600);
    
  FastLED.addLeds<LED_TYPE, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(  BRIGHTNESS );
  
  encoder.setPosition(START_POSITION / ROTARYSTEPS);

  // Set LCD type as 16 char, 2 rows
  lcd.begin(COLUMNS,ROWS);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Zeit: ");
  delay(100);
  
} 


void loop() {

  
  encoder.tick();

  // get the current physical position and calc the logical position
  newPos = encoder.getPosition() * ROTARYSTEPS;

  if (newPos < ROTARYMIN) {
    encoder.setPosition(ROTARYMIN / ROTARYSTEPS);
    newPos = ROTARYMIN;
    
    
  } else if (newPos > ROTARYMAX) {
    encoder.setPosition(ROTARYMAX / ROTARYSTEPS);
    newPos = ROTARYMAX;
    
  } 

  if(newPos!=oldPos) printOnLcd (timeString(), 0, TIME_CURSOR);
  
  oldPos=newPos;

  if (encoder.update() && encoder.read()==LOW) encoderPressed(newPos);  //if encoder button is pressed

    
  if (countDown==true) timerDown();
    
  
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
     
    unsigned long ledsRestar=map(temporal, 0, countDownenMs, 0, NUM_LEDS);  //leds corresponding to the elapsedTime
    doSomenthingWithLeds((NUM_LEDS-ledsRestar), NUM_LEDS, false, false, BLACK);

    lcdTimer(temporal);

    if (temporal>=countDownenMs){  // if the countdown has come to an end...
      
      countDown=false;
      printOnLcd("     Done !     ", 1, 0);
   
      }
    
    }  
}



void lcdTimer (unsigned long elapsedTime){

  // timeRemaining = setTime-elapsedTime = setTime-(currentMillis-initialMillis)

  //countDownenMs=ms of countdown. This is a fixed value
  //timerLength=millis() at the beginning of the counter
  //elapsedTime=curentMillis-timerLength

  unsigned long remainingMillis=countDownenMs-elapsedTime;
  unsigned long minutes=remainingMillis/60000;
  unsigned long seconds=(remainingMillis-minutes*60000)/1000;
  
  char foo[16];
  

 if (minutes>=10){
  
  if (seconds>=10){
    
      sprintf(foo, "%ld:%ld", minutes, seconds);
     }else{
      sprintf(foo, "%ld:0%ld", minutes, seconds);
    }
    
  }else{

  if (seconds>=10){
      sprintf(foo, " %ld:%ld", minutes, seconds);
     }else{
      sprintf(foo, " %ld:0%ld", minutes, seconds);
    }
    
 }
  
    
  printOnLcd (foo, 1, 5);
  
}
  


void printOnLcd (String stringToPrint, int line, int row){

  lcd.setCursor(row, line);
  lcd.print(stringToPrint);
  
  }


String timeString (){

char data[16];

if (newPos>=10){
    sprintf(data, "%d min", newPos);
  }else{
    sprintf(data, " %d min", newPos);
    }

return data;
  
  }



  
