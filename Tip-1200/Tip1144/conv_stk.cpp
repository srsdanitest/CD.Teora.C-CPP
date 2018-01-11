#include <iostream.h>

const int SIZE=100;

class stack {
   int stck[SIZE];
   int tos;
 public:
   stack(void) {tos=0;}
   void push(int i);
   int pop(void);
   operator int(void) {return tos;}        // converts stack to int
 };

void stack::push(int i)
 {
   if(tos==SIZE)
    {
      cout << "Stack is full." << endl;
      return;
    }
   stck[tos++] = i;
}

int stack::pop(void)
 {
   if(tos==0)
    {
      cout << "Stack underrun." << endl;
      return 0;
    }
    
    return stck[--tos];
 }

void main(void)
 {
   stack stck;
   int i, j;

   for(i=0; i<20; i++)
      stck.push(i);
   j = stck;                  // convert to integer
   cout << j << " items on stack." << endl;
   cout << (SIZE - stck) << " spaces open." << endl;
   
 }


