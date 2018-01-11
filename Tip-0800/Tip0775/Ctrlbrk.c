#include <stdio.h>
#include <dos.h>

int Ctrl_Handler(void)
  {
    printf("\007Press Enter to end the program\n");
    return(1);
  }

void main(void)
  {
    Ctrlbrk(Ctrl_Handler);
    printf("Press Enter to end the program\n");
    while (getchar() != '\n');
      ;
  }



