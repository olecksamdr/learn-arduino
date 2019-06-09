const int LED = 9;
const int BUTTON = 2;

boolean lastButton = LOW;
boolean currentButton = LOW;
boolean isLedOn = false;

boolean debounce(int pin, boolean last) {
  boolean current = digitalRead(pin);

  if (last != current) {
    delay(5);
    return digitalRead(pin);
  }
}

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(BUTTON, INPUT);
}

void loop() {
  currentButton = debounce(BUTTON, lastButton);

  if (lastButton == LOW && currentButton == HIGH) {
    isLedOn = !isLedOn;
  }

  digitalWrite(LED, isLedOn);
  lastButton = currentButton;
}
