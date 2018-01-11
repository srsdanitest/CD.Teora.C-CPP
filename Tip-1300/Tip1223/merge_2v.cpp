//  If you use Visual C++, set the compile options to /GX
#ifdef __BCPLUSPLUS__
#include <iostream.h>
#include <vector.h>
#include <algorith.h>
#include <list.h>
#include <deque.h>
#else
#include <iostream>
#include <vector>
#include <algorithm>
#include <list>
#include <deque>
#endif

using namespace std;

void main(void)
{
	const int MAX_ELEMENTS = 8;
	typedef vector<int> IntVector;		//Define a template class vector of int
	typedef IntVector::iterator IntVectorIt;		//Define an iterator type
	typedef list<int> IntList;			//Define a template class list of int
	typedef IntList::iterator IntListIt;	//Define an iterator type
	typedef deque<int> IntDeque;		//Define a template class deque of int
	typedef IntDeque::iterator IntDequeIt;	//Define an iterator type

	IntVector NumbersVector(MAX_ELEMENTS);
	IntVectorIt startv, endv, itv;
	IntList NumbersList;
	IntListIt first, last, itl;
	IntDeque NumbersDeque(2 * MAX_ELEMENTS);
	IntDequeIt itd;

	//Initialize vector NumbersVector
	NumbersVector[0] = 4;
	NumbersVector[1] = 10;
	NumbersVector[2] = 70;
	NumbersVector[3] = 10;
	NumbersVector[4] = 30;
	NumbersVector[5] = 69;
	NumbersVector[6] = 96;
	NumbersVector[7] = 100;

	startv = NumbersVector.begin();		//location of first element of NumbersVector
	endv = NumbersVector.end();		//one past the last element of NumbersVector

	//sort NumbersVestor, mersge requires the sequences to be sorted
	sort(startv, endv);

	//print content of NumbersVector
	cout << "NumbersVector { ";
	for(itv = startv; itv != endv; itv++)
		cout << *itv << " ";
	cout << " }\n" << endl;

	//Initialize list NumbersList
	for(int i = 0; i < MAX_ELEMENTS; i++)
		NumbersList.push_back(i);

	first = NumbersList.begin();	//location of first element of NumbersList
	last = NumbersList.end();		//one past the last element of NumbersList

	//print content of NumbersList
	cout << "NumbersList { ";
	for(itl = first; itl != last; itl++)
		cout << *itl << " ";
	cout << " }\n" << endl;

	//merge the elements of NumbersVestor and NumbersList and place the 
	//results in NumbersDeque
	merge(startv, endv, first, last, NumbersDeque.begin());

	//print content of NumbersDeque
	cout << "After calling merge\n" << endl;
	cout << "NumbersDeque { " ;
	for (itd = NumbersDeque.begin(); itd != NumbersDeque.end(); itd++)
		cout << *itd << " ";
	cout << " }\n" << endl;
}


	