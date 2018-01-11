#include <stdio.h>

#define MIN(x, y) (((x) < (y)) ? (x): (y))
#define MAX(x, y) (((x) > (y)) ? (x): (y))

void main(void)
 {
   printf("Maximum of 10.0 and 25.0 is %f\n", MAX(10.0, 25.0));
   printf("Minimum of 3.4 and 3.1 is %f\n", MIN(3.4, 3.1));
 }

  
