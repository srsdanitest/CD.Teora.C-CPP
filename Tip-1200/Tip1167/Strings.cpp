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
   void makestr(char *s) (strcpy(s, p);}  // make quoted string from Strings object

   operator char *(void) {return p;}          // conversion to char
 }

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






