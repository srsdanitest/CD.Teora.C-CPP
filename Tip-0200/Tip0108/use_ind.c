#include <stdio.h>

void main(void)
 { 
   int age = 10;
   int user_has_dog = 0;   // 0 is false

   if (age == 10)
     {
       printf("Dogs are important pets\n");
       if (! user_has_dog)
         printf("You should get a dalmatian\n");
     }
   printf("Happy is a dalmatian\n");
 }
