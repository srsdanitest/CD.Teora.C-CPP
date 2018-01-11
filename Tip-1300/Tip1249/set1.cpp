#ifdef __BCPLUSPLUS__
#include <set.h>
#else
#include <set>
#endif

#include <iostream.h>

using namespace std;
class ltstr
 {
  public:
    bool operator()(const char* s1, const char* s2) const
      { return (strcmp(s1, s2) < 0);}
 };

void main(void)
 {
   const int N = 6;
   const char* a[N] = {"aaa", "bbb", "ccc", "ddd", "eee", "fff"};
   const char* b[N] = {"ggg", "hhh", "eee", "iii", "ccc", "aaa"};

   set<const char*, ltstr> A(a, a + N);
   set<const char*, ltstr> B(b, b + N);
   set<const char*, ltstr> C;
   cout << "Set A: ";
   copy(A.begin(), A.end(), ostream_iterator<const char*>(cout, " "));
   cout << endl;
   cout << "Set B: ";
   copy(B.begin(), B.end(), ostream_iterator<const char*>(cout, " "));   
   cout << endl;
   cout << "Union: ";
   set_union(A.begin(), A.end(), B.begin(), B.end(),
            ostream_iterator<const char*>(cout, " "), ltstr());   
   cout << endl;
   cout << "Intersection: ";
   set_intersection(A.begin(), A.end(), B.begin(), B.end(),
                    ostream_iterator<const char*>(cout, " "), ltstr());    
   cout << endl;
   set_difference(A.begin(), A.end(), B.begin(), B.end(),inserter(C, C.begin()),
                  ltstr());
   cout << "Set C (difference of A and B): ";
   copy(C.begin(), C.end(), ostream_iterator<const char*>(cout, " "));
   cout << endl;
 }

