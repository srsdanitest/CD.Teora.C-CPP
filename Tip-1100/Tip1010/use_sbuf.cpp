// Operations with streambufs.
#include <iostream.h>
#include <fstream.h>

void main(void)
 {
   int c;
   const char *filename = "_junk_.$$$";
   ofstream outfile;
   streambuf *out, *input = cin.rdbuf();

   // Position at the end of file. Append all text.
   outfile.open( filename, ios::ate | ios::app);
   if (!outfile) 
    {
      cerr << "Could not open " << filename;
      return(-1);
    }

   out = outfile.rdbuf();  // Connect ofstream and streambuf.

   clog << "Input some text. Use Control-Z to end." << endl;
   while ( (c = input -> sbumpc() ) != EOF)
    {
      cout << char(c);                         // Echo to screen.
      if (out -> sputc(c) == EOF)
         cerr << "Output error";
      }
 }
