#include <iostream>
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


	while (true)
	{
		cout << "Input Pointer which your want decrypt[call de_id()]: ";
		uint64_t encrypt_obj = 0;
		cin >> dec >> encrypt_obj;
		if (encrypt_obj == 0) break;
		uint64_t decrypt_obj = decrypt_objectid(encrypt_obj);
		cout << "decrypt!==>" << dec << decrypt_obj << endl;
	}


	return 0;
}