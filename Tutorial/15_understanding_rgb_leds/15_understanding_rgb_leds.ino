// We have an RGB LED, connected. 3 resistors, and respective wires + GND

int redPin = 9; // Using PWM-capable pins
int greenPin = 10;
int bluePin = 11;
String msg = "Olá, Helena. Azul, Vermelho ou Verde... Que cor queres?";
String errorMsg = "Estás bem? Não percebi. Podes repetir?";
String weirdMsg = "Sure, why not?!";
String lightMsg = "Let there be light!";
String myColor;
int rest = 1000;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(redPin, OUTPUT);
pinMode(greenPin, OUTPUT);
pinMode(bluePin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(rest);
Serial.println(msg);
while (Serial.available() == 0){
}
myColor = Serial.readString();
myColor.trim();
myColor.toLowerCase();

if (myColor == "vermelho") {
  Serial.println(lightMsg);
  digitalWrite(redPin, HIGH);
  digitalWrite(greenPin, LOW);
  digitalWrite(bluePin, LOW);
}
else if (myColor == "azul") {
  Serial.println(lightMsg);
  digitalWrite(redPin, LOW);
  digitalWrite(greenPin, LOW);
  digitalWrite(bluePin, HIGH);
}
else if (myColor == "verde") {
  Serial.println(lightMsg);
  digitalWrite(redPin, LOW);
  digitalWrite(greenPin, HIGH);
  digitalWrite(bluePin, LOW);
}
else if (myColor == "rosa") {
  Serial.println(weirdMsg);
  // We need analogWrite to introduce variability in the light
  analogWrite(redPin, 255);
  analogWrite(greenPin, 30);
  analogWrite(bluePin, 60);
}
else if (myColor == "roxo") {
  Serial.println(weirdMsg);
  // We need analogWrite to introduce variability in the light
  analogWrite(redPin, 138);
  analogWrite(greenPin, 43);
  analogWrite(bluePin, 180);
}
else {
  Serial.println(errorMsg);
  digitalWrite(redPin, LOW);
  digitalWrite(greenPin, LOW);
  digitalWrite(bluePin, LOW);
}
}



