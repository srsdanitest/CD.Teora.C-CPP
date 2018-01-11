#include <iostream.h>
#include <time.h>

inline void swap_inline(int *a, int *b, int *c, int *d)
 {
   int temp;

   temp = *a;
   *a = *b;
   *b = temp;

   temp = *c;
   *c = *d;
   *d = temp;
 }

void swap_call(int *a, int *b, int *c, int *d)
 {
   int temp;

   temp = *a;
   *a = *b;
   *b = temp;

   temp = *c;
   *c = *d;
   *d = temp;
 }


void main(void)
 {
   clock_t start, stop;
   long int i;
   int a = 1, b = 2, c = 3, d = 4;

   start = clock();
   for (i = 0; i < 300000L; i++)
     swap_inline(&a, &b, &c, &d);
   stop = clock();
   cout << "Time for inline: " << stop - start;
   
   start = clock();
   for (i = 0; i < 300000L; i++)
     swap_call(&a, &b, &c, &d);
   stop = clock();

   cout << "\nTime for called function: " << stop - start;
 }

   



