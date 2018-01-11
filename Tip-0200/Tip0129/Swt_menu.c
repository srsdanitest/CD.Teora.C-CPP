#include <stdio.h>
#include <conio.h>
#include <ctype.h>
#include <stdlib.h>

void main(void)
 {
   char letter;
   
   do {
     printf("A Display directory listing\n");
     printf("B Change system time\n");
     printf("C Change system date\n");
     printf("Q Quit\n");
     printf("Choice: ");
     
     letter = getch();     
     letter = toupper(letter);

     switch (letter) {
       case 'A': system("DIR");
                 break;
       case 'B': system("TIME");
                 break;
       case 'C': system("DATE");
                 break;
     };
    }
   while (letter != 'Q');
 }

