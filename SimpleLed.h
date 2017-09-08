#include <Arduino.h>
#ifndef __SIMPLELED__
#define __SIMPLELED__

enum SimpleLedMode { SIMPLELED_ON, SIMPLELED_OFF, SIMPLELED_BLINK, SIMPLELED_FLASH };

class SimpleLed {
  private:
    int               pin_number;
    SimpleLedMode     mode = SIMPLELED_OFF;
    unsigned int      interval = 500;
    unsigned long     time = 0;
    int               state = LOW;
    int               pwm_value = 0xFF;
    bool              pwm_available = false;
    void init(int pin, int pwm_value);
	void update();
  public:
    SimpleLed (int pin);
    SimpleLed (int pin, int pwm_value);
    void on();
    void off();
    int get_value();
    void set_value(int pwm_value);
    void blink(unsigned int interval);
    void flash(unsigned int interval);
    void touch();
}
;

#endif
