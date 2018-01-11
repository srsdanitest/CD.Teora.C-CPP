#include <stdio.h>
#include <direct.h>
#include <stdlib.h>

void main(void)
  {
    char *path_1 = "C:\\SUBDIR\\FILENAME.EXT";
    char *path_2 = "SUBDIR\\FILENAME.EXT";
    char *path_3 = "FILENAME.EXE";
    char subdir[MAXDIR];
    char drive[MAXDRIVE];
    char filename[MAXFILE];
    char extension[MAXEXT];
    int flags;					// holds the fnsplit return value

	 flags = fnsplit (path_1, drive, subdir, filename, extension);
    printf ("Splitting %s\n", path_1);
    printf ("Drive %s Subdir %s Filename %s Extension %s\n",
      drive, subdir, filename, extension);
    flags = fnsplit (path_2, drive, subdir, filename, extension);
    printf ("Splitting %s\n", path_2);
    printf ("Drive %s Subdir %s Filename %s Extension %s\n",
      drive, subdir, filename, extension);

    flags = fnsplit (path_3, drive, subdir, filename, extension);
    printf ("Splitting %s\n", path_3);
    printf ("Drive %s Subdir %s Filename %s Extension %s\n",
      drive, subdir, filename, extension);
  }
