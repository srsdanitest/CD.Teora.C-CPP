#include <stdio.h>
#include <dos.h>

void main(void)
 {
   struct date desired_date;

   desired_date.da_mon = 10;
   desired_date.da_day = 31;
   desired_date.da_year = 1997;

   setdate(&desired_date);
 }
