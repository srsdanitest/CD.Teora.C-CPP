#include <iostream.h>
#include <strstrea.h>

void main(void)
 {
   char title[64], publisher[64], author[64];

   ostrstream title_str(title, sizeof(title));
   ostrstream pub_str(publisher, sizeof(publisher));
   ostrstream author_str(author, sizeof(author));

   title_str << "Jamsa's C/C++ Programmer's Bible" << ends;
   pub_str << "Jamsa Press" << ends;
   author_str << "Jamsa and Klander" << ends;

   cout << "Book: " << title << " Publisher: " << publisher << " Author: " <<
      author << endl;
 }


   
