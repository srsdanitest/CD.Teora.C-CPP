#include <iostream.h>

const int SIZE = 100;

template <class SType> class stack {
   SType stck[SIZE];
   int tos;
 public:
   stack(void);
   ~stack(void);
   void push(SType i);
   SType pop(void);
 };

template <class SType> stack<SType>::stack()
 {
   tos = 0;
   cout << "Stack Initialized." << endl;
 }

template <class SType> stack<SType>::~stack()
 {
   cout << "Stack Destroyed." << endl;
 }

template <class SType> void stack<SType>::push(SType i)
 {
   if(tos==SIZE)
    {
      cout << "Stack is full." << endl;
      return;
    }
   stck[tos++] = i;
 }
template <class SType> SType stack<SType>::pop(void)
 {
   if(tos==0)
    {
      cout << "Stack underflow." << endl;
      return 0;
    }
   return stck[--tos];
 }

void main(void)
 {
   stack<int> a;
   stack<double> b;
   stack<char> c;
   int i;

   a.push(1);
   a.push(2);
   b.push(99.3);
   b.push(-12.23);

   cout << a.pop() << " ";
   cout << a.pop() << " ";
   cout << b.pop() << " ";
   cout << b.pop() << endl;

   for(i=0; i<10; i++)
      c.push((char) 'A' + i);
   for(i=0; i<10; i++)
      cout << c.pop();
   cout << endl;
 }
