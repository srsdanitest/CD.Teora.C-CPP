#include <stdio.h>
#include <dir.h>

void main(void)
 {
   int drive_count;

   drive_count = setdisk(3);
   printf("The number of available drives is %d\n", drive_count);
 }
