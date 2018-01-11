#include <iostream.h>
#include <stdio.h>


void main(void)
 { 
   char str[256];
   int i = 0;

   while ((str[i] = cin.get()) != '\n')
     i++;

   str[i] = NULL;

   cout << "The string was: " <<  str;
 }
