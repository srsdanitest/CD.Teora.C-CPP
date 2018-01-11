#include <iostream.h>

class amount;

class coins 
{
   enum units {penny, nickel, dime, quarter, half_dollar};
   friend amount;
};

class amount 
{
   coins::units money;
 public:
   void setm(void);
   int getm(void);
 } object;

void amount::setm(void)
 {
   money = coins::dime;
 }

int amount::getm(void)
 {
   return money;
 }

void main(void)
 {
   
   object.setm();
   cout << object.getm();
   
 }


