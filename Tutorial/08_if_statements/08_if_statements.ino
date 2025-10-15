int readPin=A0;
int readVal;
float Voltage2;
int dt = 250;
int redPin = 9;

void setup() {
  // put your setup code here, to run once:
  pinMode(readPin, INPUT);
  Serial.begin(9600); // printing on screen + baud rate
  pinMode(redPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  readVal=analogRead(readPin);
  Voltage2=(5./1023.)*readVal; // 5. to avoid int division
  Serial.print("Potentiometer Voltage is ");
  Serial.println(Voltage2); // print line
  if (Voltage2 > 2.0 && Voltage2 < 3.0) {  // or would be ||, of course
    digitalWrite(redPin, HIGH);
  }
  else {
    digitalWrite(redPin, LOW);
  }
  delay(dt);
}
