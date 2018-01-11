#include <iostream.h>
#include <strstrea.h>

const int size = 5;

class plot 
{
   int x, y;
 public:
   plot(int i, int j)
    {
      if(i>size)
         i = size;
      if(i<0)
         i = 0;
      if(j>size)
         j = size;
      if(j<0)
         j=0;
      x=i;
      y=j;
    }
   friend ostream &operator<<(ostream &stream, plot obj);
};

ostream &operator<<(ostream & stream, plot obj)
 {
   register int i, j;

   for(j=size; j>=0; j--)
    {
      stream << j;
      if(j==obj.y)
       {
         for(i=0; i<obj.x; i++)
            stream << "  ";
            stream << '*';
       }
      stream << endl;
    }
   for(i=0; i<=size; i++)
      stream << " " << i;
   stream << endl;
   return stream;
 }

void main(void)
 {
   plot a(2,3), b(1,1);
   char str[200];

   cout << "Output using cout:" << endl;
   cout << a << endl << b << endl << endl;

   ostrstream outs(str, sizeof(str));
   outs << a << b << ends;
   cout << "output using in-RAM formatting:" << endl;
   cout << str;
 }

