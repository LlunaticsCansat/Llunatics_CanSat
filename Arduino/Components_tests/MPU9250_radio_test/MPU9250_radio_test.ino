#include "MPU9250.h"
#include <SoftwareSerial.h>  

unsigned long countTime = millis();

struct SensorData {               //Create a struct that contains all the dates
    unsigned long time = NAN;
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
    float mpuTemperature = NAN;
};

MPU9250 mpu;

SoftwareSerial radio(7, 6);

void setup() {
    radio.begin(9600);
    Wire.begin();

    if (!mpu.setup(0x68)) {  // change to your own address
        while (1) {
            radio.println("MPU connection failed. Please check your connection with `connection_check` example.");
            delay(5000);
        }
    }
}


void loop() {
  unsigned long currentTime = millis();
  float AccX, AccY, AccZ, GyroX, GyroY, GyroZ, MagX, MagY, MagZ, Yaw, Pitch, Roll, MpuTemp;

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
    MpuTemp = mpu.getTemperature();
    }

  if (currentTime - countTime >= 1000){   
    SensorData currentSensorData = CollectSensorData(currentTime, AccX, AccY, AccZ, GyroX, GyroY, GyroZ, MagX, MagY, MagZ, Yaw, Pitch, Roll, MpuTemp);
    sendData(currentSensorData);
    countTime = currentTime;
  }
}

SensorData CollectSensorData(unsigned long currentTime, float AccX, float AccY, float AccZ, float GyroX, float GyroY, float GyroZ, float MagX, float MagY, float MagZ, float Yaw, float Pitch, float Roll, float MpuTemp) { //Collect dates from the sensors (exept Gps)

    SensorData currentSensorData;

    currentSensorData.time = currentTime; 
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
    currentSensorData.mpuTemperature = MpuTemp;

    return currentSensorData;
}

void sendData(SensorData Data){ //send data to ground station with APC220
  
  radio.print(Data.time);
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

  radio.println(Data.mpuTemperature);
}