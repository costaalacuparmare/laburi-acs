#include <avr/io.h>
#include <util/delay.h>
 
int main() {
  DDRD |= (1 << PD5);

  PORTD |= (1 << PD5);
  PORTD ^= (1 << PD5);

  DDRB &= ~(1 << PB2);
  PORTB |= (1 << PB2);

  while(1) {
    if (!(PINB & (1 << PB2))) {
      DDRD |= (1 << PD7);
      _delay_ms(1000);
      DDRD &= ~(1 << PD5);
      _delay_ms(1000);
      int i = 4;
      while (i) {
        PORTD ^= (1 << PD7);
        _delay_ms(500);
        i--;
      }
      DDRD &= ~ (1 << PD7);
      DDRD |= (1 << PD5);
    }
  }
 
	return 0;
}
