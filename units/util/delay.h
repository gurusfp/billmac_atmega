
void
_delay_ms(uint16_t ms)
{
  for (; ms; ms--) {
  }
}

#define _delay_us _delay_ms

