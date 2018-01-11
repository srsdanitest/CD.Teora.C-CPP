#include <iostream.h>
#define ARR_SIZE 100

class stack 
{
   int stck[ARR_SIZE];
   int stack_top;
 public:
 	stack();
   ~stack();
   void push(int i);
   int pop();
 };

stack::stack(void)
 {
 	stack_top = 0;
   cout << "Stack Initialized" << endl;
 }

stack::~stack(void)
 {
 	cout << "Stack Destroyed" << endl;
 }

void stack::push(int i)
 {
 	if (stack_top==ARR_SIZE)
    {
    	cout << "Stack is full." << endl;
      return;
    }
   stck[stack_top] = i;
   stack_top++;
 }

int stack::pop(void)
 {
 	if (stack_top==0)
    {
    	cout << "Stack underflow." << endl;
      return 0;
    }
   stack_top--;
   return stck[stack_top];
 }

void main(void)
 {
 	stack obj1, obj2;

   obj1.push(1);
   obj2.push(2);
   obj1.push(3);
   obj2.push(4);
   cout << obj1.pop() << endl;
   cout << obj1.pop() << endl;
   cout << obj2.pop() << endl;
   cout << obj2.pop() << endl;
 }
 

