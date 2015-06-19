int ledPin = 2;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); 
  Serial.print("Alive\n");
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(ledPin, HIGH);
  Serial.print("LED ON\n");
  delay(500);
  digitalWrite(ledPin, LOW);
  Serial.print("LED OFF\n");  
  delay(500);
}

