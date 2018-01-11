#ifdef __BCPLUSPLUS__
#include <map.h>
#else
#include <map>
#endif

#include <iostream.h>
#include <string.h>

using namespace std;
typedef map<int, string, less<int>> INT2STRING;

void main(void)
 {
   // Create a map of ints to strings
   INT2STRING theMap;
   INT2STRING::iterator theIterator;
   string theString = "";
   int index, continue = 1;

   // Fill theMap with the digits 0 - 9, each mapped to its string counterpart
   // Note: value_type is a pair for maps...
   theMap.insert(INT2STRING::value_type(0,"Zero"));
   theMap.insert(INT2STRING::value_type(1,"One"));
   theMap.insert(INT2STRING::value_type(2,"Two"));
   theMap.insert(INT2STRING::value_type(3,"Three"));
   theMap.insert(INT2STRING::value_type(4,"Four"));
   theMap.insert(INT2STRING::value_type(5,"Five"));
   theMap.insert(INT2STRING::value_type(6,"Six"));
   theMap.insert(INT2STRING::value_type(7,"Seven"));
   theMap.insert(INT2STRING::value_type(8,"Eight"));
   theMap.insert(INT2STRING::value_type(9,"Nine"));
   // Read a Number from the user and print it back as words
   while (continue)
     {
       cout << "Enter \"q\" to quit, or enter a Number: ";
       cin >> theString;
       if(theString == "q")
         continue = 0;
       // extract each digit from the string, find its corresponding
       // entry in the map (the word equivalent) and print it
       for( index = 0; index < theString.length(); index++)
        {
          theIterator = theMap.find(theString[index] - '0');
          if(theIterator != theMap.end())			// is 0 - 9
            cout << (*theIterator).second << " ";
          else    						// not 0 - 9
            cout << "[err] ";
        }
       cout << endl;
    }
 }
