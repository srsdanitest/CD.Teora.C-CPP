#include <iostream.h>
#include <fstream.h>

void main(void)
 {
   float fnum[4] = {99.75, -34.4, 1776.0, 200.1};
   int i;

   ofstream out("numbers.asc", ios::out | ios::binary);
   if(!out)
    {
      cout << "Cannot open file.";
      exit (1);
    }
   out.write((unsigned char *) &fnum, sizeof(fnum));
   out.close();
   for (i=0; i<4; i++)
      fnum[i] = 0.0;
   ifstream in("numbers.asc", ios::in | ios::binary);
   if(!in)
    {
      cout << "Cannot open file.";
      exit (1);
    }
   in.read((unsigned char *) &fnum, sizeof(fnum));
   cout << in.gcount() << " bytes read." << endl;
   for (i=0; i<4; i++)
      cout << fnum[i] << " ";
   in.close();
 }
 


