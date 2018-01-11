//  If you use Visual C++, set the compile options to /GX
#ifdef __BCPLUSPLUS__
#include <iostream.h>
#include <vector.h>
#include <algorith.h>
#else
#include <iostream>
#include <vector>
#include <algorithm>
#endif

using namespace std;

void main(void)
{
	const int VECTOR_SIZE = 8;

	//Define a template class vector of int
	typedef vector<int> IntVector;

	//Define an interator for template class vector of strings
	typedef IntVector::iterator IntVectorIt;

	IntVector Numbers(VECTOR_SIZE);
	IntVector Result(4);

	IntVectorIt start, end, it;

	//Initialize vector Numbers
	Numbers[0] = 4;
	Numbers[1] = 10;
	Numbers[2] = 70;
	Numbers[3] = 30;
	Numbers[4] = 10;
	Numbers[5] = 69;
	Numbers[6] = 96;
	Numbers[7] = 7;

	start = Numbers.begin();	//location of first
								//element of Numbers

	end = Numbers.end();		//one past the location
								//last element of Numbers

	cout << "Before calling partial_sort_copy\n" << endl;

	//print content of Numbers
	cout << "Numbers { ";
	for (it = start; it != end; it++)
		cout << *it << " ";
	cout << "\b }\n" << endl;

	//sort the smallest 4 elemetns in the Numbers
	//and copy the results in Result
	partial_sort_copy(start, end, Result.begin(), Result.end());

	cout << "After calling partial_sort_copy\n" << endl;

	cout << "Numbers { ";
	for(it = start; it != end; it++)
		cout << *it << " ";
	cout << "\b }\n" << endl;

	cout << "Result { ";
	for(it = Result.begin(); it != Result.end(); it++)
		cout << *it << " ";
	cout << "\b }\n" << endl;
}