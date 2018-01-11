#ifdef __BCPLUSPLUS__
#include <deque.h>
#else
#include <deque>
#endif

#include <iostream.h>


using namespace std;
typedef deque<char >  CHARDEQUE;
void print_contents (CHARDEQUE deque, char*);

void main(void)
 {
   CHARDEQUE  a;				//create a  with  A, B, C and D

   a.push_back('A');
   a.push_back('B');
   a.push_back('C');
   a.push_back('D');
   print_contents (a,"a");			//print out the contents
   cout << "max_size of a is " << a.max_size() << endl;
   cout << "size of a is " << a.size() << endl;

   // increase the size to 10 and set the new elements to be 'X'
   a.resize(10,'X');
   print_contents (a,"a");
   cout << "size of a is " << a.size() << endl;
   a.resize(5);				// resize it to 5
   print_contents (a,"a");
   cout << "size of a is " <<a.size() << endl;
   cout << "max_size of a is still " << a.max_size() << endl;
 }

//function to print the contents of deque
void print_contents (CHARDEQUE  deque, char *name)
 {
   CHARDEQUE::iterator pdeque;

   cout <<"The contents of "<< name <<" : ";
   for(pdeque = deque.begin();pdeque != deque.end();pdeque++)
    {
      cout << *pdeque <<" ";
    }
   cout<< endl;
 }
