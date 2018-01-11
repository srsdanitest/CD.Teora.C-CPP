#include <iostream.h>
#include <fstream.h>

void main(int argc, char *argv[])
 {
   if(argc!=2)
    {
      cout << "Usage: PR <filename>" << endl;
      exit (1);
    }
   ifstream in(argv[1]);
   if(!in)
    {
      cout << "Cannot open file.";
      exit (1);
    }
   char str[255];
   while(in)
    {
      in.getline(str, 255);      // Delimiter defaults to newline
      cout << str << endl;
    }
   in.close();
 }


