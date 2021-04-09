void setup() {
  //Test 1: with simple digital write
  //Connect heater with pin 13
  //pinMode(3,OUTPUT);

  //Test 2: PWM write
  //Connect heater with pin 3 and pin 11
  pinMode(3, OUTPUT);
  pinMode(11, OUTPUT);
  TCCR2A = _BV(COM2A1) | _BV(COM2B1) | _BV(WGM21) | _BV(WGM20);
  TCCR2B = _BV(CS22);
  OCR2A = 180;
  OCR2B = 50;
}

void loop() {
  //Test 1
  //digitalWrite(13, HIGH);
  //delayMicroseconds(100); // Approximately 10% duty cycle @ 1KHz
  //digitalWrite(13, LOW);
  //delayMicroseconds(1000 - 100);
}
