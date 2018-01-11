#include <stdio.h>

void main(void)
 {
   int count = 1;

   label:
     printf("%d ", count++);
     
     if (count <= 100)
       goto label;
 }
