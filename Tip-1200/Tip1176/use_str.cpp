#include <iostream.h>
#include <stdlib.h>
#include <string.h>
#include "strings.h"
#include <conio.h>
#include <stdio.h>


void main(void)
  {
   Strings s1("A sample program which uses string objects.\n");
   Strings s2(s1);
   Strings s3;
   char s[80];

   cout << s1 << s2;
   s3 = s1;
   cout << s3;
   s3.makestr(s);
   cout << "Converted to a string: " << s;

   s2 = "This is a new string.";
   cout << s2 << endl;

   Strings s4("This is a new string, too.");
   s1 = s2 + s4;
   cout << s1 << endl;

   if(s2==s3)
      cout << "Strings are equal." << endl;
   if(s2!=s3)
      cout << "Strings are not equal." << endl;
   if(s1<s4)
      cout << "s1 is less than s4." << endl;
   if(s1>s4)
      cout << "s1 is greater than s4." << endl;
   if(s1<=s4)
      cout << "s1 is less than or equal to s4." << endl;
   if(s1>s4)
      cout << "s1 is greater than or equal to s4." << endl;

   if(s2 > "ABC")
      cout << "s2 is greater than 'ABC'" << endl << endl;

   s1 = "one two three one two three\n";
   s2 = "two";
   cout << "Initial string: " << s1;
   cout << "String after subtracting two: ";
   s3 = s1 - s2;
   cout << s3;

   cout << endl;
   s4 = "Jamsa's C/C++ ";
   s3 = s4 + "Programmer's Bible\n";
   cout << s3;
   s3 = s3 - "C/C++";
   s3 = "This is " + s3;
   cout << s3;

   cout << "Enter a string: ";
   cin >> s1;
   cout << s1 << endl;
   cout << "s1 is " << s1.strsize() << " characters long." << endl;
   puts(s1);

   s1 = s2 = s3;
   cout << s1 << s2 << s3;
   s1 = s2 = s3 = "Program finished.\n";
   cout << s1 << s2 << s3;
 }










