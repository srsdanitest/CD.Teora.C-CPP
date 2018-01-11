#include <iostream.h>

union swap_byte
  {
  void swap(void);
  void set_byte(unsigned i);
  void show_word(void);

  unsigned u;
  unsigned char c[2];
  };

void swap_byte::swap()
  {
  unsigned char t;

  t = c[0];
  c[0] = c[1];
  c[1] = t;
  }

void swap_byte::show_word()
  {
  cout << u;
  }

void swap_byte::set_byte(unsigned i)
  {
  u = i;
  }

void main(void)
  {
  swap_byte b;

  b.set_byte(49034);
  b.swap();
  b.show_word();
  }
