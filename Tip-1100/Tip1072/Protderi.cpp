#include <iostream.h>
#include <string.h>

class Base 
{
  public:
    Base(char *str) { strcpy(message, str); }; 
    void show_base(void) { cout << message << endl; };
  protected:  
    char message[256];
 };


class Level1 : public Base 
{
  public:
    Level1(char *str, char *base) : Base(base) {
      strcpy(message, str);};
    void show_level1(void) { cout << message << endl; } ;
  protected:  
    char message[256];
 };

class Lowest : public Level1 
{
  public:
    Lowest(char *str, char *level1, char *base) :
      Level1(level1, base) { strcpy(message, str); };
    void show_lowest(void) 
	{
       show_base();
       show_level1();
       cout << message << endl; 
	};
  protected:
    char message[256];
 };

void main(void) 
 {
   Lowest bottom("Lowest message", "Level1 message", "Base message");
   
   bottom.show_lowest();
 }

                


