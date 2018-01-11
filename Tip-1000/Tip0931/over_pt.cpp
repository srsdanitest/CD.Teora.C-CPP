#include <iostream.h>

int somef(int a);
int somef(int a, int b);

void main(void)
  {
  int (*fp)(int a);   // pointer to int xxx(int)

  fp = somef;         // points to somef(int)
  cout << fp(5);
  }

int somef(int a)
  {
  return a;
  }

int somef(int a, int b)
  {
  return a*b;
  }


