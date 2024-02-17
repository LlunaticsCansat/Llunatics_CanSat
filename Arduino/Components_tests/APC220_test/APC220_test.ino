/*
    APC220 CONECTION:
             RXD: Arduino Pin 8
             TXD: Arduino Pin 9
             GND: Arduino GND
             VCC: Arduino 5V
             
*/

#include <SoftwareSerial.h>

SoftwareSerial radio(8, 9);  //

void setup() {
  Serial.begin(9600);  // Comunication velocity
                       // The velocity of serialport should be
                       // the same than the apc220 module
  Serial.println("USB Serial initialized");
  radio.begin(9600);
  Serial.println("Radio initialized");
}

void loop() {
  radio.println("Radio: Hola Llunatics!");  // Mensaje "Hola mundo"
  Serial.println("USB Serial: Hola Llunatics!");
  delay(1000);  // Retraso de envio cada 1 segundo
}