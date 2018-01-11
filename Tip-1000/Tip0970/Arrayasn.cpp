#include <iostream.h>
#include <string.h>

class Employee 
{
  public:
    Employee(void); 
    void show_employee(void) { cout << name << endl; };

  private:
    char name[256];
    long id;
 }; 

Employee::Employee(void)
 {
   static int index = 0;

   switch (index++) {
     case 0: strcpy(Employee::name, "Kris"); 
             Employee::id = 1;
             break;
     case 1: strcpy(Employee::name, "Happy");
             Employee::id = 2;
             break;
     };
 }

 void main(void)
  {
    Employee workers[2]; 

    workers[0].show_employee(); 
    workers[1].show_employee();
  }



