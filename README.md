# Llunatics

Llunatics is a CanSat, a mini satellite that is the size of a can, designed and developed by a team formed by students of first baccalaureate in Catalonia participating in the [Esero CanSat competition](https://esero.es/cansat-2/).

The team is constructed by 5 members, each one focused on the diferent aspects of the project.

Our [Twitter](https://twitter.com/CansatLlunatics)

Our [Web Site](http://llunatics.cat/)

# Components

The microcontroller for our CanSat is an Arduino Nano Every. Because it has more Flash memory and RAM memory than a classic Arduino's, it is necessary to compile our program.

## Sensors
| Component Name | Arduino Pin                  | Module Pin                     |
|----------------|------------------------------|--------------------------------|
| APC220         | [5V, GND, D6(RX), D7(TX)]    | [VCC, GND, TXD, RXD]           |
| BMP280         | [3V3, GND, A5, A4]           | [VCC, GND, SCL, SDA]           |
| MPU9250        | [3V3, GND, A5, A4]           | [VCC, GND, SCL, SDA]           |
| NEO-6M GPS     | [5V, GND, RX0, TX1]          | [VCC, GND, TX, RX]             |
| LDR sensor     | [5V, GND, A0]                |                                |
| Buzzer         | [GND, D8]                    |                                |
| SD Card Reader | [5V, GND, D13, D12, D11, D9] | [5V, GND, SCK, MISO, MOSI, CS] |

# Variables/Datas

| Name                  | Format        | Source                    | Quantity              |
|-----------------------|---------------|---------------------------|-----------------------|
| time                  | Unsigned Long | Arduino Power-on Timer    | ms                    |
| temperature           | Float         | BMP280                    | ºC                    |
| pressure              | Float         | BMP280                    | pa                    |
| altitude              | Float         | BMP280                    | m                     |
| accelerationX         | Float         | MPU9250                   | g forces              |
| accelerationY         | Float         | MPU9250                   | g forces              |
| accelerationZ         | Float         | MPU9250                   | g forces              |
| velocityRotationX     | Float         | MPU9250                   | degrees/second        |
| velocityRotationY     | Float         | MPU9250                   | degrees/second        |
| velocityRotationZ     | Float         | MPU9250                   | degrees/second        |
| magneticFieldX        | Float         | MPU9250                   | µT                    |
| magneticFieldY        | Float         | MPU9250                   | µT                    | 
| magneticFieldZ        | Float         | MPU9250                   | µT                    | 
| Yaw                   | Float         | MPU9250                   | degrees               |
| Pitch                 | Float         | MPU9250                   | degrees               |
| Roll                  | Float         | MPU9250                   | degrees               |
| latitude              | Float         | NEO-6M GPS                | GCS in degrees        |
| longitude             | Float         | NEO-6M GPS                | GCS in degrees        |
| rectennaVoltage       | Float         | Arduino analog Pin        | V                     | 
| cansatBrightness      | Float         | LDR sensor                | index between 0~1023  |

# Progress

Ground station GUI is not yet complete
