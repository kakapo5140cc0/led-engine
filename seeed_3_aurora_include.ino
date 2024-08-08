uint8_t brightness = 50;

#define LED_PIN D2          // your Led Data Pin
#define NUM_LEDS 16         // number of LEDs
#define DELAYMS_SHOWLED 25  // 100Hz
#define DELAYMS_MODE 2000
#define SIZE(ARRAY) (sizeof(ARRAY) / sizeof(ARRAY[0]))
#include <FastLED.h>
FASTLED_USING_NAMESPACE
#include <colorpalettes.h>
#include <Adafruit_NeoPixel.h>
CRGB leds[NUM_LEDS];  // create virtual FastLED LED Strip with NUM_LEDS
int buttonState;

int mode = 1;
#define COOLING 55               //fire
#define SPARKING 120             //fire
bool gReverseDirection = false;  //fire

 uint8_t colorIndex[NUM_LEDS];
DEFINE_GRADIENT_PALETTE(aurora_gp) {
  0,     0,   10,    0,  //black
  89,    20,  232,  30, //dark green
  135,   0,   234,  101,//bright green
  175,   1,   126,  213,//blue
  225,   181, 0,   255,//purple
  255,   141, 1,    196 //dark purple
};
CRGBPalette16 greenblue = aurora_gp;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);  //create adafruit Neopixel LED strip with also NUM_LEDS

void setup() {
  strip.begin();
  strip.setBrightness(brightness);
  ledsClear();  // Initialize all pixels to 'off'
  Serial.begin(9600);
  pinMode(D3, INPUT);
  pinMode(13, OUTPUT);
   for (int i = 0; i < NUM_LEDS; i++) {
     colorIndex[i] = random8();
   }
}

void loop() {
  digitalWrite(13, LOW);  // om sneller op te laden
  buttonState = digitalRead(3);
  Serial.print(mode);
  if (buttonState == HIGH) {
  }
  if (buttonState == LOW) {
    mode++;
    delay(333);
    if (mode > 7) {
      mode = 1;
    }
  }


  EVERY_N_MILLIS(DELAYMS_SHOWLED) {
    switch (mode) {
      case 1:  // your hand is on the sensor
        Serial.println("rainbow");
        rainbow();
        ledsCopyAndShow();
        break;
      case 2:  // your hand is close to the sensor
        Serial.println("white");
        ledWhite();
        ledsCopyAndShow();
        break;
      case 3:  // your hand is close to the sensor
        Serial.println("fire");
        Fire2012();
        ledsCopyAndShow();
        break;
      case 4:  // your hand is on the sensor
        Serial.println("ocean");
        ledOcean();
        ledsCopyAndShow();
        break;
      case 5:  // your hand is on the sensor
        Serial.println("forest");
        ledForest();
        ledsCopyAndShow();
        break;
      case 6:  // your hand is on the sensor
        Serial.println("sky");
        aurora();
        ledsCopyAndShow();
        break;
      case 7:  // your hand is on the sensor
        Serial.println("off");
        for (int i = 0; i < NUM_LEDS; i++) {
          leds[i] = 0x000000;
        }
        ledsCopyAndShow();
        break;
    }
  }
}

void ledsCopyAndShow() {
  for (int i = 0; i < NUM_LEDS; i++) {

    //we use --> strip.setPixelColor(led_index, r_val, g_val, b_val);
    // and set the R/G/B values to the R/G/B values of the fastLED Array

    strip.setPixelColor(i, leds[i].r, leds[i].g, leds[i].b);
    // leds[i] --> fastLED pixel number i
  }
  strip.show();
}

void ledsClear() {
  fill_solid(leds, NUM_LEDS, CRGB::Black);
  ledsCopyAndShow();
}