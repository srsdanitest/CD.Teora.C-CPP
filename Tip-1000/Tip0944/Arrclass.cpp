#include <iostream.h>

class Employee 
{
  public:
    Employee(void) { cout << "Constructing an instance\n"; };
    void show_employee(void) { cout << name; };

  private:
    char name[256];
    long id;
 };

 void main(void)
  {
    Employee workers[5];

    // Other statements here
  }



