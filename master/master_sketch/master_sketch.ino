#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

String name = "ESP32test"; // device to connect with
bool connected;

const int redLedPin = 16;      // red dual-color led
const int buttonPin1 = 19;     // button for LED 1 control
const int buttonPin2 = 4;     // button for LED 2 control
const int buttonPin3 = 5;     // button for LED 3 control
int brightness = 128;

void setup() {
  Serial.begin(115200);
  pinMode(redLedPin, OUTPUT);
  pinMode(buttonPin1, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP);
  pinMode(buttonPin3, INPUT_PULLUP);
  
  
  SerialBT.begin("ESP32test_Master", true); // true starts as master
  Serial.println("The device started in master mode, make sure remote BT device is on!");

  connected = SerialBT.connect(name); // connect to "ESP32test"

  delay(5000); // time to connect

  if (connected) {
    Serial.println("Connected Successfully!");
  }
}

void loop() {
  if (SerialBT.connected()) {
    digitalWrite(redLedPin, LOW);  // turn on
  }
  else {
    digitalWrite(redLedPin, HIGH); // turn off
    
  }

  // Check if button to increase brightness is pressed
  if (digitalRead(buttonPin1) == LOW) {
    brightness += 10; // increase brightness
    if (brightness > 255) {
      brightness = 255;
    }
    while (digitalRead(buttonPin1) == LOW) {} // wait for button release
  }

  // Check if button to decrease brightness is pressed
  if (digitalRead(buttonPin3) == LOW) {
    brightness -= 10; // decrease brightness
    if (brightness < 0) {
      brightness = 0;
    }
    while (digitalRead(buttonPin3) == LOW) {} // wait for button release
  }

   // Check if button to turn off is pressed
  if (digitalRead(buttonPin2) == LOW) {
    brightness = 0; // set brightness to 0 (turn off)
    while (digitalRead(buttonPin2) == LOW) {} // wait for button release
  }
  

  if (Serial.available()) {
    SerialBT.write(Serial.read());
  }
  if (SerialBT.available()) {
    Serial.write(SerialBT.read());
  }

  delay(20);
}
