#include <iostream.h>
#include <stdlib.h>

class array 
{
   int *p;
   int size;
 public:
   array(int sz) {           // simple constructor
      p = new int[sz];
      if(!p) exit(1);
      size = sz;
    }
   ~array() {delete [] p;}    // destructor
   array(const array &object);// copy constructor
   void put(int i, int j){
      if(i>=0 && i<size)
        p[i] = j;
    }
   int get(int i) {return p[i];}
 };

array::array(const array &object)
 {
   int lcl_i;

   p = new int[object.size];
   if (!p)
      exit(1);
   for(lcl_i=0; lcl_i < object.size; lcl_i++)
      p[lcl_i] = object.p[lcl_i];
 }

void main(void)
 {
   array num(10);
   int lcl_i;

   for (lcl_i=0; lcl_i<10; lcl_i++)
      num.put(lcl_i, lcl_i);
   for (lcl_i=9; lcl_i>=0; lcl_i--)
      cout << num.get(lcl_i);
   cout << endl;

   //  Create another array using the copy constructor
   array x=num;
   for (lcl_i=0; lcl_i<10; lcl_i++)
      cout << x.get(lcl_i);
 }



