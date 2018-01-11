#include <iostream.h>

void clrscr(int size=25)
 {
   while(size > 0)
    {
      cout << endl;
      size--;
    }
 }

void main(void)
 {
   int i;

   for(i=0; i<30; i++)
      cout << i << endl;
   cin.get();
   clrscr();                  // clears 25 lines
   for(i=0; i<30; i++)
      cout << i << endl;
   cin.get();
   clrscr(10);                  // clears 10 lines
 }
