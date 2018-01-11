#include <iostream.h>
#include <iomanip.h>
#include <string.h>

class String 
{
  public: 
    char *operator +(char *append_str)
      { return(strcat(buffer, append_str)); };
   
    char *operator -(char letter);

    String(char *string) 
      { strcpy(buffer, string); 
        length = strlen(buffer); }

    void show_string() { cout << buffer; };
  private:
    char buffer[256];
    int length;
};

void main(void)
 {
   String title("Jamsa's C/C++ ");

   title = title + "Programmer's Bible\n";
   title.show_string();
 }

