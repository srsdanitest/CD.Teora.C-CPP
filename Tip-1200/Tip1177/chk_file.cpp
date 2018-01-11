#include "strings.h"
#include <iostream.h>
#include <fstream.h>

//executable file extensions

char ext[3][4] = { "EXE", "COM", "BAT" };

void main(int argc, char *argv[])
{
	Strings fname;
	int i;

	if(argc != 2)
	{
		cout << "Usage fname name" << endl;
		exit(1);
	}
	fname = argv[1];
	fname = fname + ".";
	for (i = 0; i<3; i++)
	{
		fname = fname + ext[i];
		cout << "Trying " << fname << " ";
		ifstream f;

      f.open(fname);
		if(f)
		{
			cout << " - Exists" << endl;
			f.close();
		}
		else
			cout << " - Not found"<< endl;
		fname = fname - ext[i];
	}
}