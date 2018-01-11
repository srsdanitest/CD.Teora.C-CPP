#include <iostream.h>

float sample_function(float i);
double sample_function(double i);

void main(void)
{
	cout << sample_function(1500.1) << " "; 	// unambiguous, calls sample_function(double)
   cout << sample_function(1500);           // ambiguous
}

float sample_function(float i)
{
	return i;
}

double sample_function(double i)
{
	return -i;
}

