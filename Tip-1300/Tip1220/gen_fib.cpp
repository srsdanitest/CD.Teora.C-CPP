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

//return the next Fibonacci number in the Fibonacci series.
int Fibonacci(void)
{
	static int r;
	static int f1 = 0;
	static int f2 = 1;
	r = f1 + f2;
	f1 = f2;
	f2 = r;
	return f1;
}

void main(void)
{
	const int VECTOR_SIZE = 15;

	//Define a template class vector of integers 
	typedef vector<int> IntVector;

	//Define a iterator for template class vector of integer
	typedef IntVector::iterator IntVectorIt;

	IntVector Numbers(VECTOR_SIZE);		//vector containing numbers
	IntVectorIt start, end , it;
	int i;

	//Initialize vector Numbers
	for(i = 0; i < VECTOR_SIZE; i++)
		Numbers[i] = i * i;
	start = Numbers.begin();	//location of first element of Numbers
	end = Numbers.end();		//one past the location of the last elememt of Numbers
	cout << "Before calling generate_n" << endl;
	//print content of Numbers
	cout << "Numbers { ";
	for (it = start; it != end; it++)
		cout << *it << " ";
	cout << " }\n" << endl;

	//fill the specified range with a series of 
	//Fibonacci numbers using the Fibonacci function
	generate_n(start + 5, Numbers.size() - 5, Fibonacci);

	cout << "After calling generate_n" << endl;

	//print content of Numbers
	cout << "Numbers {";
	for (it = start; it != end; it++)
	cout << *it << " ";
	cout << " }\n" << endl;
}