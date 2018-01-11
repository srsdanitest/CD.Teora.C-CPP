#include <iostream.h>

void show_values(int one = 1, int two = 2, int three = 3)
 {
   cout << one << ' ' << two << ' ' << three << '\n';
 }

                                                    
void main(void)
 {
   show_values(1, 2, 3);   
   show_values(100, 200);
   show_values(1000);
   show_values();
 }

