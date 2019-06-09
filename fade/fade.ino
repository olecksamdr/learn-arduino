const int LED = 9;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED as an output.
  pinMode(LED, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {

  for (int i = 0; i <= 255; i++) {
    analogWrite(LED, i);
    delay(10);
  }

  for (int i = 255; i >= 0; i--) {
    analogWrite(LED, i);
    delay(10);
  }
}
