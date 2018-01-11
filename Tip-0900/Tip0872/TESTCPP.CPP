#ifdef __cplusplus
#include <iostream.h>
#else
#include <stdio.h>
#endif


void main(void)
 {
#ifdef __cplusplus
  cout << "C++ compilation";
#else
  printf("C compilation\n");
#endif
 }
