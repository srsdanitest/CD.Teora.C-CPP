#include <stdio.h>

void main(void)
 {
   FILE *fp;

   int pages = 800;
   float price = 49.95;

   if (fp = fopen("FPRINTF.DAT", "w"))
     {
       fprintf(fp, "Book Title: Jamsa\'s C & C++ Programmer\'s Bible\n");
       fprintf(fp, "Pages: %d\n", pages);
       fprintf(fp, "Price: $%5.2f\n", price);
       fclose(fp);
     }
   else 
     printf("Error opening FPRINTF.DAT\n");
 }
