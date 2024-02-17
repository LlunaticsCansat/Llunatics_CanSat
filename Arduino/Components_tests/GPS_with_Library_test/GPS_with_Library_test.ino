// TinyGPSPlus - Version: Latest 
#include <TinyGPS++.h>
#include <TinyGPSPlus.h>

#include <SoftwareSerial.h>

static const int RXPin = 4, TXPin = 3;
static const uint32_t GPSBaud = 9600;

TinyGPSPlus gps;
SoftwareSerial ss(RXPin, TXPin);

float latitude, longitude;

void setup() {
  Serial.begin(115200);
  ss.begin(GPSBaud);
}

void loop() {

  while (ss.available() > 0) {
    gps.encode(ss.read());
    if (gps.location.isValid()) {
      latitude = gps.location.lat();
      longitude = gps.location.lng();

      Serial.print(latitude,6);
      Serial.print(",");
      Serial.println(longitude,6);
      }
    }
  }