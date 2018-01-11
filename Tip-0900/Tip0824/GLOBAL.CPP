#include <iostream.h>

int global_name = 1001;

void main(void)
 {
   int global_name = 1;  // Local variable

   cout << "Local variable value " << global_name << '\n';
   cout << "Global variable value " << ::global_name << '\n';
 }
