#include <SD.h>
#include<Wire.h>
#include<Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>

File dataFile;
Adafruit_BMP280 bmp;

unsigned long countTime = millis();

void setup() {
  Serial.begin(9600);
  Serial.println(F("BMP280 test"));

  if (!bmp.begin()) {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring!"));
    while (1); }

  bmp.begin(0x76);
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Modo de operaciÃ³n */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Presion oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtrado. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Tiempo Standby. */

  if (!SD.begin(9))
  {
    Serial.println(F("Error at startup"));
    return;
  }
  Serial.println(F("Correctly initiated"));
      
  if(!SD.exists("datalog.csv"))
  {
      dataFile = SD.open("datalog.csv", FILE_WRITE);
      if (dataFile) {
        Serial.println("New file, Writing headers(row 1)");
        dataFile.println("Time(ms),Temperature,Pressure");
        dataFile.close();
      } else {
        Serial.println("Error creating the file datalog.csv");
      }
  }
}

void loop() {

  unsigned long currentTime = millis();

  if (currentTime - countTime >= 1000){
    
    dataFile = SD.open("datalog.txt", FILE_WRITE);
    if (dataFile){
        dataFile.print(currentTime);
        dataFile.print(","); 
      
        dataFile.print(bmp.readTemperature());
        dataFile.print(",");
      
        dataFile.println(bmp.readPressure());
      
        dataFile.close();
      
        Serial.println("finish printing");

        countTime = currentTime;

    } else {
      Serial.println("error to open the foulder");
    }
  }

  
}
