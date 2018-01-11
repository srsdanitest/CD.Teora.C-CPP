#include <stdio.h>

class c {
 public:
 	int j;
   c(void) {j=10;}
 };

void PrintInt(const c* Object)
 {
 	c* New = Object;
   New->j +=5;
   printf("%d\n", New->j);
 }

void main(void)
 {
 	const c Sample;

   PrintInt(&Sample);
 }
