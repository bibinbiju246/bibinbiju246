#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

const int redledPin = 16; // LED pin
const int buttonPin1 = 19;     // button for LED 1 control
const int buttonPin2 = 4;     // button for LED 2 control
const int buttonPin3 = 5;     // button for LED 3 control
int brightness = 0;

void setup() {
  Serial.begin(115200);
  pinMode(redledPin, OUTPUT);
  
  SerialBT.begin("ESP32test", false); // true starts as slave
  Serial.println("The device started in slave mode.");

  while (!SerialBT.connected()) {
    delay(100);
  }
  Serial.println("Connected to master device!");
}

void loop() {
  while (SerialBT.available()) {
    char command = SerialBT.read();
    if (digitalRead(buttonPin1) == LOW) {
      digitalWrite(redledPin, HIGH); // Turn on LED
    }
    else if (digitalRead(buttonPin3) == LOW) {
      digitalWrite(redledPin, LOW); // Turn off LED
    }
    else if (digitalRead(buttonPin2) == LOW) {
      // Read the brightness level from master
      while (!SerialBT.available()) {
        delay(10);
      }
      brightness = SerialBT.parseInt();
      brightness = constrain(brightness, 0, 255); // Limit brightness to 0-255
      
      analogWrite(redledPin, brightness); // Set LED brightness
    }
  }
}
