int readPin=A0;
int readVal;
float Voltage2;
int halfBreak=500;

void setup() {
  // put your setup code here, to run once:
  pinMode(readPin, INPUT);
  Serial.begin(9600); // printing on screen + baud rate

}

void loop() {
  // put your main code here, to run repeatedly:
  readVal=analogRead(readPin);
  Voltage2=(5./1023.)*readVal; // 5. to avoid int division
  Serial.println(Voltage2); // print line
  delay(halfBreak);
}
