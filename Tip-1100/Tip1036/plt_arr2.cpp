#include <iostream.h>
#include <strstrea.h>

const int size = 5;

class plot {
   int x, y;
 public:
   plot(void);
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

plot::plot(void)
{
	cout << "Enter x value: ";
	cin >> this->x;
	cout << "\nEnter y value: ";
	cin >> this->y;
}


void main(void)
 {
   plot a(2,3), b(1,1), c;
   char str[200];
   ostrstream outs(str, sizeof(str));

   cout << "Output using cout:" << endl;
   cout << a << endl << b << endl << c << endl << endl;
   outs << a << b << c << ends;
   cout << "output using in-RAM formatting:" << endl;
   cout << str;
   istrstream ins(str);
 }

