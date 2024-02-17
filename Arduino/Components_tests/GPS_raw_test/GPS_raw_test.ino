#include <SoftwareSerial.h>

const int RX = 4;
const int TX = 3;

SoftwareSerial gps(RX, TX);

void setup()
{
  Serial.begin(115200);
  gps.begin(9600);
}

void loop()
{
  if (gps.available())
  {
    char data;
    data = gps.read();
    Serial.print(data);
  }else{
    Serial.println("No data")
  }
}
