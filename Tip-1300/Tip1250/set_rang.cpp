#ifdef __BCPLUSPLUS__
#include <set.h>
#else
#include <set>
#endif

#include <iostream.h>

using namespace std;
typedef set<int, less<int>> SET_INT;

void main(void)
 {
   SET_INT s1;
   SET_INT::iterator i;

   s1.insert(5);
   s1.insert(10);
   s1.insert(15);
   s1.insert(20);
   s1.insert(25);
   cout << "s1 -- starting at s1.lower_bound(12)" << endl;

// prints: 15,20,25
   for (i = s1.lower_bound(12); i != s1.end(); i++)
      cout << "s1 has " << *i << " in its set." << endl;
   cout << "s1 -- starting at s1.lower_bound(15)" << endl;

// prints: 15,20,25
   for (i = s1.lower_bound(15);i != s1.end(); i++)
      cout << "s1 has " << *i << " in its set." << endl;
   cout << "s1 -- starting at s1.upper_bound(12)" << endl;

// prints: 15,20,25
   for (i = s1.upper_bound(12); i != s1.end(); i++)
      cout << "s1 has " << *i << " in its set." << endl;
   cout << "s1 -- starting at s1.upper_bound(15)" << endl;

// prints: 20,25
   for (i = s1.upper_bound(15); i != s1.end(); i++)
     cout << "s1 has " << *i << " in its set." << endl;
   cout << "s1 -- s1.equal_range(12)" << endl;

// does not print anything
   for (i = s1.equal_range(12).first;i != s1.equal_range(12).second; i++)
      cout << "s1 has " << *i << " in its set." << endl;
   cout << "s1 -- s1.equal_range(15)" << endl;

// prints: 15
   for (i = s1.equal_range(15).first;i != s1.equal_range(15).second; i++)
      cout << "s1 has " << *i << " in its set." << endl;
 }
