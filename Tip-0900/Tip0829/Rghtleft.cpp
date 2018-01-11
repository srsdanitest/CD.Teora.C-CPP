#include <iostream.h>
#include <iomanip.h>

void main(void)
 {
   int i;

   cout << "Right justification\n";
   for (i = 0; i < 3; i++)
     {
       cout.width(5);
       cout << setiosflags(ios::right) << i;
     }
   
   cout << "\nLeft justification\n";
   for (i = 0; i < 3; i++)
     {
       cout.width(5);
       cout << setiosflags(ios::left) << i;
     }
 }


