#include <iostream.h>
#include <string.h>

class Employee 
{
 public:
   Employee(char *name, char sex, int age, char *phone) {
     strcpy(Employee::name, name);
     Employee::sex = sex;
     Employee::age = age;
     strcpy(Employee::phone, phone);
   };
     friend ostream& operator<< (ostream& cout, Employee emp);
 private:
   char name[256];
   char phone[64];
   int age;
   char sex;
};

ostream& operator<< (ostream& cout, Employee emp)
 { 
   cout << "Name: " << emp.name << "\tSex: " << emp.sex;
   cout << "\tAge: " << emp.age << "\tPhone: " << emp.phone << endl; 
   return cout;
 }

void main(void)
 {
   Employee worker("Happy", 'M', 4, "555-1212");

   cout << worker ;
 }
