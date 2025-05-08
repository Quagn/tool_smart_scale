void button_setup() {
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
}

void button_read() {
  digitalRead(button1);
  digitalRead(button2);
}
