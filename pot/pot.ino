const int POT = 0;

int val;

void setup() {
  Serial.begin(9600);
}

void loop() {
  val = analogRead(POT);

  Serial.print(val);
  Serial.print(" = ");
  Serial.print(5.0 / 1023.0 * val);
  Serial.print("V\n");

  delay(200);
}
