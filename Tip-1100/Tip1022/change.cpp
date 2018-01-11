#include <iostream.h>
#include <fstream.h>
#include <stdlib.h>

void main(int argc, char *argv[])
 {
   if(argc!=4)
    {
      cout << "Usage: change <filename> <byte> <character>" << endl;
      exit (1);
    }
   fstream out(argv[1], ios::in | ios::out | ios::binary);
   if(!out)
    {
      cout << "Cannot open file!";
      exit (1);
    }
   out.seekp(atoi(argv[2]), ios::beg);
   out.put(*argv[3]);
   out.close();
 }
