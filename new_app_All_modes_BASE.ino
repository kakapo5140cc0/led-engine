#include <bluefruit.h>

// BLE Service
BLEUart bleuart;  // UART over BLE
int time_ = 100;
int data_;



uint8_t brightness = 250;

#define LED_PIN D2  // your Led Data Pin
#define PIN_HICHG (22)
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
DEFINE_GRADIENT_PALETTE(aurora_gp){
  0, 0, 10, 0,       //black
  89, 20, 232, 30,   //dark green
  135, 0, 234, 101,  //bright green
  175, 1, 126, 213,  //blue
  225, 181, 0, 255,  //purple
  255, 141, 1, 196   //dark purple
};
CRGBPalette16 greenblue = aurora_gp;


///sky
DEFINE_GRADIENT_PALETTE(thunder_gp){
  // 0x5e47dd,      //black
  // 0x040420,
  // 0x4634cc,
  // 0x8f60d8,
  // 0xcc5494,
  0, 4,4,32,       //black
  89, 94,71,221,   //dark green
  135, 70,52,204,  //bright green
  175, 143,96,216,  //blue
  225, 204,84,148,  //purple
  255, 141, 1, 196   //dark purple
};
CRGBPalette16 purpleish = thunder_gp;




Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);  //create adafruit Neopixel LED strip with also NUM_LEDS





void setup() {
  strip.begin();
  //strip.setBrightness(brightness);
  ledsClear();  // Initialize all pixels to 'off'
  //Serial.begin(9600);
  pinMode(D3, INPUT);
  pinMode(PIN_HICHG, OUTPUT);
  digitalWrite(PIN_HICHG, LOW);
  for (int i = 0; i < NUM_LEDS; i++) {
    colorIndex[i] = random8();
  }





  //////////////////////////////////////////////ble
  //Serial.begin(115200);
  while (!Serial) delay(10);  // Wait for Serial to be ready

  // Initialize Bluefruit
  Bluefruit.begin();
  Bluefruit.setTxPower(4);            // Transmission Power
  Bluefruit.setName("Led Engine 1");  // BLE Device Name
                                      //    Bluefruit.setName("Xiao_BLE_1"); // BLE Device Name

  Bluefruit.Periph.setConnectCallback(connect_callback);
  Bluefruit.Periph.setDisconnectCallback(disconnect_callback);

  // Initialize the BLE UART service
  bleuart.begin();
  bleuart.setRxCallback(bleuart_rx_callback);

  // Start Advertising
  startAdv();
  pinMode(LED_BUILTIN, OUTPUT);

  // pinMode(ledRed, OUTPUT);
  // pinMode(ledGreen, OUTPUT);
  // pinMode(ledBlue, OUTPUT);
}

void loop() {
  // No need to put code here, everything is handled in callbacks
  // Serial.println()
  // digitalWrite(LED_BUILTIN, HIGH);
  // delay(time_);
  // digitalWrite(LED_BUILTIN, LOW);
  // delay(time_);
  EVERY_N_MILLIS(DELAYMS_SHOWLED) {
    switch (mode) {
      case 1:  // your hand is on the sensor
        thunder();
        ledsCopyAndShow();
        break;
      case 2:  // your hand is on the sensor
        aurora();
        ledsCopyAndShow();
        break;
      case 3:  // your hand is on the sensor
        sunset();
        ledsCopyAndShow();
        break;
      case 4:  // your hand is on the sensor
        bioluminescence();
        ledsCopyAndShow();
        break;
      case 5:  // your hand is on the sensor
        fluorescence();
        ledsCopyAndShow();
        break;
      case 6:  // your hand is on the sensor
        reflection();
        ledsCopyAndShow();
        break;
      case 7:  // your hand is on the sensor
        spectra();
        ledsCopyAndShow();
        break;
      case 8:  // your hand is on the sensor
        photonic();
        ledsCopyAndShow();
        break;
      case 9:  // your hand is on the sensor
        vulcanic();
        ledsCopyAndShow();
        break;
      case 10:  // your hand is on the sensor
        ocean();
        ledsCopyAndShow();
        break;
      case 11:  // your hand is on the sensor
        forest();
        ledsCopyAndShow();
        break;
      case 12:  // your hand is on the sensor
        sky();
        ledsCopyAndShow();
        break;
    }
  }
}

void startAdv(void) {
  // Advertising Packet
  Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
  Bluefruit.Advertising.addTxPower();
  Bluefruit.Advertising.addName();
  Bluefruit.Advertising.addService(bleuart);

  // Start Advertising
  Bluefruit.Advertising.restartOnDisconnect(true);
  Bluefruit.Advertising.setInterval(32, 244);  // Advertising interval in 0.625 ms units
  Bluefruit.Advertising.setFastTimeout(30);    // Fast mode timeout in seconds
  Bluefruit.Advertising.start(0);              // 0 = Don't stop advertising
}

void connect_callback(uint16_t conn_handle) {
  // Serial.println("Connected");
}

void disconnect_callback(uint16_t conn_handle, uint8_t reason) {
  // Serial.println("Disconnected");
}

void bleuart_rx_callback(uint16_t conn_handle) {
  (void)conn_handle;

  // Read incoming data
  uint8_t packet[20];
  int length = bleuart.read(packet, sizeof(packet));

  //   Serial.print("Received: ");
  //   for (int i = 0; i < length; i++) {
  //     Serial.print(packet[i]);
  //   }
  //Serial.println(length);
  //   Serial.println(packet[0]);
  String labelNames = "";

  switch (packet[0]) {

    case 49:
      // Thunder
      labelNames += "Thunder";
      mode = 1;
      break;

    case 50:
      // Aurora
      labelNames += "Aurora";
      // aurora();
      mode = 2;
      // ledsCopyAndShow();
      break;

    case 51:
      // Sunset
      labelNames += "Sunset";
      mode = 3;
      break;

    case 52:
      // Bioluminescence
      labelNames += "Bioluminescence";
      mode = 4;
      break;

    case 53:
      // Fluorescence
      labelNames += "Fluorescence";
      mode = 5;
      break;

    case 54:
      // Reflection
      labelNames += "Reflection";
      mode = 6;
      break;

    case 55:
      // Spectra
      labelNames += "Spectra";
      mode = 7;
      break;

    case 56:
      // Photonic
      labelNames += "Photonic";
      mode = 8;
      break;

    case 57:
      // Vulcanic
      labelNames += "Vulcanic";
      mode = 9;
      break;

    case 58:
      // Ocean
      labelNames += "Ocean";
      mode = 10;
      break;

    case 59:
      // Forest
      labelNames += "Forest";
      mode = 11;
      break;

    case 60:
      // Sky
      labelNames += "Sky";
      mode = 12;
      break;

    case 65:
      // A
      labelNames += "OFF";
      for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = 0x000000;
      }
      ledsCopyAndShow();
      break;

    case 66:
      // B
      labelNames += "Empty";
      brightness = 50;
      break;

    case 67:
      // C
      labelNames += "Half";
      brightness = 125;
      break;

    case 68:
      // D
      labelNames += "Full";
      brightness = 250;
      break;

    default:
      // Default case
      break;
  }

  // Print the stored label names
  Serial.println(labelNames);
}



void ledsCopyAndShow() {
  for (int i = 0; i < NUM_LEDS; i++) {

    //we use --> strip.setPixelColor(led_index, r_val, g_val, b_val);
    // and set the R/G/B values to the R/G/B values of the fastLED Array

    strip.setPixelColor(i, leds[i].r, leds[i].g, leds[i].b);
    // leds[i] --> fastLED pixel number i
  }
  strip.setBrightness(brightness);
  strip.show();
}

void ledsClear() {
  fill_solid(leds, NUM_LEDS, CRGB::Black);
  ledsCopyAndShow();
}
