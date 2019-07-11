//#include "libgo.h"
#include "main.h"
#include <thread>


int main()
{
	driver *drv = 0;
	drv = new driver();
	unsigned long long base = drv->GetGameModule();
	printf("0x%-12IX GameBase\n", base);
	unsigned long imageSize = drv->GetImageSize();
	printf("0x%-12IX ImageSize\n", imageSize);
	unsigned char *dump = 0;
	dump = (unsigned char*)malloc(imageSize);
	drv->RPM(base, dump, imageSize);
	unsigned long long *strings = 0;
	strings = (unsigned long long*)malloc(0x102400);
	if (!strings) throw "variable initialization memory failed in function [main]";
	unsigned long long size = FindPattern(dump, imageSize, "48 8D 15 ? ? ? ?", strings);
	printf("[!] Total fount count %Id\n", size);

	const wchar_t *searchNames[18] =
	{
		L"LastRenderTimeOnScreen",
		L"ComponentVelocity",
		L"AnimScriptInstance",
		L"ControlRotation_CP",
		L"WeaponProcessor",
		L"EquippedWeapons",
		L"WeaponTrajectoryData",
		L"TrajectoryConfig",
		L"VDragCoefficient",
		L"TrajectoryGravityZ",
		L"VehicleRiderComponent",
		L"SeatIndex",
		L"ReplicatedMovement",
		L"LastVehiclePawn",
		L"SimulationSubstepTime",
		L"Team",
		L"Health",
		L"GroggyHealth",
	};
	
	for (int i = 0; i < size; i++)
	{
		unsigned long long offset = strings[i];
		if (*(unsigned int*)(dump + offset + 3) > 0x0f000000) continue;
		unsigned long long stringAddr = *(unsigned int*)(dump + offset + 3) + offset + 7 + (unsigned long long)dump;
		wchar_t name[128]{ 0 };
		memcpy(name, (void *)stringAddr, 128);
		for (int j = 0; j < 18; j++)
		{
			if (!wcsicmp(name, searchNames[j]))
			{
				unsigned long long *searchOut = new unsigned long long[20];
				if (FindPattern(dump + offset, 200, "41 B9 ? ? ? ? 45 33 C0", searchOut))
				{
					int r9d = *(unsigned int*)(dump + offset + searchOut[0] + 2);
					printf("0x%-12X %ws\n", r9d, name);
				}
				delete[] searchOut;
			}
		}
	}
	free(strings);
	strings = 0;
	free(dump);
	dump = 0;
	delete drv;



	printf("[!] Work Done. \n");
	getchar();
	return 0;
 }