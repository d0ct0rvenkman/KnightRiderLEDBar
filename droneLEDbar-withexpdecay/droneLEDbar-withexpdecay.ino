#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIXELPIN 4  //3 default
#define NUM_LEDS 16 //16 default
#define BRIGHTNESS 255

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIXELPIN, NEO_GRBW + NEO_KHZ800);

// tunables
uint8_t decayLambda = 35; // 35 tuned for trinket 8mhz
uint8_t brightenAmount = 50;
uint16_t oscillationInterval = 1300;  // 1.3 seconds
uint8_t LEDInterval = oscillationInterval / (2 * NUM_LEDS - 2);

// runtime
uint8_t FirstLED = 0;
uint8_t LastLED = NUM_LEDS - 1;
boolean ascending = true;
uint8_t currentlyLit = 0;


unsigned long transitionTime = 0;
float LEDbrightness [NUM_LEDS];
float LEDdecayedBrightness [NUM_LEDS];
float LEDdecayTime [NUM_LEDS];

uint8_t x;
uint8_t i;

//pixels
uint8_t R = 0;
uint8_t G = 0;
uint8_t B = 0;
uint8_t W = 0;

void setup() {
  //Serial.begin(115200);

  strip.setBrightness(BRIGHTNESS);
  strip.begin();

  for(x=0; x < 255; x++) {
    for(i = 0; i < strip.numPixels(); i++) {
      LEDbrightness[i] = x;
      
      strip.setPixelColor(i, strip.Color(LEDbrightness[i],0,0,0));
    }
    strip.show();
    delay(3);
  }
  
  delay(1000);
  for(i = 0; i < strip.numPixels(); i++) {
    LEDdecayTime[i] = millis();
  }
}

void loop() {

  if (currentlyLit == FirstLED) {
    ascending = true;
  }
  else if (currentlyLit == LastLED) {
    ascending = false;
  }

  if ((millis() - transitionTime)  >= LEDInterval) {
    transitionTime = LEDdecayTime[currentlyLit] = millis();
    //Serial.print("LED changing: ");
    if (ascending) {
       currentlyLit++;
    } else {
      currentlyLit--;
    }
    //Serial.println(currentlyLit);
    LEDbrightness[currentlyLit] = LEDdecayedBrightness[currentlyLit];
  }

  for(i = 0; i < strip.numPixels(); i++) {
    //Serial.print(i);
    //Serial.print(": ");

    if (i == currentlyLit) {
      //Serial.print("U ");
      LEDbrightness[i] = 255;
      LEDdecayedBrightness[i] = LEDbrightness[i];
    } else {
      //Serial.print("D ");
      LEDdecayedBrightness[i] = LEDbrightness[i] * exp((millis() - LEDdecayTime[i]) / -decayLambda);
    }

    //Serial.println(LEDdecayedBrightness[i]);
    R = LEDdecayedBrightness[i];
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

}
