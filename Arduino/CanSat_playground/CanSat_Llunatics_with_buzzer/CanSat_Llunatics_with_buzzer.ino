#include <Wire.h>             //For I2C
#include <SoftwareSerial.h> 
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>  //Simplifies BMP280 temp and barometric lectures
#include <TinyGPS++.h>
#include <TinyGPSPlus.h>       //simplifies GPS lectures
#include <SD.h>               //For the SD module
#include "MPU9250.h"          //Gyroscope, compass and acceleration library

struct SensorData {               //Create a struct that contains all the dates
    unsigned long time = ULONG_MAX;
    float temperature = NAN;
    float pressure = NAN;
    float altitude = NAN;
    float accelerationX = NAN;
    float accelerationY = NAN;
    float accelerationZ = NAN;
    float velocityRotationX = NAN;
    float velocityRotationY = NAN;
    float velocityRotationZ = NAN;
    float magneticFieldX = NAN;
    float magneticFieldY = NAN;
    float magneticFieldZ = NAN;
    float Yaw = NAN;
    float Pitch = NAN;
    float Roll = NAN;
    float latitude = NAN;
    float longitude = NAN;
    float rectennaVoltage = NAN;
    float cansatBrightness = NAN;
};


const int BuzzerPin = 8;
const int RadioRX = 7;
const int RadioTX = 6;
bool buzzerState = false;

TinyGPSPlus gps;

SoftwareSerial radio(RadioRX, RadioTX);


Adafruit_BMP280 bmp;
MPU9250 mpu;

File dataFile;

float latitude = NAN;
float longitude = NAN;
float AccX, AccY, AccZ, GyroX, GyroY, GyroZ, MagX, MagY, MagZ, Yaw, Pitch, Roll;

float lastYaw = 0;
float lastPitch = 0;
float lastRoll = 0;

unsigned long countTime = millis();

void setup() {
  
  Wire.begin();
  Serial1.begin(9600);
  radio.begin(9600);
  radio.println(F("Initialitzating CanSat"));

  pinMode(BuzzerPin,OUTPUT);

  
  bmp.begin(0x76); // BMP280 Pressure and temperature sensor
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */

  mpu.setup(0x68);
  
  if (!SD.begin(9))
  {
    radio.println(F("Error at startup SD"));
    return;
  }
  

}



void loop() {
  
  unsigned long currentTime = millis();

  if (mpu.update()) {
    AccX = mpu.getAccX();
    AccY = mpu.getAccY();
    AccZ = mpu.getAccZ();
    GyroX = mpu.getGyroX();
    GyroY = mpu.getGyroY();
    GyroZ = mpu.getGyroZ();
    MagX = mpu.getMagX();
    MagY = mpu.getMagY();
    MagZ = mpu.getMagZ();
    Yaw = mpu.getYaw();
    Pitch = mpu.getPitch();
    Roll = mpu.getRoll();
    }


  while (Serial1.available() > 0) {
    
    if (gps.encode(Serial1.read())) {
      
      if (gps.location.isValid()) {
        
        latitude = gps.location.lat(); //Get GPS measures
        longitude = gps.location.lng();
        
        }
    }
  }

  if (currentTime - countTime >= 1000){   

    
    SensorData currentSensorData = CollectSensorData(currentTime, latitude, longitude, AccX, AccY, AccZ, GyroX, GyroY, GyroZ, MagX, MagY, MagZ, Yaw, Pitch, Roll);
    backUpData(currentSensorData);
    sendData(currentSensorData);
    countTime = currentTime;
    
    float YawDiff = currentSensorData.Yaw - lastYaw;
    float PitchDiff = currentSensorData.Pitch - lastPitch;
    float RollDiff = currentSensorData.Roll - lastRoll;
    
    lastYaw = currentSensorData.Yaw;
    lastPitch = currentSensorData.Pitch;
    lastRoll = currentSensorData.Roll;
    
    if (currentSensorData.altitude > 100){
      buzzerState = true;
    }
    
    if (buzzerState == true){
      if(((-1 < YawDiff) && (YawDiff < 1)) && ((-1 < PitchDiff) && (PitchDiff < 1)) && ((-1 < RollDiff) && (RollDiff < 1)) ) {
        digitalWrite(BuzzerPin,HIGH);
        }else{
        digitalWrite(BuzzerPin,LOW);
        }
    }

  }

}


SensorData CollectSensorData(unsigned long currentTime, float currentLatidude, float currentLongitude, float AccX, float AccY, float AccZ, float GyroX, float GyroY, float GyroZ, float MagX, float MagY, float MagZ, float Yaw, float Pitch, float Roll) { //Collect dates from the sensors (exept Gps and MPU9250)

    SensorData currentSensorData;

    currentSensorData.time = currentTime; 
    currentSensorData.temperature = bmp.readTemperature(); // BMP280: Temperature
    currentSensorData.pressure = bmp.readPressure(); // BMP280: Pressure
    currentSensorData.altitude = bmp.readAltitude(1013.25);
    currentSensorData.accelerationX = AccX; //MPU9250
    currentSensorData.accelerationY = AccY;
    currentSensorData.accelerationZ = AccZ;
    currentSensorData.velocityRotationX = GyroX;
    currentSensorData.velocityRotationY = GyroY;
    currentSensorData.velocityRotationZ = GyroZ;
    currentSensorData.magneticFieldX = MagX;
    currentSensorData.magneticFieldY = MagY;
    currentSensorData.magneticFieldZ = MagZ;   
    currentSensorData.Yaw = Yaw;
    currentSensorData.Pitch = Pitch;
    currentSensorData.Roll = Roll;
    currentSensorData.latitude = currentLatidude; //GPS
    currentSensorData.longitude = currentLongitude;
    currentSensorData.rectennaVoltage = analogRead(A2) /1023 * 5.0; //Arduino
    currentSensorData.cansatBrightness = analogRead(A0); //Photoresistor

    return currentSensorData;
}


void backUpData(SensorData Backup){   //Writes data into the microSD

  dataFile = SD.open("cansatdata.csv", FILE_WRITE);

  dataFile.print(Backup.time);
  dataFile.print(F(","));
  
  dataFile.print(Backup.temperature);
  dataFile.print(F(","));
  dataFile.print(Backup.pressure);
  dataFile.print(F(","));
  dataFile.print(Backup.altitude);
  dataFile.print(F(","));

  dataFile.print(Backup.accelerationX);
  dataFile.print(F(","));
  dataFile.print(Backup.accelerationY);
  dataFile.print(F(","));
  dataFile.print(Backup.accelerationZ);
  dataFile.print(F(","));

  dataFile.print(Backup.velocityRotationX);
  dataFile.print(F(","));
  dataFile.print(Backup.velocityRotationY);
  dataFile.print(F(","));
  dataFile.print(Backup.velocityRotationZ);  
  dataFile.print(F(","));

  dataFile.print(Backup.magneticFieldX);
  dataFile.print(F(","));
  dataFile.print(Backup.magneticFieldY);
  dataFile.print(F(","));
  dataFile.print(Backup.magneticFieldZ);  
  dataFile.print(F(","));

  dataFile.print(Backup.Yaw);
  dataFile.print(F(","));
  dataFile.print(Backup.Pitch);
  dataFile.print(F(","));
  dataFile.print(Backup.Roll);
  dataFile.print(F(","));

  dataFile.print(Backup.latitude,6);
  dataFile.print(F(","));
  dataFile.print(Backup.longitude,6);
  dataFile.print(F(","));

  dataFile.print(Backup.rectennaVoltage);
  dataFile.print(F(","));

  dataFile.println(Backup.cansatBrightness);

  dataFile.close();
}



void sendData(SensorData Data){ //send data to ground station with APC220
  
  radio.print(F("Llunatics"));
  radio.print(F(","));
  radio.print(Data.time);
  radio.print(F(","));

  radio.print(Data.temperature);
  radio.print(F(","));
  radio.print(Data.pressure);
  radio.print(F(","));
  radio.print(Data.altitude);
  radio.print(F(","));
  
  radio.print(Data.accelerationX);
  radio.print(F(","));
  radio.print(Data.accelerationY);
  radio.print(F(","));
  radio.print(Data.accelerationZ);
  radio.print(F(","));

  radio.print(Data.velocityRotationX);
  radio.print(F(","));
  radio.print(Data.velocityRotationY);
  radio.print(F(","));
  radio.print(Data.velocityRotationZ);  
  radio.print(F(","));

  radio.print(Data.magneticFieldX);
  radio.print(F(","));
  radio.print(Data.magneticFieldY);
  radio.print(F(","));
  radio.print(Data.magneticFieldZ);  
  radio.print(F(","));

  radio.print(Data.Yaw);
  radio.print(F(","));
  radio.print(Data.Pitch);
  radio.print(F(","));
  radio.print(Data.Roll);
  radio.print(F(","));

  radio.print(Data.latitude,6);
  radio.print(F(","));
  radio.print(Data.longitude,6);
  radio.print(F(","));

  radio.print(Data.rectennaVoltage);
  radio.print(F(","));

  radio.println(Data.cansatBrightness);
}