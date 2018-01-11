#include <iostream.h>
#include <stdlib.h>
#include <fstream.h>

void main(int argc, char **argv)
 {
   char buffer[1];
   
   ifstream input(argv[1], ios::in);

   if (input.fail())
    {
      cout << "Error opening the file " << argv[1];
      exit(1);
    }

   ofstream output(argv[2], ios::out);

   if (output.fail())
    {
      cout << "Error opening the file " << argv[2];
      exit(1);
    }
 
 
   do {
     input.read(buffer, sizeof(buffer));
     if (input.good())
       output.write(buffer, sizeof(buffer));
   } while (! input.eof());

   input.close();
   output.close(); 
 }




