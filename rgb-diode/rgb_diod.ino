const int R_LED = 9;
const int G_LED = 10;
const int B_LED = 11;

const int BUTTON = 2;

boolean lastButton = LOW;
boolean currentButton = LOW;
int ledMode = 0;

boolean debounce(int pin, boolean last) {
  boolean current = digitalRead(pin);

  if (last != current) {
    delay(5);
    return digitalRead(pin);
  }
}

// todo: random color generation
void setMode(int mode) {
  switch(mode) {
    case 1:
      // red
      digitalWrite(R_LED, HIGH);
      digitalWrite(G_LED, LOW);
      digitalWrite(B_LED, LOW);
      break;
    case 2:
      // green
      digitalWrite(R_LED, LOW);
      digitalWrite(G_LED, HIGH);
      digitalWrite(B_LED, LOW);
      break;
    case 3:
      // blue
      digitalWrite(R_LED, LOW);
      digitalWrite(G_LED, LOW);
      digitalWrite(B_LED, HIGH);
      break;
    case 4:
      // purpule
      analogWrite(R_LED, 127);
      analogWrite(G_LED, 0);
      analogWrite(B_LED, 127);
      break;
    case 5:
      analogWrite(R_LED, 0);
      analogWrite(G_LED, 127);
      analogWrite(B_LED, 127);
      break;
    case 6:
      analogWrite(R_LED, 127);
      analogWrite(G_LED, 127);
      analogWrite(B_LED, 0);
      break;
    case 7:
      // white
      analogWrite(R_LED, 85);
      analogWrite(G_LED, 85);
      analogWrite(B_LED, 85);
      break;
    default:
      digitalWrite(R_LED, LOW);
      digitalWrite(G_LED, LOW);
      digitalWrite(B_LED, LOW);
  }
}

void setup() {
  pinMode(R_LED, OUTPUT);
  pinMode(G_LED, OUTPUT);
  pinMode(B_LED, OUTPUT);

  pinMode(BUTTON, INPUT);
}

void loop() {
  currentButton = debounce(BUTTON, lastButton);

  if (lastButton == LOW && currentButton == HIGH) {
    ledMode = ledMode < 7 ? ledMode + 1 : 0;
  }

  setMode(ledMode);
  lastButton = currentButton;
}
