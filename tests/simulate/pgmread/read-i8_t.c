#include <stdlib.h>
#include <avr/pgmspace.h>

#define VAL 0x11

const int8_t data[] PROGMEM = { -VAL, -2 * VAL, -7 * VAL };

int8_t get_val (uint8_t i)
{
  int8_t v = -VAL;
  if (i == 1) v *= 2;
  if (i == 2) v *= 7;
  return v;
}

__attribute__((noinline,noclone))
void test (uint8_t i)
{
  if (pgm_read_i8 (&data[0]) != get_val (0))
    exit (__LINE__);

  if (pgm_read_i8 (&data[i]) != get_val (i))
    exit (__LINE__);
}

int main (void)
{
  test (1);
  test (2);
  return 0;
}
