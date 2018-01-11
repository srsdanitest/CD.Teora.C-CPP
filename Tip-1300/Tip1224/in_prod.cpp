//  If you use Visual C++, set the compile options to /GX
#ifdef __BCPLUSPLUS__
#include <iostream.h>
#include <vector.h>
#include <numeric.h>
#include <iterator.h>
#else
#include <iostream>
#include <vector>
#include <numeric>
#include <iterator>
#endif

using namespace std;

typedef vector<float> FloatArray;
typedef ostream_iterator<float, char, char_traits<char>>
FloatOstreamIt;

void main(void)
{
	FloatOstreamIt itOstream(count, " ");

	//Initialize the arrays
	FloatArray rgF1, rgF2;
	for (int i=1; i<=5; i++)
	{
		rgF1.push_back(i);
		rgF2.push_back(i*i);
	};

	//print the arrays
	cout << "Array 1: ";
	copy(rgF1.begin(), rgF1.end(), itOstream);
	cout << endl;
	cout << "Array 2: ";
	copy(rgF2.begin(), rgF2.end(), itOstream);
	cout << endl;

	//This is the sum of the products (S.O.P) of the corresponding elements
	float ip1 = inner_product(rgF1.begin(), rgF1.end(), rgF2.begin(), 0);
	cout << "The inner product (S.O.P.) of Array and Array2 is " << ip1 << endl;

	//This is the product of the sums (P.O.S.) of the corresponding elements
	float ip2 = inner_product(rgF1.begin(), rgF1.end(), rgF2.begin(), 1,
		multiplies<float>(), plus<float>());
	cout << "The inner product (P.O.S.) of Array2 is " << ip2 << endl;
}