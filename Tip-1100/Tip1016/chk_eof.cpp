#include <iostream.h>
#include <fstream.h>
#include <ctype.h>
#include <iomanip.h>
#include <stdio.h>

int main(int argc, char *argv[])
 {
   if(argc!=2)
    {
      cout << "Usage: chk_eof <filename>" << endl;
      exit (1);
    }
   ifstream in(argv[1], ios::in | ios::binary);
   if(!in)
    {
      cout << "Cannot open input file." << endl;
      exit (1);
    }

   register int i, j;
   int count = 0;
   char c[16];

   cout.setf(ios::uppercase);
   while(!in.eof())
    {
      for(i=0; i<16 && !in.eof(); i++)
         in.get(c[i]);
      if(i<16)
         i--;
      for(j=0; j < i; j++)
         cout << setw(3) << hex << (int) c[j];
      for(; j < 16; j++)
         cout << "  ";
      cout << "\t";
      for(j=0; j < i; j++)
         if(isprint(c[j]))
            cout << c[j];
         else
            cout << ".";
      cout << endl;
      count ++;
      if(count==16)
       {
         count = 0;
         cout << "Press ENTER to continue: ";
         cin.get();
         cout << endl;
       }
    }
   in.close();
 }






