#include <iostream.h>

class sample
{
public:
	int who;
	sample(int id);
} global_obj1(1), global_obj2(2);

sample::sample(int id)
{
	cout << "Initializing " << id << "\n";
	who = id;
}

void main(void)
{
	sample local_obj(3);
	cout << "This is NOT the first line displayed.\n";
	sample local_obj2(4);
}


