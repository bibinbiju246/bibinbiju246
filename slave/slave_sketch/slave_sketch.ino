#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

const int redledPin = 16; // LED pin
const int controlPin = 4;
//const int buttonPin1 = 19;     // button for LED 1 control
//const int buttonPin2 = 4;     // button for LED 2 control
//const int buttonPin3 = 5;     // button for LED 3 control
//int brightness = 0;

void setup() {
  Serial.begin(115200);
  pinMode(redledPin, OUTPUT);
  pinMode(controlPin,INPUT);
  
  SerialBT.begin("ESP32test", false); // true starts as slave
  Serial.println("The device started in slave mode.");

  while (!SerialBT.connected()) {
    delay(100);
  }
  Serial.println("Connected to master device!");
}

void loop() 

{
  if (digitalRead(controlPin) == HIGH) {
    digitalWrite(redledPin, HIGH); // Turn on LED
  } else {
    digitalWrite(redledPin, LOW); // Turn off LED
  }
  printf("chenges \n");
}
