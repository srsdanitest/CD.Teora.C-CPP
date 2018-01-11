#include <iostream.h>
#include <stdlib.h>

class loc 
{
   int longitude, latitude;
  public:
    loc(void) {}                //  Used to construct temporaries
    loc (int lg, int lt)
      {
        longitude = lg;
        latitude = lt;
      }
    void show(void)
      {
      cout << longitude << " ";
      cout << latitude << endl;
      }
    void *operator new(size_t size);
    void operator delete(void *p);
 };

void *loc::operator new(size_t size)
 {
   cout << "In the custom new function." << endl;
   return malloc(size);
 }

void loc::operator delete(void *p)
 {
   cout << "In the custom delete function." << endl;
   free(p);
 }

void main(void)
  {
  loc *p1, *p2;

  p1 = new loc(10,20);
  if (!p1)
   {
     cout << "Allocation error\n";
     exit(1);
   }

  p2 = new loc(-10,-20);
  if (!p2)
   {
      cout << "Allocation error\n";
      exit(1);
   }
  p1->show();
  p2->show();
  delete p1;
  delete p2;
  exit (0);
 }

