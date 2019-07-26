#include <iostream>
#include <string>
using namespace std;

//#include "ObjectStores.h"

#include "asm.h"

int main()
{
	//cout << "Set GName: ";
	//uint64_t gname = 0;
	//cin >> hex >> gname;
	//cout << dec << gname << endl;
	//cout << "Set GObject: ";
	//uint64_t gobject = 0;
	//cin >> hex >> gobject;
	//cout << dec << gobject << endl;

	//GlobalObjects = reinterpret_cast<decltype(GlobalObjects)>(gobject);

	string str = string("/Script/CoreUObject/");
	int pos = str.rfind('?');
	printf("pos = %d\n", pos);
	if (pos == string::npos)
	{
		printf("string::npos = %d\n", pos);
	}

	while (true)
	{
		cout << "Input Pointer which your want decrypt[call outer dec()]: ";
		uint64_t encrypt_obj = 0;
		cin >> dec >> encrypt_obj;
		if (encrypt_obj == 0) break;
		uint64_t decrypt_obj = decrypt_outer(encrypt_obj);
		cout << "decrypt!  0x" << hex << decrypt_obj << "   "<< dec << decrypt_obj << endl;
	}


	return 0;
}