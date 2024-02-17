/*

*/
// mesure a bettery with ACS712 current and intensity sensor
float SENSIBILITY = 0.066; // Modelo 30A
int SAMPLESNUMBER = 100;

void setup() 
{
  Serial.begin(9600);
}

void printMeasure(String prefix, float value, String postfix)
{
  Serial.print(prefix);
  Serial.print(value, 3);
  Serial.println(postfix);
}

void loop()
{
  float current = getIntensity(SAMPLESNUMBER);
  float currentRMS = 0.707 * current;
  float power = 230.0 * currentRMS;

  printMeasure("Intensidad: ", current, "A ,");
  printMeasure("Irms: ", currentRMS, "A ,");
  printMeasure("Potencia: ", power, "W");
  delay(1000);
}

float getIntensity(int samplesNumber)
{
  float voltage;
  float currentSum = 0;
  for (int i = 0; i < samplesNumber; i++)
  {
    voltage = analogRead(A0) * 5.0 / 1023.0;
    currentSum += (voltage - 2.5) / SENSIBILITY;
  }
  return(currentSum / samplesNumber);
}