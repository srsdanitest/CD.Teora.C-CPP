#include <stdio.h>
#include <time.h>

void main(void)
 {
   time_t seconds;

   struct tm time_fields;

   time_fields.tm_mday = 22;
   time_fields.tm_mon = 8;
   time_fields.tm_year = 97;
   time_fields.tm_hour = 0;
   time_fields.tm_min = 0;
   time_fields.tm_sec = 0;

   seconds = mktime(&time_fields);

   printf("The number of seconds between 1-1-70 and 10-31-97 is %ld\n",
     seconds);
 }

