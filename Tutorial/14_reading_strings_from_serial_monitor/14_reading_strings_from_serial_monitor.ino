String myName;
String msg="What is you name? ";
String msg2="Hello ";
String msg3=", welcome to Arduino!";

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
Serial.println(msg);
while (Serial.available()==0){

}
myName=Serial.readString();
Serial.print(msg2);
Serial.print(myName);
Serial.println(msg3);
}
