#include <iostream.h>

class Beepers 
{
 public:
   void beep(void); 
   void beepbeep(void);
};
     
   
void Beepers::beep(void) 
{ 
  asm 
  { 
	  mov ah,2;
    mov dl,7;
    int 0x21; 
  }
}
                           
void Beepers::beepbeep(void) 
{ 
  asm 
  { 
	  mov ah,2;
      mov dl,7;
      int 0x21; 
      mov ah,2;
      mov dl,7;
      int 0x21; 
  }
}

void main(void)
 {
   Beepers noise;

   noise.beep();
   noise.beepbeep();
 }


