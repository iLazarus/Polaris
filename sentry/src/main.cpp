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

	uint64_t encrypt_obj = 0;
	uint64_t decrypt_obj = 0;
	while (true)
	{
		encrypt_obj = 0;
		decrypt_obj = 0;
		cout << "outer: ";
		
		cin >> dec >> encrypt_obj;
		if (encrypt_obj == 0) break;
		decrypt_obj = decrypt_outer(encrypt_obj);
		cout << "decrypt outer!  0x" << hex << decrypt_obj << "   "<< dec << decrypt_obj << endl;

		///////////////
		cout << "id: ";
		cin >> dec >> encrypt_obj;
		if (encrypt_obj == 0) break;
		decrypt_obj = decrypt_objectid(encrypt_obj);
		cout << "decrypt    id!  0x" << hex << decrypt_obj << "   " << dec << decrypt_obj << endl;

		///////////////
		cout << "number: ";
		cin >> dec >> encrypt_obj;
		if (encrypt_obj == 0) break;
		decrypt_obj = decrypt_objectnumber(encrypt_obj);
		cout << "decrypt number!  0x" << hex << decrypt_obj << "   " << dec << decrypt_obj << endl;
	}


	return 0;
}