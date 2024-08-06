/*
Physical Microcontroller XIAO nRF52840 BLE Sense
Core & version: Seeed nRF52 Boards 1.1.8  https://files.seeedstudio.com/arduino/package_seeeduino_boards_index.json
 --> don't choose mbed enabled version!
FastLED version = 3.6.0 https://github.com/FastLED/FastLED
Adafruit NeoPixel version = 1.11.0 https://github.com/adafruit/Adafruit_NeoPixel

Tested RGB Led Type: WS2812B (common type with 4 pins Vcc,Gnd,Din,Dout)

for other RGB Leds you might have to change "NEO_GRB + NEO_KHZ800"

  Everything that begins with leds[]... is regarding  FastLED array and library
  and everything that begins with strip. is regarding the Neopixel Led Array and data
 */



#define LED_PIN D2          // your Led Data Pin
#define NUM_LEDS 12         // number of LEDs
#define DELAYMS_SHOWLED 25  // 100Hz
#define DELAYMS_MODE 2000
#define SIZE(ARRAY) (sizeof(ARRAY) / sizeof(ARRAY[0]))
#include <FastLED.h>
FASTLED_USING_NAMESPACE
#include <colorpalettes.h>
#include <Adafruit_NeoPixel.h>
uint8_t brightness = 150;
CRGB leds[NUM_LEDS];  // create virtual FastLED LED Strip with NUM_LEDS
int buttonState;




int mode = 1;
#define COOLING 55               //fire
#define SPARKING 120             //fire
bool gReverseDirection = false;  //fire




uint8_t colorIndex[NUM_LEDS];
DEFINE_GRADIENT_PALETTE(aurora_gp) {
   0,     0,   100,    0,  //black green
   89,    20,  232,  30, //dark green
   135,   0,   234,  141,//bright green
   175,   1,   126,  213,//blue
   225,   181, 61,   255,//purple
   255,   141, 1,    196 //dark purple
   };
CRGBPalette16 aurora = aurora_gp;


Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);  //create adafruit Neopixel LED strip with also NUM_LEDS

void setup() {
  strip.begin();
  strip.setBrightness(brightness);
  ledsClear();  // Initialize all pixels to 'off'
  Serial.begin(9600);
  pinMode(D3, INPUT_PULLUP);
  pinMode(13, OUTPUT);  
}

void loop() {
digitalWrite(13, LOW); // om sneller op te laden
  buttonState = digitalRead(3);
  Serial.print(mode);
  if (buttonState == HIGH) {
    //Serial.println("knop los");
  }
  if (buttonState == LOW) {
    //Serial.println("knop ingedrukt");
    mode++;
    delay(500);
    if (mode > 5) {
      mode = 0;
    }
  }


  // EVERY_N_MILLIS(DELAYMS_MODE) {
  //   mode++;
  //   if (mode > 3) {
  //     mode = 0;
  //   }
  // }

  EVERY_N_MILLIS(DELAYMS_SHOWLED) {

    //uncomment rainbow(); and comment out ledPlasma();
    //for standard FastLED rainbow animation
    switch (mode) {
      case 1:  // your hand is on the sensor
        Serial.println("plasma");
        ledPlasma();
        ledsCopyAndShow();
        break;
      case 2:  // your hand is close to the sensor
        Serial.println("rainbow");
        rainbow();
        ledsCopyAndShow();
        break;
      case 3:  // your hand is close to the sensor
        Serial.println("fire");
        Fire2012();
        ledsCopyAndShow();
        break;
        case 4:  // your hand is on the sensor
        Serial.println("aurora");
        auroraa();
        ledsCopyAndShow();
        break;
        case 5:  // your hand is on the sensor
        Serial.println("heat");
        ledHeat();
        ledsCopyAndShow();
        break;
    }
  }
}

// inoise8 will generate a 2D noisefield
void ledPlasma() {
  int zoom = 60;         // try values between 20 and 80 to zoom in or out into the plasma noise field
  float speedFract = 5;  // increase to go slower , decrease to move the noise faster
  uint16_t aniSpeed = millis() / speedFract;
  for (int i = 0; i < NUM_LEDS; i++) {
    int xPos = 0;
    int yPos = i;
    byte noises = inoise8(yPos * zoom, xPos * zoom, aniSpeed);
    leds[i] = ColorFromPalette(ForestColors_p, noises, 255);  //  (color palette  ,rainbow color index, brightness)
  }
}

void rainbow() {
  static uint8_t gHue = 0;
  EVERY_N_MILLISECONDS(20) {
    gHue++;
  }
  fill_rainbow(leds, NUM_LEDS, gHue, 7);
}



void Fire2012() {
  // Array of temperature readings at each simulation cell
  static uint8_t heat[NUM_LEDS];

  // Step 1.  Cool down every cell a little
  for (int i = 0; i < NUM_LEDS; i++) {
    heat[i] = qsub8(heat[i], random8(0, ((COOLING * 10) / NUM_LEDS) + 2));
  }

  // Step 2.  Heat from each cell drifts 'up' and diffuses a little
  for (int k = NUM_LEDS - 1; k >= 2; k--) {
    heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2]) / 3;
  }

  // Step 3.  Randomly ignite new 'sparks' of heat near the bottom
  if (random8() < SPARKING) {
    int y = random8(7);
    heat[y] = qadd8(heat[y], random8(160, 255));
  }

  // Step 4.  Map from heat cells to LED colors
  for (int j = 0; j < NUM_LEDS; j++) {
    CRGB color = HeatColor(heat[j]);
    int pixelnumber;
    if (gReverseDirection) {
      pixelnumber = (NUM_LEDS - 1) - j;
    } else {
      pixelnumber = j;
    }
    leds[pixelnumber] = color;
  }
}




void ledOcean() {
  int zoom = 60;         // try values between 20 and 80 to zoom in or out into the plasma noise field
  float speedFract = 5;  // increase to go slower , decrease to move the noise faster
  uint16_t aniSpeed = millis() / speedFract;
  for (int i = 0; i < NUM_LEDS; i++) {
    int xPos = 0;
    int yPos = i;
    byte noises = inoise8(yPos * zoom, xPos * zoom, aniSpeed);
    leds[i] = ColorFromPalette(OceanColors_p, noises, 255);  //  (color palette  ,rainbow color index, brightness)
  }
}



void ledHeat() {
  int zoom = 60;         // try values between 20 and 80 to zoom in or out into the plasma noise field
  float speedFract = 5;  // increase to go slower , decrease to move the noise faster
  uint16_t aniSpeed = millis() / speedFract;
  for (int i = 0; i < NUM_LEDS; i++) {
    int xPos = 0;
    int yPos = i;
    byte noises = inoise8(yPos * zoom, xPos * zoom, aniSpeed);
    leds[i] = ColorFromPalette(HeatColors_p, noises, 255);  //  (color palette  ,rainbow color index, brightness)
  }
}










void auroraa() {
  
  /*for (int i = NUM_LEDS-1; i = 1; i--) {
    leds[i] = leds[i-1]
  }*/
  uint8_t wavesize = random8(10,45);//選擇一次波的長度
  uint8_t color = random8(0,255);//選擇該次波的顏色
  //Serial.println(wavesize);
  //Serial.println(color);
  for (int i = 0; i < wavesize; i++) {
    for (int j = NUM_LEDS-1; j >= -1 ; j--) {//先將所有的像素往後移一格
      leds[j] = leds[j-1];
    }
    leds[0] = ColorFromPalette(aurora, color+0.3*i, 55+(200/wavesize*i));
    //Serial.println(leds[0]);
    FastLED.delay(2);
  }
  for (int k = 0; k < wavesize; k++) {
    for (int l = NUM_LEDS-1; l >= -1; l--) {//先將所有的像素往後移一格
      leds[l] = leds[l-1];
    }
    leds[0] = ColorFromPalette(aurora, color-0.3*k, 255-(200/wavesize*k));
    FastLED.delay(2);
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