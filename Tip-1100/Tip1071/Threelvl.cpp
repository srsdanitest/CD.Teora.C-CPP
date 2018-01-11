#include <iostream.h>

class Base 
{
 public:
   void show_base(void) { cout << "Base class message\n"; };
};

class Level1 : public Base 
{
 public:
   void show_level1(void) 
   { 
       show_base();
       cout << "Level 1 message\n"; 
   };
};

class Level2 : public Level1 
{
  public:
    void show_level2(void) 
	{
        show_level1();
        cout << "Level 2 message\n"; 
	};
};

class Level3 : public Level2 
{
  public:
    void show_level3(void) 
	{
        show_level2();
        cout << "Level 3 message\n"; 
	};
};

void main(void)
 {
   Level3 my_data;

   my_data.show_level3();
 }

