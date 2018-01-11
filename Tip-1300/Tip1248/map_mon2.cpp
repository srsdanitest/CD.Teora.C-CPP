#ifdef __BCPLUSPLUS__
#include <map.h>
#else
#include <map>
#endif
#include <iostream.h>
#include <string.h>

using namespace std;

typedef map<string, int> STRING2INT;

void main(void)
{
    STRING2INT DateMap;
    STRING2INT::iterator DateIterator;
    string DateBuffer;

    // print the maximum number of <key,data> pairs that DateMap can hold
    cout << "DateMap is capable of holding " << DateMap.max_size()
         << " <string,int> pairs" << endl;

    if(!DateMap.empty())
        cout << "DateMap has " << DateMap.size() << " entries" << endl;
    else
        cout << "DateMap is empty" << endl;
        cout << "Entering new entries in DateMap" << endl;
    // Fill in DateMap with the months of the year, mapped to their number
    // January - 1, February - 2, etc. using operator[].
    DateMap["January"] = 1;
    DateMap["February"] = 2;
    DateMap["March"] = 3;
    DateMap["April"] = 4;
    DateMap["May"] = 5;
    DateMap["June"] = 6;
    DateMap["July"] = 7;
    DateMap["August"] = 8;
    DateMap["September"] = 9;
    DateMap["October"] = 10;
    DateMap["November"] = 11;
    DateMap["December"] = 12;

    if(!DateMap.empty())
        cout << "DateMap has " << DateMap.size() << " entries" << endl;
    else
        cout << "DateMap is empty" << endl;

    // Ask the user for a month of the year and print the number
    // that corresponds to the month entered 
    DateIterator = DateMap.end();
    while(DateIterator == DateMap.end())
     {
        cout << "Enter a Month :";
        cin >> DateBuffer;
        if((DateIterator = DateMap.find(DateBuffer)) != DateMap.end())
            cout << (*DateIterator).first << " is Month Number "
                 << (*DateIterator).second << endl;
        else
            cout << "Enter a Valid Month (example: March)" << endl;
     }

    // empty DateMap - note that clear simply calls erase(begin(),end());
    DateMap.clear();

    if(!DateMap.empty())
        cout << "DateMap has " << DateMap.size() << " entries" << endl;
    else
        cout << "DateMap is empty" << endl;

    cout << "Entering new entries in DateMap" << endl;
    // Fill DateMap with the days of the week, each mapped to an int
    DateMap["Monday"] = 1;
    DateMap["Tuesday"] = 2;
    DateMap["Wednesday"] = 3;
    DateMap["Thursday"] = 4;
    DateMap["Friday"] = 5;
    DateMap["Saturday"] = 6;
    DateMap["Sunday"] = 7;

    if(!DateMap.empty())
        cout << "DateMap has " << DateMap.size() << " entries" << endl;
    else
        cout << "DateMap is empty" << endl;

    // Ask the user for a day of the week and print the number
    // that corresponds to the day entered
    DateIterator = DateMap.end();
    while(DateIterator == DateMap.end()){
        cout << "Enter a Day of the Week:";
        cin >> DateBuffer;
        if((DateIterator = DateMap.find(DateBuffer)) != DateMap.end())
            cout << (*DateIterator).first << " is Day Number "
                 << (*DateIterator).second << endl;
        else
            cout <<"Enter a Valid Day of the Week(example: Monday)"<< endl;
    }
// Now clear DateMap again - this time using erase instead of clear
    DateMap.erase(DateMap.begin(), DateMap.end());

    if(!DateMap.empty())
        cout << "DateMap has " << DateMap.size() << " entries" << endl;
    else
        cout << "DateMap is empty" << endl;
 }
