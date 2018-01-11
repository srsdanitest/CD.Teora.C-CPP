#include <iostream.h>

void main(void)
 {
   int age;
   float salary;
   char name[128];

   cout << "Enter your first name age salary: ";
   cin >> &name >> &age >> &salary;
   cout << name << ' ' << age << ' ' << salary;
 }
