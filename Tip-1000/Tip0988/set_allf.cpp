#include <iostream.h>

void showflags(void);

void main(void)
 {
   showflags();
   long f = ios::showpos | ios::showbase | ios::oct | ios::right;
   cout.flags(f);
   showflags();
 }

void showflags(void)
 {
   long flag_set, i;
   int j;
   char flags[15][12] = {
      "skipws", "left", "right", "internal", "dec",
      "oct", "hex", "showbase", "showpoint", "uppercase",
      "showpos", "scientific", "fixed", "unitbuf",
   };

   flag_set = cout.flags();
   for (i=1, j=0; i<0x2000; i = i<<1, j++)
      if (i & flag_set)
         cout << flags[j] << " is on." << endl;
      else
         cout << flags[j] << " is off." << endl;
   cout << endl;
 }
