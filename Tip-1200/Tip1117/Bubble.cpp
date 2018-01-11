#include <iostream.h>

template <class X> void bubble_sort(X *items, int size)
template <class X> void show_items(X *items, int size)

void main(void)
 {
   int iarray[7] =      {7, 5, 4, 3, 9, 8, 6};
   double darray[5] =   {4.2, 2.5, -0.9, 100.2, 3.0};

   cout << "Here is unsorted integer array: " << endl;
   show_items(iarray, 7);
   cout << "Here is unsorted double array: " << endl;
   show_items(darray, 5);
   bubble_sort(iarray, 7);
   bubble_sort(darray, 5);
   cout << "Here is sorted integer array: " << endl;
   show_items(iarray, 7);
   cout << "Here is sorted double array: " << endl;
   show_items(darray, 5);
 }

template <class X> void bubble_sort(X *items, int size)
 {
   register int i, j;
   X temp;

   for (i = 1; i < size; i++)
    for (j = size-1; j >= i; j--)
      if (items[j-1] > items[j])
        {
          temp = items[j-1];
          items[j-1] = items[j];
          items[j] = temp;
        }
  }

template <class X> void show_items(X *items, int size)
 {
   int i;

   for(i=0; i < size; i++)
      cout << items[i] << ", ";
   cout << endl;
 }


