#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIXELPIN 6
#define NUM_LEDS 8
#define BRIGHTNESS 255

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIXELPIN, NEO_GRBW + NEO_KHZ800);


int sensorPin = A0;
int sensorValue = 0;
float sleepTime = 200;
int FirstLED = 0;
int LastLED = NUM_LEDS - 1;
boolean ascending = true;
int currentlyLit = 2;

int delayMin = 15;
int delayMax = 300;
  
int brightnessArray [NUM_LEDS];

void setup() {                
  Serial.begin(9600);

  for(uint16_t i=0; i<strip.numPixels(); i++) {
    brightnessArray[i] = 0;
  }
  strip.setBrightness(BRIGHTNESS);
  strip.begin();
  strip.show();
}

void loop() {

  if (currentlyLit == FirstLED)
  {
    ascending = true;
  }
  else if (currentlyLit == LastLED)
  {
    ascending = false;
  }
  
  strip.setPixelColor(currentlyLit, strip.Color(0, 0, 0));
  strip.show();
  
  if (ascending)
  {
     currentlyLit++;
  }
  else
  {
    currentlyLit--;
  }


  strip.setPixelColor(currentlyLit, strip.Color(255, 0, 0, 0));
  strip.show();
    





  //delay(sleepTime);
  delay(sleepTime);

}
