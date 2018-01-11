#include <iostream.h>

int sum(int *array, int element_count)
 {
   int result = 0;
   int count;

   for (count = 0; count < element_count; count++)
     result += array[count];

   return(result);
 }

float sum(float *array, int element_count)
 {
   float result = 0;
   int count;

   for (count = 0; count < element_count; count++)
     result += array[count];

   return(result);
 }


void main(void) 
 {
   int a[5] = { 1, 2, 3, 4, 5 };
   float b[4] = { 1.11, 2.22, 3.33, 4.44 };

   cout << "Sum of int values: " << sum(a, 5) << '\n';
   cout << "Sum of float values: " << sum(b, 4) << '\n';
 }

