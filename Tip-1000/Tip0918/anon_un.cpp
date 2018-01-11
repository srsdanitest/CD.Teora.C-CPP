#include <iostream.h>
#include <string.h>

void main(void)
  {
  // define anonymous union
  union
    {
    long l;
    double d;
    char s[4];
    };

  // now, your program can reference elements directly

  l = 100000;
  cout << l << " ";
  d = 123.2342;
  cout << d << " ";
  strcpy(s, "hi");
  cout << s;
  }
