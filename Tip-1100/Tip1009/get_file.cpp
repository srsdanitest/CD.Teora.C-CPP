#include <iostream.h>
#include <fstream.h>

int main(int argc, char *argv[])
 {
   char ch;

   if(argc!=2)
    {
      cout << "Usage: PR <filename>" << endl;
      return 1;
    }
   ifstream in(argv[1], ios::in | ios::binary);
   if(!in)
    {
      cout << "Cannot open file.";
      return 1;
    }
   while(in)
    {
      in.get(ch);
      cout << ch;
    }
 }
 

