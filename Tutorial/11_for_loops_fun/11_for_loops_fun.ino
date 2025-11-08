int i;         // counter
int pause = 500;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  }

void loop() {
  // put your main code here, to run repeatedly:
  for (i = 1; i <= 10; i++) {
    if (i % 2 == 0) { // Print even numbers
      Serial.println(i);
    }
    delay(pause);
  }
  Serial.println();
}
