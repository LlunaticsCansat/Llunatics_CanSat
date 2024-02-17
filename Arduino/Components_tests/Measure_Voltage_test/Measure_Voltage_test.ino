/*

*/
float read;
float volt;

void setup() {
  Serial.begin(9600);
  pinMode(A0,INPUT);  
}

void loop() {
  read = analogRead(A0);
  volt = read /1023 * 5.0;
  Serial.println(volt);  
  delay(1000);
}
