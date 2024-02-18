# Llunatics

Llunatics is a CanSat, a mini satellite that is the size of a can, designed and developed by a team formed by students of first baccalaureate in Catalonia participating in the [Esero CanSat competition](https://esero.es/cansat-2/).

The team is constructed by 5 members, each one focused on the diferent aspects of the project.

# Components

The microcontroller for our CanSat is an Arduino Nano Every, because it have more Flash memory and Ram memory than classic Arduinos, it is necessary to compile our program.

## Sensors
| Component Name | Arduino Pin                  | Module Pin                     |
|----------------|------------------------------|--------------------------------|
| APC220         | [5V, GND, D6(RX), D7(TX)]    | [VCC, GND, TXD, RXD]           |
| BMP280         | [3V3, GND, A5, A4]           | [VCC, GND, SCL, SDA]           |
| MPU9250        | [3V3, GND, A5, A4]           | [VCC, GND, SCL, SDA]           |
| NEO-6M GPS     | [5V, GND, RX0, TX1]          | [VCC, GND, TX, RX]             |
| ACS712         | [5V, GND, A1]                | [VCC, GND, OUT]                |
| LDR sensor     | [5V, GND, A0]                |                                |
| SD Card Reader | [5V, GND, D13, D12, D11, D9] | [5V, GND, SCK, MISO, MOSI, C9] |

# Variables/Datas

| Name                  | Format        | Source                    | Quantity              |
|-----------------------|---------------|---------------------------|-----------------------|
| time                  | Unsigned Long | Arduino Power-on Timer    | ms                    |
| temperature           | Float         | BMP280                    | ºC                    |
| pressure              | Float         | BMP280                    | pa                    |
| accelerationX         | Float         | MPU9250                   | g forces              |
| accelerationY         | Float         | MPU9250                   | g forces              |
| accelerationZ         | Float         | MPU9250                   | g forces              |
| velocityRotationX     | Float         | MPU9250                   | degrees/second        |
| velocityRotationX     | Float         | MPU9250                   | degrees/second        |
| velocityRotationZ     | Float         | MPU9250                   | degrees/second        |
| magneticFieldX        | Float         | MPU9250                   | µT                    |
| magneticFieldX        | Float         | MPU9250                   | µT                    | 
| magneticFieldZ        | Float         | MPU9250                   | µT                    | 
| Yaw                   | Float         | MPU9250                   | degrees               |
| Pitch                 | Float        | MPU9250                   | degrees               |
| Roll                  | Float        | MPU9250                   | degrees               |
| mpuTemperature        | Float         | MPU9250                   | ºC                    |
| latitude              | Float         | NEO-6M GPS                | GCS in degrees        |
| longitude             | Float         | NEO-6M GPS                | GCS in degrees        |
| rectennaIntensity     | Float         | ACS712                    | A                     |
| rectennaVoltage       | Float         | Arduino analog Pin        | V                     | 
| cansatBrightness      | Float         | LDR sensor                | index between 0~1023  |

# Progress

Ground station GUI is not yet complete
