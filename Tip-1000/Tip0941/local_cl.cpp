#include <iostream.h>

void f(void);

void main(void)
{
	f();
}

void f(void)
{
	class mylocalclass
		{
		int i;
	public:
		void put_i(int n) {i=n;}
		int get_i() {return i;}
		} ob;

	ob.put_i(10);
	cout << ob.get_i();
}

