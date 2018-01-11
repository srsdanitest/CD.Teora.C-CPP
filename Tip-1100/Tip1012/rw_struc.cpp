#include <iostream.h>
#include <fstream.h>
#include <string.h>

struct status 
{
   char name[80];
   float balance;
   unsigned long account_number;
 };

void main(void)
 {
   struct status acc;

   strcpy(acc.name, "Lars Klander");
   acc.balance = 1234.56;
   acc.account_number = 98765432;
   ofstream outbal("balance.asc", ios::out | ios::binary);
   if(!outbal)
    {
      cout << "Cannot open output file." << endl;
      exit (1);
    }
   outbal.write((unsigned char *) &acc, sizeof(struct status));
   outbal.close();
   ifstream inbal("balance.asc", ios::in | ios::binary);
   if(!inbal)
    {
      cout << "Cannot open file." << endl;
      exit (1);
    }
   inbal.read((unsigned char*) &acc, sizeof(struct status));

   cout << acc.name << endl;
   cout << "Account number: " << acc.account_number << endl;
   cout.precision(2);
   cout.setf(ios::fixed);
   cout << "Balance: $" << acc.balance << endl;
   inbal.close();
 }

