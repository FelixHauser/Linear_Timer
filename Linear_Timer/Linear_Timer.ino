// WS2812B Strip timer. 
// Maker: Felix Hauser  https://github.com/FelixHauser
// Open Source Project: Copy, distribute but document and attribute credit.

#include "Configuration.h"

bool segel=false;
int segelPhase;

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
  
  //Serial.begin(9600);
    
  FastLED.addLeds<LED_TYPE, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(  BRIGHTNESS );

  encoder.setPosition(START_POSITION / ROTARYSTEPS);
  
  lcd.begin(COLUMNS,ROWS);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Zeit: ");

  pinMode(BUZZER_PIN, OUTPUT);

  delay(100);
   
} 

void buzzer(int freq, int firstDelay, int secondDelay, int repeat){

  for (int foo=1; foo<repeat; foo++){
    
    tone (BUZZER_PIN, freq);
    delay (firstDelay);
    noTone (BUZZER_PIN);
    delay (secondDelay);
  }
  
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

  if(newPos!=oldPos) printOnLcd (timeString(newPos), 0, TIME_CURSOR);
  
  oldPos=newPos;

  
  if (encoder.update() && encoder.read()==LOW) encoderPressed();  //if encoder button is pressed
  
  if (countDown==true) timerDown();
    
  
}



void doSegel(){

  lcd.clear();
  segelPhase++;
  buzzer(1000, 1000, 300, 4);
  
  switch (segelPhase){
            case 2:
              printOnLcd (PHASE2, 0, 0);
              setTimeToCount(TIME_PHASE2);  
              break;
              
            case 3:
              setTimeToCount(TIME_PHASE3);           
              printOnLcd (PHASE3, 0, 0);
              break;
              
            case 4:
              setTimeToCount(TIME_PHASE4);            
              printOnLcd (PHASE4, 0, 0);
              break;
                        
            case 5:          
              setTimeToCount(TIME_PHASE5);             
              printOnLcd (PHASE5, 0, 0);
              break;

            case 6:
              printOnLcd(PHASE6, 0, 0);
              segelPhase=1;
              segel=false;
              break;
        }

  countDown=true;
  
  }


void doSomenthingWithLeds(int fromLed, int toLed, bool wait, bool increment, long color){
  
  for (int i=fromLed; i<toLed; i++){    
        leds[i]=color; 
        if (wait==true) delay(LIGHT_UP_SPEED);
        if (increment==true) FastLED.show();        
      }
             
      if (increment==false)FastLED.show();

  }


void encoderPressed(){

if (countDown==false){
  
  if (newPos<=0) {  // (newPos==-1)
    
    segel=true;
    segelPhase=1; 
    setTimeToCount(TIME_PHASE1); //initial selgel phase
    printOnLcd (PHASE1, 0, 0);
    
  }else{

    setTimeToCount(newPos);
    
    }

}else{

  segel=false;
  segelPhase=1;
  countDown=false;
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Zeit: ");

  int pepe=encoder.getPosition() * ROTARYSTEPS;
  
  printOnLcd (timeString(pepe), 0, TIME_CURSOR);
  
  doSomenthingWithLeds(0, NUM_LEDS, false, false, BLACK); //change to green
  
  
  }

}


void setTimeToCount(int timeToCount){

      doSomenthingWithLeds(0, NUM_LEDS, true, true, BLUE);  //light up all leds sequentally
      doSomenthingWithLeds(0, NUM_LEDS, false, false, GREEN); //change to green

      timerLength=millis(); //starting time

      countDownenMs = 60*timeToCount*1000L;   // countdown time in ms
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
      buzzer(1000, 1000, 300, 4);
      if (segel==false){
            printOnLcd("     Done !     ", 1, 0);
        }else{

          doSegel();
          
          }
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



String timeString (int timeToWrite){

char data[16];

if (timeToWrite>=10){
    sprintf(data, "%d min", timeToWrite);
    
  }else if (timeToWrite<10 && timeToWrite>0){
    
    sprintf(data, " %d min", timeToWrite);
    
    }else{
      
    sprintf(data, PHASES_TIMER, newPos);
    
      }

return data;
  
  }



  
