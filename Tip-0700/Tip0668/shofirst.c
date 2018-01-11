#include <stdio.h>
#include <stdlib.h>

void main(int argc, char *argv[])
 {
   char line[255];  // Line read from the file
   int i,j;
   FILE *fp;

   if (argc > 2)
      j = 10;
   else
      j = argv[2];

   if (fp = fopen(argv[1], "r"))
     {
       for (i=0; i < j; i++)
         {
            fgets(line, sizeof(line), fp);
            fputs(line, stdout);
         }
       fclose(fp);
     }
   else
     {
       printf("Cannot open %s\n", argv[1]);
       exit (1);
     }
 }

