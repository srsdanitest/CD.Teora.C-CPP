#include <iostream.h>
#include <iomanip.h>
#include <string.h>

class String {
  public: 
    char *operator +(char *append_str)
      { return(strcat(buffer, append_str)); };
   
    String(char *string) 
      { 
		strcpy(buffer, string); 
        length = strlen(buffer); 
	}

    void show_string(void) { cout << buffer; };
  
    void strapd(char *source) { strcat(buffer, source); };

  private:
    char buffer[256];
    int length;
};


void main(void)
 {
   String title("Jamsa's C/C++ ");
   title = title + "Programmer's Bible\n";
   title.show_string();

 
   String book2("Rescued by C++");
   book2.strapd(", Third Edition ");
   book2.show_string();
 }

