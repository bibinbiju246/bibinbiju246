#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

String name = "ESP32test";//device to connect with
bool connected;

void setup() {
  Serial.begin(115200);
  pinMode(16, OUTPUT); //red dual color led
  pinMode(17, OUTPUT); //green dual color led
  SerialBT.begin("ESP32test_Master", true); //true starts as master
  Serial.println("The device started in master mode, make sure remote BT device is on!");

  connected = SerialBT.connect(name);//connect to "ESP32test"

  delay(5000);//time to connect

  if (connected) {
    Serial.println("Connected Succesfully!");
  }
}

void loop() {

  if (SerialBT.connected())
  {
    digitalWrite(17, LOW);//turn on
    digitalWrite(16, HIGH);//turn off
  }
  else
  {
    digitalWrite(17, HIGH);//turn off
    digitalWrite(16, LOW); //turn on
  }

  if (Serial.available()) {
    SerialBT.write(Serial.read());
  }
  if (SerialBT.available()) {
    Serial.write(SerialBT.read());
  }
  delay(20);
}
