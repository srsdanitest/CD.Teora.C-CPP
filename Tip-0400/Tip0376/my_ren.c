#include <stdio.h>

void main(int argc, char *argv[])
 {
  if (argc < 3)
    printf("Must specify a source and target filename\n");
  else if (rename(argv[1], argv[2]))
    printf("Error renaming file\n");
 }
