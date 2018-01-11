#include <iostream.h>

ostream& attention(ostream& cout) 
{
 return(cout << '\a');
};

void main(void)
 {
   cout << attention << "The boss is coming to your office...\n";
 }
