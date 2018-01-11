#include <iostream.h>                                                
#include <string.h>

class StringClass 
{
 public:
   void str_reverse(char *string) 
   { 
     if (*string)
       {
         str_reverse(string+1);
         cout.put(*string);
       }
   };
   int str_length(char *string) 
   {
       if (*string)    
         return (1 + str_length(++string));
       else
         return(0);
     };

   StringClass(char *string) { strcpy(StringClass::string, string); };
   char string[256];
};


void main(void)
 {
   StringClass title("Jamsa's C/C++ Programmer's Bible");

   title.str_reverse(title.string);

   cout << endl << "The title is " << 
     title.str_length(title.string) << " bytes long.";
 }


