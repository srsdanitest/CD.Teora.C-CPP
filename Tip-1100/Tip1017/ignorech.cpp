#include <iostream.h>
#include <fstream.h>

void main(void)
 {
   ifstream in("ignorech.cpp");
   if(!in)
    {
      cout << "Cannot open file." << endl;
      exit (1);
    }
   in.ignore(10, ' ');
   char c;
   while(in)
   {
     in.get(c);
     cout << c;
   }
   in.close();
 }
 

