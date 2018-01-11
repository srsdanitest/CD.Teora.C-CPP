#include <stdio.h>
#include <dos.h>
#include <conio.h>

int count = 0;

void interrupt handler(void)
 {
   count++;
 }

void main(void)
 {
   void interrupt (*original_handler)();
   int old_count = 0;

   original_handler = _dos_getvect(5);

   _disable();                // Turn off interrupts during _dos_setvect
   _dos_setvect(5, handler);
   _enable();

   printf("Press SHIFT-PRTSC three times or any key to end\n");
     
   while (count < 3)
     if (count != old_count)
       {
         printf("SHIFT-PRTSC pressed\n");
         old_count = count;
       }
   
   _disable();
   _dos_setvect(5, original_handler);
   _enable();
 }
