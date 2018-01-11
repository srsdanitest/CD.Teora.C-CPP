#ifdef __BCPLUSPLUS__
#include <deque.h>
#else
#include <deque>
#endif
#include <iostream.h>


using namespace std;
typedef deque<char> CHARDEQUE;

void print_contents(CHARDEQUE deque, char*);

void main(void)
 {
   CHARDEQUE  a(3, 'A');		//create a  with  3 A's
   CHARDEQUE  b(4, 'B');		//create b with 4 B's.

   print_contents(a, "a");		//print out the contents
   print_contents(b, "b");
   a.swap(b);				//swap a and b
   print_contents(a, "a");
   print_contents(b, "b");
   a.swap(b);				// swap it back
   print_contents(a, "a");
   print_contents(b, "b");
   a.assign(b.begin(),b.end());	//assign the contents of b to a
   print_contents(a, "a");
   a.assign(b.begin(),b.begin()+2);	//assign the first two items of b to a
   print_contents(a, "a");
   a.assign(3, 'Z');			//assign 3 'Z's to a
   print_contents(a, "a");
 }

//function to print the contents of deque
void print_contents(CHARDEQUE deque, char *name)
 {
   CHARDEQUE::iterator pdeque;

   cout << "The contents of " << name << " : ";
   for(pdeque = deque.begin(); pdeque != deque.end(); pdeque++)
     cout << *pdeque << " ";
   cout<< endl;
 }
