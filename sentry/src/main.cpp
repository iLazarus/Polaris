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



	cout << "Input Object Pointer which your want decrypt: ";
	uint64_t encrypt_obj = 0;
	cin >> hex >> encrypt_obj;
	
	uint64_t decrypt_obj = decrypt_gobjects(encrypt_obj);
	cout << "decrypt!==>" << hex << decrypt_obj << endl;





	system("pause");
	return 0;
}