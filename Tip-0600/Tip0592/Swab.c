#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mem.h>

void main(void)
 {
   char *source = "aJsm\'a s/C+C +rPgoarmmres\'B biele";
   char target[64];

   memset(target, NULL, sizeof(target));  

   swab(source, target, strlen(source));

   printf("Source: %s Target %s\n", source, target);
 }
