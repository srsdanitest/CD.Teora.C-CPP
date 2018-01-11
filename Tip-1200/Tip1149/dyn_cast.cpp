// NOTE: You must compile this program with your compiler's Generate RTTI option enabled.
#include <iostream.h>
#include <typeinfo.h>

class Base1
{
   virtual void f(void) { /* A virtual function makes the class polymorphic */ }
};

class Base2 { };
class Derived : public Base1, public Base2 { };

void main(void) 
{
   try 
   {
      Derived d, *pd;
      Base1 *b1 = &d;

      // Perform a downcast from a Base1 to a Derived.
      if ((pd = dynamic_cast<Derived *>(b1)) != 0) 
	  {
           cout << "The resulting pointer is of type "
                << typeid(pd).name() << endl;
         }
      else throw Bad_cast();

      // Cast from the first base to the most derived class and then back
      // to another accessible base.
      Base2 *b2;
      if ((b2 = dynamic_cast<Base2 *>(b1)) != 0) 
	  {

          cout << "The resulting pointer is of type "
               << typeid(b2).name() << endl;
         }
      else throw Bad_cast();
      }
   catch (Bad_cast) 
   {
      cout << "dynamic_cast failed" << endl;
      exit(1);
      }
   catch (...) {
      cout << "Exception handling error." << endl;
      exit(1);
      }

}
