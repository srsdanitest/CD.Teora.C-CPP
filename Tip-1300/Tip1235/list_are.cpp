#ifdef __BCPLUSPLUS__
#include <list.h>
#else
#include <list>
#endif
#include <iostream>

using namespace std;

typedef list<int> LISTINT;

void main(void)
{
    LISTINT listOne;
    LISTINT listAnother;
    LISTINT::iterator i;

    // Add some data
    listOne.push_front (2);
    listOne.push_front (1);
    listOne.push_back (3);
    listAnother.push_front(4);
    listAnother.assign(listOne.begin(), listOne.end());

    // 1 2 3
    for (i = listAnother.begin(); i != listAnother.end(); ++i)
        cout << *i << " ";
    cout << endl;
    listAnother.assign(4, 1);

    // 1 1 1 1
    for (i = listAnother.begin(); i != listAnother.end(); ++i)
        cout << *i << " ";
    cout << endl;
    listAnother.erase(listAnother.begin());

    // 1 1 1
    for (i = listAnother.begin(); i != listAnother.end(); ++i)
        cout << *i << " ";
    cout << endl;
    listAnother.erase(listAnother.begin(), listAnother.end());
    if (listAnother.empty())
        cout << "All gone\n";
}
