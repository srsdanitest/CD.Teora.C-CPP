#include <iostream.h>

template <class X> void compact(X *items, int count, int start, int end)
template <class X> void show_items(X *items, int size)

void main(void)
 {
   int nums[7] =  {0, 1, 2, 3, 4, 5, 6};
   char str[18] = "Generic Functions";

   cout << "Here is uncompacted integer array: ";
   show_items(nums, 7);
   cout << "Here is the uncompacted char array: ";
   show_items(str, 18);
   compact(nums, 7, 2, 4);
   compact(str, 18, 6, 10);
   cout << "Here is compacted integer array: ";
   show_items(nums, 7);
   cout << "Here is the compacted char array: ";
   show_items(str, 18);
 }

template <class X> void compact(X *items, int count, int start, int end)
 {
   register int i;
   for(i=end+i; i < count; i++, start++)
      items[start] = items[i];
   for( ; start<count; start++)
      items[start] = (X) 0;
 }

template <class X> void show_items(X *items, int size)
 {
   int i;
   for(i=0; i < size; i++)
      cout << items[i];
   cout << endl;
 }






