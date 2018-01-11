#include <stdio.h>
#include <time.h>

void main(void)
 {
   time_t seconds;

   struct tm time_fields;

   time_fields.tm_mday = 31;
   time_fields.tm_mon = 10;
   time_fields.tm_year = 97;

   if (mktime(&time_fields) == -1)
     printf("Error converting fields\n");
   else
     printf("Julian date for October 31, 1997 is %d\n", time_fields.tm_yday);
 }

