#include <iostream.h>
#include <string.h>

class Employee 
{
 public:
   Employee(void) {};
   Employee(char *name, char sex, int age, char *phone) 
   {
     strcpy(Employee::name, name);
     Employee::sex = sex;
     Employee::age = age;
     strcpy(Employee::phone, phone); 
   };
     friend ostream &operator<<(ostream &cout, Employee emp);
     friend istream &operator>>(istream &stream, Employee &emp);
 private:
   char name[256];
   char phone[64];
   int age;
   char sex;
};

ostream &operator<<(ostream &cout, Employee emp)
 {
   cout << "Name: " << emp.name << "\tSex: " << emp.sex;
   cout << "\tAge: " << emp.age << "\tPhone: " << emp.phone << endl;
   return cout;
 }


istream &operator>>(istream &stream, Employee &emp)
 {
   cout << "Enter Name: ";
   stream >> emp.name;
   cout << "Enter Sex: ";
   stream >> emp.sex;
   cout << "Enter Age: ";
   stream >> emp.age;
   cout << "Enter Phone: ";
   stream >> emp.phone;
   return stream;
 }

void main(void)
 {
   Employee worker;

   cin >> worker;
   cout << worker ;
 }
