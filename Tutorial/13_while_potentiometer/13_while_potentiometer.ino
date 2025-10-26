int myNumber;
String msg="Please Enter Your Number:";
String msg2="Your Number Is: ";

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
Serial.println(msg);
while (Serial.available()==0) {
}
myNumber=Serial.parseInt();
Serial.print(msg2);
Serial.println(myNumber);
}
