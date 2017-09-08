#include <SimpleLed.h>

SimpleLed led(9);
int mode = 0;
unsigned long last_time = 0;
unsigned long interval = 0;

void setup() {
  Serial.begin(115200);
  led.off();
  ::last_time = millis();
  ::mode = 0;
}

void loop() {
  // put your main code here, to run repeatedly:
  long now = millis();
  led.touch();
  if (now - ::last_time < ::interval) return;
  switch (::mode) {
    case 0:
      led.on();
      Serial.println("ON 2s");
      ::mode = 1;
      ::interval = 2000;
      break;
    case 1:
      led.off();
      Serial.println("OFF 2s");
      ::mode = 2;
      ::interval = 2000;
      break;
    case 2:
      led.flash(500);
      Serial.println("FLASH 500ms");
      ::mode = 3;
      ::interval = 2000;
      break;
    case 3:
      led.blink(250);
      Serial.println("BLINK 10s EACH 250ms");
      ::mode = 4;
      ::interval = 10000;
      break;
    case 4:
      led.off();
      led.set_value(0);
      Serial.print("FADE IN ... ");
      led.on();
      for (int i = 1; i <= 255; i++) {
        led.set_value(i);
        delay(10);
      }
      Serial.println("OK");
      ::mode = 5;
      ::interval = 0;
      break;
    case 5:
      Serial.print("FADE OUT ... ");
      led.set_value(255);
      led.on();
      for (int i = 254; i > 0; i--) {
        led.set_value(i);
        delay(10);
      }
      led.off();
      led.set_value(255);
      Serial.println("OK");
      ::mode = 0;
      ::interval = 0;
      break;
  }
  ::last_time = now;
}