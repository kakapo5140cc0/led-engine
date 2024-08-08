#include <bluefruit.h>

// BLE Service
BLEUart bleuart;  // UART over BLE
int mode = 0;
void setup() {
  //Serial.begin(115200);
  //while (!Serial) delay(10);  // Wait for Serial to be ready

  // Initialize Bluefruit
  Bluefruit.begin();
  Bluefruit.setTxPower(4);          // Transmission Power
                                    // Bluefruit.setName("Xiao_BLE"); // BLE Device Name . change this and keep it unique for each device
  Bluefruit.setName("Xiao_BLE_3");  // BLE Device Name. change this and keep it unique for each device

  Bluefruit.Periph.setConnectCallback(connect_callback);
  Bluefruit.Periph.setDisconnectCallback(disconnect_callback);

  // Initialize the BLE UART service
  bleuart.begin();
  bleuart.setRxCallback(bleuart_rx_callback);

  // Start Advertising
  startAdv();
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  // pinMode(ledRed, OUTPUT);
  // pinMode(ledGreen, OUTPUT);
  // pinMode(ledBlue, OUTPUT);
}

void loop() {
  // No need to put code here, everything is handled in callbacks
  // Serial.println()
  //    digitalWrite(LED_BUILTIN, HIGH);
  // delay(time_);
  //    digitalWrite(LED_BUILTIN, LOW);
  //    delay(time_);
  switch (mode) {
    case 1:  // your hand is on the sensor
      digitalWrite(LED_GREEN, HIGH);
      digitalWrite(LED_BLUE, HIGH);

      digitalWrite(LED_RED, LOW);
      break;
    case 2:  // your hand is close to the sensor
      digitalWrite(LED_RED, HIGH);
      digitalWrite(LED_BLUE, HIGH);

      digitalWrite(LED_GREEN, LOW);
      break;
    case 3:  // your hand is close to the sensor
      digitalWrite(LED_RED, HIGH);
      digitalWrite(LED_GREEN, HIGH);

      digitalWrite(LED_BLUE, LOW);
      break;
    case 4:  // your hand is close to the sensor
      digitalWrite(LED_RED, HIGH);
      digitalWrite(LED_GREEN, HIGH);
      digitalWrite(LED_BLUE, HIGH);
      break;
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

  // Print received data
  // Serial.print("Received: ");
  // for (int i = 0; i < length; i++) {
  //   Serial.print(packet[i]);
  // }
  // Serial.println(packet[0]);
  // String str = (char*)packet;

  // // Serial.println(sizeof(str));
  // Serial.println(char(packet[0]));
  if ((packet[0]) == 49) {
    // Serial.println("One printed");
    mode = 1;
  } else if ((packet[0]) == 50) {
    // Serial.println("Two printed");
    mode = 2;
  } else if ((packet[0]) == 51) {
    // Serial.println("Three printed");
    mode = 3;
  } else if ((packet[0]) == 52) {
    //Serial.println("Four printed");
    mode = 4;
  }  //else {
     // Serial.println ("Nothing");
  //}
  // Serial.println();
}