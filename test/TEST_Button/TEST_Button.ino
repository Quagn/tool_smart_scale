const int button1 = 16;     // the number of the pushbutton pin
const int button2 = 3;     // the number of the pushbutton pin
const int ledPin =  2;       // the number of the LED pin

// variable for storing the pushbutton status
int buttonState = 0;

void setup() {
  Serial.begin(9600);
  // initialize the pushbutton pin as an input
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  // initialize the LED pin as an output
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH
  if (digitalRead(button1) || !digitalRead(button2)) {
    // turn LED on
    Serial.println("On");
    digitalWrite(ledPin, LOW);
  } else {
    // turn LED off
    Serial.println("Off");
    digitalWrite(ledPin, HIGH);
  }
}