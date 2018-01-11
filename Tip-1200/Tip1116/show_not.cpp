#include <iostream.h>

void sample(int x, char *y);
void sample(float x, long y);
void sample(char *x, char *y);

void main(void)
 {
   sample(10, "hi");
   sample(0.23, 10L);
   sample("Jamsa's", "C/C++");
 }

void sample(int x, char *y)
 {
   cout << x << " " << y << endl;
 }

void sample(float x, long y)
 {
   cout << x << " " << y << endl;
 }

void sample(char *x, char *y)
 {
   cout << x << " " << y << endl;
 }

