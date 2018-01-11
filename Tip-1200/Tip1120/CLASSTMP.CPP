#include <iostream.h>

template<class T> class Distance {
  public:
    Distance(T distance); 
    void show_distance(void) { 
       cout << "The distance is " << distance << " miles\n"; };
  private:
    T distance;
};

template<class T>
Distance<T>::Distance(T distance) { Distance::distance = distance; };


void main(void)
 {
    Distance<int> short_distance(100);
    Distance<long> long_distance(2000000L);

    short_distance.show_distance();
    long_distance.show_distance();
 }

