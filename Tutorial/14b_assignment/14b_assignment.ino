// Assignment: ask user which light of 3 he wants to light up. Do it.

int redPin = 9;
int greenPin = 10;
int bluePin = 11;
String response;
String msg = "Which LED do you want to turn on? Blue, Red or Green? ";
String errorMsg = "Error. All lights turning off.";
String redMsg = "Acknowledged. Red light turning on.";
String greenMsg = "Acknowledged. Green light turning on.";
String blueMsg = "Acknowledged. Blue light turning on.";
String allMsg = "Cheeky. All lights on!";
String noneMsg = "Roger that. Lights off!";

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(redPin, OUTPUT);
pinMode(greenPin, OUTPUT);
pinMode(bluePin, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
Serial.println(msg);
while (Serial.available() == 0) {
}

response=Serial.readString();
response.trim(); // NOTE: will remove leading/tailing spaces or newlines
response.toLowerCase(); // Convert user input to lowercase to avoid not reading rEd, as an example
// We could have, of course, used OR (||) but it would be more cumbersome and cover less possibilities

// Red
if (response == "red") {
  Serial.println(redMsg);
  digitalWrite(redPin, HIGH);
  digitalWrite(greenPin, LOW);
  digitalWrite(bluePin, LOW);
} 
// Green
else if (response == "green") {
  Serial.println(greenMsg);
  digitalWrite(redPin, LOW);
  digitalWrite(greenPin, HIGH);
  digitalWrite(bluePin, LOW);
} 
// Blue
else if (response == "blue") {
  Serial.println(blueMsg);
  digitalWrite(redPin, LOW);
  digitalWrite(greenPin, LOW);
  digitalWrite(bluePin, HIGH);
} 
// No lights
else if (response == "none") {
  Serial.println(noneMsg);
  digitalWrite(redPin, LOW);
  digitalWrite(greenPin, LOW);
  digitalWrite(bluePin, LOW);
} 
// All lights
else if (response == "all") {
  Serial.println(allMsg);
  digitalWrite(redPin, HIGH);
  digitalWrite(greenPin, HIGH);
  digitalWrite(bluePin, HIGH);
} else { // bad user input
  Serial.println(errorMsg);
  digitalWrite(redPin, LOW);
  digitalWrite(greenPin, LOW);
  digitalWrite(bluePin, LOW);
}
}
