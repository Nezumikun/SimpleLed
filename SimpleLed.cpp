#include <Arduino.h>
#include "SimpleLed.h"
#include "pins_arduino.h"

SimpleLed::SimpleLed(int pin) {
  this->init(pin, 255);
}

SimpleLed::SimpleLed(int pin, int pwm_value) {
  this->init(pin, pwm_value);
}

void SimpleLed::init(int pin, int pwm_value) {
  this->pin_number = pin;
  this->pwm_value = (pwm_value > 255) ? 255 : pwm_value;
  this->pwm_available = (digitalPinToTimer(pin) != NOT_ON_TIMER);
  pinMode(this->pin_number, OUTPUT);
  this->off();
}

void SimpleLed::update() {
  if (this->state == LOW) {
    digitalWrite(this->pin_number, LOW);
	return;
  }
  if (this->pwm_available && (this->state == HIGH)) {
    analogWrite(this->pin_number, this->pwm_value);
  }
  else {
    digitalWrite(this->pin_number, HIGH);
  }
}

void SimpleLed::on() {
  this->mode = SIMPLELED_ON;
  this->state = HIGH;
  this->update();
}

int SimpleLed::get_value() {
  return this->pwm_value;
}

void SimpleLed::set_value(int pwm_value) {
  this->pwm_value = pwm_value;
  this->update();
}

void SimpleLed::off() {
  this->mode = SIMPLELED_OFF;
  this->state = LOW;
  this->update();
}

bool SimpleLed::is_on() {
  return (this->state == HIGH);
}

void SimpleLed::blink(unsigned int interval) {
  this->mode = SIMPLELED_BLINK;
  this->interval = interval;
  this->state = (this->state == HIGH) ? LOW : HIGH;
  this->time = millis();
  this->update();
}

void SimpleLed::flash(unsigned int interval) {
  this->mode = SIMPLELED_FLASH;
  this->interval = interval;
  this->state = HIGH;
  this->time = millis();
  this->update();
}

void SimpleLed::touch() {
  if ((this->mode != SIMPLELED_BLINK) && (this->mode != SIMPLELED_FLASH)) {
    return;
  }
  unsigned long now = millis();
  if (now - this->time >= this->interval) {
    if (this->mode == SIMPLELED_FLASH) {
      this->state = LOW;
      this->mode = SIMPLELED_OFF;
      this->update();
      return;
    }
    this->state = (this->state == HIGH) ? LOW : HIGH;
    this->time = now;
    this->update();
  }
}
