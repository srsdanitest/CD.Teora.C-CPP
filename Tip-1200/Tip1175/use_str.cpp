#include <iostream.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <stdio.h>

class Strings {
   char *p;
   int size;
 public:
   Strings(char *str);
   Strings(void);
   Strings(const Strings &obj);           // Copy constructor
   ~Strings(void) {delete [] p;}

   friend ostream &operator<<(ostream &stream, Strings &obj);
   friend istream &operator>>(istream &stream, Strings &obj);

   Strings operator=(Strings &obj);       // assign a Strings object
   Strings operator=(char *s);            // assign a quoted string
   Strings operator+(Strings &obj);       // concatenate a Strings object
   Strings operator+(char *s);            // concatenate a quoted string
   friend Strings operator+(char *s, Strings &obj);
            /* concatenates a quoted string with a Strings object */

   Strings operator-(Strings &obj);       // subtract a Strings object
   Strings operator-(char *s);            // subtract a quoted string

 /* relational operators between Strings objects. Note that the operators could
    just as easily return bool, rather than int */

   int operator==(Strings &obj) {return !strcmp(p, obj.p);}
   int operator!=(Strings &obj) {return strcmp(p, obj.p);}
   int operator<(Strings &obj) {return strcmp(p, obj.p) < 0;}
   int operator>(Strings &obj) {return strcmp(p, obj.p) > 0;}
   int operator<=(Strings &obj) {return strcmp(p, obj.p) <= 0;}
   int operator>=(Strings &obj) {return strcmp(p, obj.p) >= 0;}

 /* relational operators between Strings object and a quoted character string.
    Note that the operators could just as easily return bool, rather than int */

   int operator==(char *s) {return !strcmp(p, s);}
   int operator!=(char *s) {return strcmp(p, s);}
   int operator<(char *s) {return strcmp(p, s) < 0;}
   int operator>(char *s) {return strcmp(p, s) > 0;}
   int operator<=(char *s) {return strcmp(p, s) <= 0;}
   int operator>=(char *s) {return strcmp(p, s) >= 0;}

   int strsize(void) {return strlen(p);}      // return string size
   void makestr(char *s) {strcpy(s, p);}  // make quoted string from Strings object

   operator char *(void) {return p;}          // conversion to char
 };

Strings::Strings(void)
 {
   size = 1;
   p = new char[size];
   if(!p)
    {
      cout << "Allocation error!" << endl;
      exit(1);
    }
   *p = '\0';
 }

Strings::Strings(char *str)
 {
   size = strlen(str) + 1;
   p = new char[size];
   if(!p)
    {
      cout << "Allocation error!" << endl;
      exit(1);
    }
   strcpy(p, str);
 }

Strings::Strings(const Strings &obj)
 {
   size = obj.size;
   p = new char[size];
   if(!p)
    {
      cout << "Allocation error!" << endl;
      exit(1);
    }
   strcpy(p, obj.p);
 }

ostream &operator<<(ostream &stream, Strings &obj)
 {
   stream << obj.p;
   return stream;
 }

istream &operator>>(istream &stream, Strings &obj)
 {
   char t[255];      // arbitrary string length--yours can be larger
   int len;

   for(len=0; len<255; len++)
    {
      stream.get(t[len]);
      if(t[len]=='\n')
         break;
      if(t[len]=='\b')
         if(len)
          {
            len--;
            cout << "'\b'";
          }
    }
   t[len]='\0';
   len++;

   if(len>obj.size)
    {
      delete obj.p;
      obj.p = new char[len];
      if(!obj.p)
       {
         cout << "Allocation error!" << endl;
         exit(1);
       }
      obj.size = len;
    }
   strcpy(obj.p, t);
   return stream;
 }

Strings Strings::operator=(Strings &obj)
  {
   Strings temp(obj.p);

   if(obj.size > size)
    {
      delete p;
      p = new char[obj.size];
      size = obj.size;
      if(!p)
       {
         cout << "Allocation error!" << endl;
         exit(1);
       }
    }
   strcpy(p, obj.p);
   strcpy(temp.p, obj.p);
   return temp;
 }

Strings Strings::operator=(char *s)
  {
   int len = strlen(s) + 1;

   if(size < len)
    {
      delete p;
      p = new char[len];
      size = len;
      if(!p)
       {
         cout << "Allocation error!" << endl;
         exit(1);
       }
    }
   strcpy(p, s);
   return *this;
 }

Strings Strings::operator+(Strings &obj)
 {
   int len;
   Strings temp;

   delete temp.p;
   len = strlen(obj.p) + strlen(p) + 1;
   temp.p = new char[len];
   temp.size = len;
   if(!temp.p)
    {
      cout << "Allocation error!" << endl;
      exit(1);
    }
   strcpy(temp.p, p);
   strcat(temp.p, obj.p);
   return temp;
 }

Strings Strings::operator+(char *s)
 {
   int len;
   Strings temp;

   delete temp.p;
   len = strlen(s) + strlen(p) + 1;
   temp.p = new char[len];
   temp.size = len;
   if(!temp.p)
    {
      cout << "Allocation error!" << endl;
      exit(1);
    }
   strcpy(temp.p, p);
   strcat(temp.p, s);
   return temp;
 }

Strings operator+(char *s, Strings &obj)
 {
   int len;
   Strings temp;

   delete temp.p;
   len = strlen(s) + strlen(obj.p) + 1;
   temp.p = new char[len];
   temp.size = len;
   if(!temp.p)
    {
      cout << "Allocation error!" << endl;
      exit(1);
    }
   strcpy(temp.p, s);
   strcat(temp.p, obj.p);
   return temp;
 }

Strings Strings::operator-(Strings &substr)
 {
   Strings temp(p);
   char *s1;
   int i,j;

   s1 = p;
   for(i=0; *s1; i++)
    {
      if(*s1!=*substr.p)
       {
         temp.p[i] = *s1;
         s1++;
       }
      else
       {
         for(j=0; substr.p[j]==s1[j] && substr.p[j]; j++)
            ;
         if(!substr.p[j])
          {
            s1 += j;
            i--;
          }
         else
          {
            temp.p[i] = *s1;
            s1++;
          }
       }
    }
    temp.p[i] = '\0';
    return temp;
 }

Strings Strings::operator-(char *substr)
 {
   Strings temp(p);
   char *s1;
   int i,j;

   s1 = p;
   for(i=0; *s1; i++)
    {
      if(*s1!=*substr)
       {
         temp.p[i] = *s1;
         s1++;
       }
      else
       {
         for(j=0; substr[j]==s1[j] && substr[j]; j++)
            ;
         if(!substr[j])
          {
            s1 += j;
            i--;
          }
         else
          {
            temp.p[i] = *s1;
            s1++;
          }
       }
    }
    temp.p[i] = '\0';
    return temp;
 }

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










