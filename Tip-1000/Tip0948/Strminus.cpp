/* Another way to overload the - operator */

#include <iostream.h>
#include <iomanip.h>
#include <string.h>

class String {
  public: 
    char *operator +(char *append_str)
      { return(strcat(buffer, append_str)); };
   
    char *operator -(char letter);

    String(char *string) 
      { strcpy(buffer, string); 
        length = strlen(buffer); }

    void show_string(void) { cout << buffer; };
  private:
    char buffer[256];
    int length;
};

char *String::operator -(char letter)
 { 
   char target[256];
   int i, j;

   for (i = 0, j = 0; buffer[j]; j++) 
     if (buffer[j] != letter)
       target[i++] = buffer[j];
   target[i] = NULL;
   
   for (i = 0, j = 0; (buffer[j] = target[i]); i++, j++)
     ; 
   return(buffer);
 }

void main(void)
 {
   String title("Jamsa's C/C++ ");

   title = title + "Programmer's Bible\n";
   title.show_string();
   title = title - '0';
   title.show_string();
 }

