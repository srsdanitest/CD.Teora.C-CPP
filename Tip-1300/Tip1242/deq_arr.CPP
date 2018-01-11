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
   CHARDEQUE  a;				// create an empty deque a

   if(a.empty())				//check whether it is empty
     cout << "a is empty" << endl;
   else
     cout << "a is not empty" << endl;

   a.push_back('A');				//inset A, B, C and D  to a
   a.push_back('B');
   a.push_back('C');
   a.push_back('D');
   if(a.empty())				//check again whether a is empty
       cout << "a is empty" << endl;
   else
       cout << "a is not empty" << endl;
   print_contents(a,"a");			//print out the contents

   cout << "The first element of a is  " << a[0] << endl;
   cout << "The first element of a is  " << a.at(0) << endl;
   cout << "The last element of a is  " << a[a.size()-1] << endl;
   cout << "The last element of a is  " << a.at(a.size()-1) << endl;
 }

//function to print the contents of deque
void print_contents(CHARDEQUE deque, char *name)
 {
   CHARDEQUE::iterator pdeque;

   cout << "The contents of "<< name << " : ";
   for(pdeque = deque.begin(); pdeque != deque.end(); pdeque++)
     cout << *pdeque <<" ";
   cout << endl;
 }
