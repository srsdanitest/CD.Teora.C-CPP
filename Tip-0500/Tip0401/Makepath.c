#include <stdio.h>
#include <stdlib.h>
#include <dir.h>

void main(void)
 {
   char pathname[MAXPATH];

   char *drive = "C:";
   char *subdir = "\\SUBDIR";
   char *filename = "FILENAME";
   char *extension = "EXT";

   fnmerge(pathname, drive, subdir, filename, extension);

   printf("The complete pathname is %s\n", pathname);
 }

