#include "ClickEncoder.h"
#include "TimerOne.h"

const int i_set_pin = 5;
const int fan_set_pin = 6;

ClickEncoder *encoder;
int16_t last, value;
char tempstring[10];

/** 
 *  Timer One ISR
 */
void timerIsr() {
  encoder->service();
}

void setup() {
  Serial.begin(9600);
  delay(500);

  Serial.write(254); // cursor to beginning of first line
  Serial.write(128);

  Serial.write("Level: ");
  
  // Setup fast PWM on i set and fan set pins
  pinMode(i_set_pin, OUTPUT);
  pinMode(fan_set_pin, OUTPUT);

  encoder = new ClickEncoder(A1, A0, A2);

  Timer1.initialize(1000);
  Timer1.attachInterrupt(timerIsr); 
}

void loop() {
  value += encoder->getValue();

  if (value != last) {
      last = value;

      analogWrite(i_set_pin, value);

      sprintf(tempstring, "%3d", value);
      Serial.write(254); // cursor to 7th position on first line
      Serial.write(134);
      Serial.write(tempstring);
  }
}

