#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIXELPIN 6
#define NUM_LEDS 16
#define BRIGHTNESS 255

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIXELPIN, NEO_GRBW + NEO_KHZ800);

// tunables
uint8_t decayInterval = 2;
uint8_t decayAmount = 3;
uint8_t brightenAmount = 25;
uint8_t LEDInterval = 30;

// runtime
uint16_t timeSlept = 0;
uint8_t FirstLED = 0;
uint8_t LastLED = NUM_LEDS - 1;
boolean ascending = true;
uint8_t currentlyLit = 0;
uint8_t brightnessArray [NUM_LEDS];
uint8_t x;
uint8_t i;

//pixels
uint8_t R = 0;
uint8_t G = 0;
uint8_t B = 0;
uint8_t W = 0;

void setup() {                
  strip.setBrightness(BRIGHTNESS);
  strip.begin();

  for(x=0; x<255; x++) {
    for(i=0; i<strip.numPixels(); i++) {
      brightnessArray[i] = x;
      strip.setPixelColor(i, strip.Color(brightnessArray[i],0,0,0));
    }
    strip.show();
    delay(1);
  }
  
  delay(250);
}

void loop() {

  if (currentlyLit == FirstLED) {
    ascending = true;
  }
  else if (currentlyLit == LastLED) {
    ascending = false;
  }

  if (timeSlept >= LEDInterval) {
    timeSlept = 0;
    if (ascending) {
       currentlyLit++;
    } else {
      currentlyLit--;
    }
  }

  for(i=0; i<strip.numPixels(); i++) {
    if (i == currentlyLit) {
      if (brightnessArray[i] >= (255 - brightenAmount)) {
        brightnessArray[i] = 255;
      } else {
        brightnessArray[i] += brightenAmount;  
      }
    } else {
      if (brightnessArray[i] <= decayAmount) {
        brightnessArray[i] = 0;
      } else {
        brightnessArray[i] -= decayAmount;
      }
    }
    R = brightnessArray[i];
    G = 0;
    B = 0;
    if (R >= 200) {
      W = 1;  
    } else {
      W = 0;
    }

/*
   // single LED test
   if (i != 8) {
    R = 0;
    G = 0;
    B = 0;
    W = 0;
   }
*/    
    strip.setPixelColor(i, strip.Color(R,G,B,W));
  }

  strip.show();

  timeSlept += decayInterval;
  delay(decayInterval);

}
