/*
  BMP connection:
  
  VCC: Arduino 3.3V
  GND: Arduino GND
  SCL: Arduino A5
  SDA: Arduino A4
*/




#include<Wire.h>
#include<Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>



Adafruit_BMP280 bmp;

void setup() {
  Serial.begin(9600);
  Serial.println(F("BMP280 test"));
  if (!bmp.begin()) {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring!"));
    while (1); }

  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Modo de operaciÃ³n */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Presion oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtrado. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Tiempo Standby. */
}

void loop() 
{
    Serial.print(F("Temperature = "));
    Serial.print(bmp.readTemperature());
    Serial.println(" *C");

    Serial.print(F("Pressure = "));
    Serial.print(bmp.readPressure());
    Serial.println(" Pa");

    Serial.print(F("Altitude = "));
    Serial.print(bmp.readAltitude(1013.25));
    Serial.println(" m");

    Serial.println();
    delay(1000);
}