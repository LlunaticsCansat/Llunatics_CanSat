#include "MPU9250.h"

MPU9250 mpu;

float AccX, AccY, AccZ, GyroX, GyroY, GyroZ, MagX, MagY, MagZ, AngleX, AngleY, AngleZ, Yaw, Pitch, Roll, Temp;

void setup() {
    Serial.begin(115200);
    Wire.begin();

    mpu.setup(0x68);
}

void loop() {
    if (mpu.update()) {

    AccX = mpu.getAccX();
    Serial.print(AccX);
    Serial.print("     ");
    AccY = mpu.getAccY();
    Serial.print(AccY);
    Serial.print("     ");
    AccZ = mpu.getAccZ();
    Serial.print(AccZ);
    Serial.print("     ");
    
    GyroX = mpu.getGyroX();
    Serial.print(GyroX);
    Serial.print("     ");
    GyroY = mpu.getGyroY();
    Serial.print(GyroY);
    Serial.print("     ");
    GyroZ = mpu.getGyroZ();
    Serial.print(GyroZ);
    Serial.print("     ");
    
    MagX = mpu.getMagX();
    Serial.print(MagX);
    Serial.print("     ");
    MagY = mpu.getMagY();
    Serial.print(MagY);
    Serial.print("     ");
    MagZ = mpu.getMagZ();
    Serial.print(MagZ);
    Serial.print("     ");
    
    Yaw = mpu.getYaw();
    Serial.print(Yaw);
    Serial.print("     ");
    Pitch = mpu.getPitch();
    Serial.print(Pitch);
    Serial.print("     ");
    Roll = mpu.getRoll();
    Serial.print(Roll);
    Serial.print("     ");

    Temp = mpu.getTemperature();
    Serial.println(Temp);

    }
}