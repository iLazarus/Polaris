#pragma once
#pragma warning(disable : 4996)

#ifndef GAME_H
#define GAME_H

#include "driver.h"
#pragma comment(lib, "driver.lib")

#include "pattern.h"
#pragma comment(lib, "pattern.lib")

#include "asm.h"
#pragma comment(lib, "asmdecrypt.lib")

#include "graphics.h"
#pragma comment(lib, "graphics.lib")

#include <string>
#include <list>
#include <vector>
#include <map>
#include<algorithm>
#include <WinUser.h>

#define WIDTH GetSystemMetrics(SM_CXSCREEN)
#define HEIGHT GetSystemMetrics(SM_CYSCREEN)
#define AIMLIMITEDSIZE						80000

#define CAMERACACHE							0x152C
#define TEAM								0x1488
#define LASTRENDERONSCREEN					0x748

#define VEHICLERIDERCOMPONENT				0x1720
#define SEATINDEX							0x1E8
#define COMPONENTVELOCITY					0x354
#define LASTVEHICLEPAWN						0x220
#define REPLICATEDMOVEMENT					0xD0
#define ANIMSCRIPTINSTANCE					0xBA8
#define CONTROLROTATION_CP					0x678

#define WEAPONPROCESSOR						0xC30
#define EQUIPPEDWEAPONS						0x290
#define WEAPONTRAJECTORYDATA				0xD50
#define TRAJECTORYCONFIG					0xB0
#define VDRAGCOEFFICIENT					0x20


using namespace std;

class game
{
public:
	game();
	~game();

	void Init(driver *pDrv, graphics *pDx);
	void ScanOffset();
	void RefreshOffset();
	void FilterActors();
	void Fire();
	void HotKey();


private:

	struct Vector3
	{
	public:
		float x;
		float y;
		float z;

		Vector3()
		{
			x = 0;
			y = 0;
			z = 0;
		}

		Vector3(float _x, float _y, float _z)
		{
			x = _x;
			y = _y;
			z = _z;
		}

		~Vector3()
		{
		}

		inline Vector3 ToFRotator() //转换到角度
		{
			float RADPI = (float)(180 / M_PI);
			float Yaw = (float)atan2f(y, x) * RADPI;
			float Pitch = (float)atan2f(z, sqrtf(powf(x, 2.0) + powf(y, 2.0))) * RADPI;
			float Roll = 0;
			return  Vector3(Pitch, Yaw, Roll);
		}

		inline float Dot(Vector3 v)
		{
			return x * v.x + y * v.y + z * v.z;
		}

		inline float Distance(Vector3 v)
		{
			return float(sqrtf(powf(v.x - x, 2.0) + powf(v.y - y, 2.0) + powf(v.z - z, 2.0)));
		}

		inline float Length()
		{
			return float(sqrtf(powf(x, 2.0) + powf(y, 2.0) + powf(z, 2.0)));
		}

		Vector3 operator+(Vector3 v)
		{
			return Vector3(x + v.x, y + v.y, z + v.z);
		}

		Vector3 operator-(Vector3 v)
		{
			return Vector3(x - v.x, y - v.y, z - v.z);
		}

		Vector3 operator/(float f)
		{
			return Vector3(x / f, y / f, z / f);
		}

		Vector3 operator*(float f)
		{
			return Vector3(x * f, y * f, z * f);
		}

		bool operator==(Vector3 v)
		{
			return ((x == v.x) && (y == v.y) && (z == v.z));
		}
	};

	struct FRotator
	{
	public:
		float Pitch;
		float Yaw;
		float Roll;

		FRotator() : Pitch(0.f), Yaw(0.f), Roll(0.f)
		{

		}

		FRotator(float _pitch, float _yaw, float _roll) : Pitch(_pitch), Yaw(_yaw), Roll(_roll)
		{

		}

		~FRotator()
		{

		}

		inline double Length()
		{
			return sqrtf(powf(Pitch, 2.0) + powf(Yaw, 2.0) + powf(Roll, 2.0));
		};

		void Clamp()
		{

			if (Pitch > 180)
				Pitch -= 360;

			else if (Pitch < -180)
				Pitch += 360;

			if (Yaw > 180)
				Yaw -= 360;

			else if (Yaw < -180)
				Yaw += 360;

			if (Pitch < -89)
				Pitch = -89;

			if (Pitch > 89)
				Pitch = 89;

			while (Yaw < -180.0f)
				Yaw += 360.0f;

			while (Yaw > 180.0f)
				Yaw -= 360.0f;

			Roll = 0;
			return;
		}

		Vector3 ToVector()
		{
			float radPitch = (float)(Pitch * M_PI / 180.f);
			float radYaw = (float)(Yaw * M_PI / 180.f);

			float SP = (float)sinf(radPitch);
			float CP = (float)cosf(radPitch);
			float SY = (float)sinf(radYaw);
			float CY = (float)cosf(radYaw);

			return  Vector3(CP * CY, CP * SY, SP);
		}

		D3DMATRIX GetAxes()
		{
			auto tempMatrix = Matrix();
			return tempMatrix;
		}

		D3DMATRIX Matrix(Vector3 origin = Vector3(0, 0, 0))
		{

			float radPitch = (Pitch * float(M_PI) / 180.0f);
			float radYaw = (Yaw * float(M_PI) / 180.0f);
			float radRoll = (Roll * float(M_PI) / 180.0f);
			float SP = sinf(radPitch);
			float CP = cosf(radPitch);
			float SY = sinf(radYaw);
			float CY = cosf(radYaw);
			float SR = sinf(radRoll);
			float CR = cosf(radRoll);

			D3DMATRIX matrix;
			matrix.m[0][0] = CP * CY;
			matrix.m[0][1] = CP * SY;
			matrix.m[0][2] = SP;
			matrix.m[0][3] = 0.f;

			matrix.m[1][0] = SR * SP * CY - CR * SY;
			matrix.m[1][1] = SR * SP * SY + CR * CY;
			matrix.m[1][2] = -SR * CP;
			matrix.m[1][3] = 0.f;

			matrix.m[2][0] = -(CR * SP * CY + SR * SY);
			matrix.m[2][1] = CY * SR - CR * SP * SY;
			matrix.m[2][2] = CR * CP;
			matrix.m[2][3] = 0.f;

			matrix.m[3][0] = origin.x;
			matrix.m[3][1] = origin.y;
			matrix.m[3][2] = origin.z;
			matrix.m[3][3] = 1.f;

			return matrix;
		}

		FRotator operator+(FRotator v)
		{
			return FRotator(Pitch + v.Pitch, Yaw + v.Yaw, Roll + v.Roll);
		}

		FRotator operator-(FRotator v)
		{
			return FRotator(Pitch - v.Pitch, Yaw - v.Yaw, Roll - v.Roll);
		}

		FRotator operator*(FRotator v)
		{
			return FRotator(Pitch * v.Pitch, Yaw * v.Yaw, Roll * v.Roll);
		}

		FRotator operator/(FRotator v)
		{
			return FRotator(Pitch / v.Pitch, Yaw / v.Yaw, Roll / v.Roll);
		}
	};

	struct FMinimalViewInfo
	{
	public:
		// FOV cc cc cc f3 0f 10 ? ? ? ? ? 0f ? ? 0f ? ? 77 08 f3 0f 10 ? ? ? ? ? c3
		// ROT f2 0f 10 81 ? ? ? ? f2 41 0f 11 ? 8b 81 ? ? ? ? 41 89 ? ? c3
		// LOT cc f2 0f 10 81 ? ? ? ? f2 0f 11 ? 8b 81 ? ? ? ? 89 42 ? f2
		float FOV;
		char pad2[0x4];
		Vector3 Location;
		char pad1[0x4];
		FRotator Rotation;		
	};

	struct FCameraCacheEntry
	{
	public:
		char pad[0x10];
		struct FMinimalViewInfo POV;
	};

	string GetGNameById(unsigned long long ID)
	{
		if (!g_Chunksize) printf("[!] You Need Initialize Right Chunsize Value of Game\n");
		unsigned long long fNamePtr = drv->RPM<unsigned long long>(g_GNames + unsigned long long(ID / g_Chunksize) * 8);
		unsigned long long fName = drv->RPM<unsigned long long>(fNamePtr + 8 * unsigned long long(ID % g_Chunksize));
		char *name;
		name = (char *)malloc(256);
		if (!name) throw "variable initialization failed in function [GetGNameById]";
		drv->RPM(fName + 0x10, name, 256);
		if (!name) return "";
		string ret = string(name);
		free(name);
		name = nullptr;
		return ret;
	}

	unsigned long long ScanGNames(unsigned long long gname_offset)
	{
		if (!gname_offset) printf("[!] You Need Initialize Right GNames Offset Value of Game\n");
		bool found = false;
		unsigned long long gnames = 0;
		unsigned long long tmp = drv->RPM<unsigned long long>(drv->GetGameModule() + gname_offset + 0x1FA0);
		unsigned long long minval = (tmp >> 6 * 4) << 4 * 4;
		unsigned long long maxval = minval + 0xFFFFFF;
		for (unsigned long long i = minval; i < maxval; i++)
		{
		
			gnames = (i << 8) + 0x10;
			g_GNames = gnames;
			found = (!strcmp(GetGNameById(1).c_str(), "ByteProperty")
				&& !strcmp(GetGNameById(2).c_str(), "IntProperty")
				&& !strcmp(GetGNameById(3).c_str(), "BoolProperty"));
			if (found) break;

			gnames = (i << 8) + 0x80;
			g_GNames = gnames;
			found = (!strcmp(GetGNameById(1).c_str(), "ByteProperty")
				&& !strcmp(GetGNameById(2).c_str(), "IntProperty")
				&& !strcmp(GetGNameById(3).c_str(), "BoolProperty"));
			if (found) break;
		}
		printf("0x%-12IX %s\n", gnames, found ? "GNames Pointer Found [!]" : "GNames Pointer Miss [X]");
		if (found)
		{
			g_GNames = gnames;
			printf("[!] Start In The Cache\n");
			CachedNames.clear();

			fclose(stdout);
			freopen("names.txt", "w", stdout);

			for (int i = 0; i < 240000; i++)
			{
				string name = GetGNameById(i);
				if (name == "Uaz_C" || name == "Uaz_A_01_C" || name == "Uaz_B_01_C" || name == "Uaz_C_01_C") {
					name = "吉普";
				}
				else if (name == "Dacia_C" || name == "Dacia_A_01_v2_C" || name == "Dacia_A_02_v2_C" || name == "Dacia_A_03_v2_C"
					|| name == "Dacia_A_04_v2_C" || name == "ABP_Dacia_01_C"
					|| name == "BP_Mirado_A_01_C" || name == "BP_Mirado_A_02_C" || name == "BP_Mirado_A_03_C" || name == "BP_Mirado_A_04_C" || name == "BP_Mirado_A_03_Esports_C"
					|| name == "BP_Mirado_Open_01_C" || name == "BP_Mirado_Open_02_C" || name == "BP_Mirado_Open_03_C" || name == "BP_Mirado_Open_04_C" || name == "BP_Mirado_Open_C")
				{
					name = "轿车";
				}
				else if (name == "ABP_Motorbike_03_C" || name == "ABP_Motorbike_04_C" || name == "BP_Motorbike_03_C" || name == "BP_Motorbike_04_C" || name == "BP_Motorbike_04_Desert_C" || name == "BP_Scooter_01_A_C" || name == "BP_Scooter_02_A_C" || name == "BP_Scooter_03_A_C" || name == "BP_Scooter_04_A_C") {
					name = "摩托";
				}
				else if (name == "ABP_Motorbike_04_Sidecar_C" || name == "BP_Motorbike_04_SideCar_C" || name == "BP_Motorbike_04_SideCar_Desert_C" || name == "ABP_Motorbike_03_Sidecart_C"
					|| name == "BP_Motorbike_03_SideCart_C" || name == "BP_Motorbike_04_Desert_C" || name == "BP_TukTukTuk_A_01_C" || name == "BP_TukTukTuk_A_02_C" || name == "BP_TukTukTuk_A_03_C") {
					name = "三轮";
				}
				else if (name == "Buggy_A_01_C" || name == "Buggy_A_02_C" || name == "Buggy_A_03_C" || name == "Buggy_A_04_C" || name == "Buggy_A_05_C" || name == "Buggy_A_06_C" || name == "Buggy_C" || name == "ABP_Buggy_02" || name == "ABP_Buggy_02_C") {
					name = "四驱";
				}
				else if (name == "AquaRail_C" || name == "AquaRail_A_01_C" || name == "Boat_PG117_C" || name == "PG117_A_01_C") {
					name = "游艇";
				}
				else if (name == "BP_M_Rony_A_01_C" || name == "BP_M_Rony_A_02_C" || name == "BP_M_Rony_A_03_C" ||
					name == "BP_PickupTruck_C" || name == "BP_PickupTruck_A_C" || name == "BP_PickupTruck_A_01_C" || name == "BP_PickupTruck_A_02_C" || name == "BP_PickupTruck_A_03_C" || name == "BP_PickupTruck_A_04_C" || name == "BP_PickupTruck_A_05_C" || name == "BP_PickupTruck_B_C" || name == "BP_PickupTruck_B_01_C" || name == "BP_PickupTruck_B_02_C" || name == "BP_PickupTruck_B_03_C" || name == "BP_PickupTruck_B_04_C" || name == "BP_PickupTruck_B_05_C")
				{
					name = "皮卡";
				}
				else if (name == "BP_Van_A_01_C" || name == "BP_Van_A_02_C" || name == "BP_Van_A_03_C" || name == "BP_MiniBus_C" || name == "ABP_Minibus_02_C")
				{
					name = "公交";
				}
				else if (name == "BP_Snowmobile_01_C" || name == "BP_Snowmobile_02_C" || name == "BP_Snowmobile_03_C" || name == "BP_Snowmobile_04_C" || name == "Dacia_A_01_v2_snow_C" || name == "Uaz_A_01_snow_C" || name == "BP_Motorbike_04_snow_C")
				{
					name = "雪橇";
				}
				else if (name == "Item_Armor_C_01_Lv3_C")
				{
					name = "三甲";
				}
				else if (name == "Item_Armor_D_01_Lv2_C")
				{

					name = "二甲";
				}
				else if (name == "Item_Head_F_01_Lv2_C" || name == "Item_Head_F_02_Lv2_C")
				{
					name = "二头";
				}
				else if (name == "Item_Head_G_01_Lv3_C")
				{

					name = "三头";
				}
				else if (name == "Item_Weapon_Grenade_C")
				{

					name = "手雷";
				}
				else if (name == "Item_Boost_AdrenalineSyringe_C")
				{

					name = "肾上腺";
				}
				else if (name == "Item_Boost_EnergyDrink_C")
				{

					name = "饮料";
				}
				else if (name == "Item_Boost_PainKiller_C")
				{

					name = "止疼";
				}
				else if (name == "Item_Heal_FirstAid_C")
				{

					name = "大药";
				}
				else if (name == "Item_Heal_MedKit_C")
				{
					name = "医疗箱";
				}
				else if (name == "Item_Weapon_Groza_C")
				{

					name = "Goza";
				}
				else if (name == "Item_Ghillie_01_C" || name == "Item_Ghillie_02_C" || name == "Item_Ghillie_03_C" || name == "Item_Ghillie_04_C")
				{
					name = "吉利服";
				}
				else if (name == "Item_Attach_Weapon_Magazine_ExtendedQuickDraw_Large_C")
				{

					name = "步快";
				}
				else if (name == "Item_Attach_Weapon_Magazine_ExtendedQuickDraw_SniperRifle_C")
				{

					name = "狙快";
				}
				else if (name == "Item_Attach_Weapon_Muzzle_Compensator_Large_C")
				{

					name = "步口";
				}
				else if (name == "Item_Attach_Weapon_Muzzle_Compensator_SniperRifle_C")
				{

					name = "狙口";
				}

				else if (name == "Item_Attach_Weapon_Muzzle_Suppressor_Large_C")
				{

					name = "步消";
				}
				else if (name == "Item_Attach_Weapon_Muzzle_Suppressor_SniperRifle_C")
				{

					name = "狙消";
				}
				else if (name == "Item_Attach_Weapon_Upper_DotSight_01_C" || name == "Item_Attach_Weapon_Upper_DotSight_Crossbow_C")
				{
					name = "红点";
				}
				else if (name == "Item_Attach_Weapon_Upper_Holosight_C")
				{

					name = "全息";
				}
				else if (name == "Item_Attach_Weapon_Upper_Aimpoint_C")
				{

					name = "2X镜";
				}
				else if (name == "Item_Attach_Weapon_Upper_Scope3x_C")
				{

					name = "3X镜";
				}
				else if (name == "Item_Attach_Weapon_Upper_ACOG_01_C")
				{

					name = "4X镜";
				}
				else if (name == "Item_Attach_Weapon_Upper_Scope6x_C")
				{

					name = "6X镜";
				}
				else if (name == "Item_Attach_Weapon_Upper_CQBSS_C")
				{

					name = "8X镜";
				}
				else if (name == "Item_Attach_Weapon_Upper_PM2_01_C")
				{

					name = "15X镜";
				}
				else if (name == "Item_Back_F_01_Lv2_C" || name == "Item_Back_F_02_Lv2_C")
				{
					name = "二包";
				}
				else if (name == "Item_Back_C_01_Lv3_C" || name == "Item_Back_C_02_Lv3_C")
				{
					name = "三包";
				}
				else if (name == "Item_Ammo_556mm_C")
				{

					name = "5.56";
				}
				else if (name == "Item_Ammo_762mm_C")
				{

					name = "7.62";
				}
				else if (name == "Item_Ammo_300Magnum_C")
				{

					name = "马格南";
				}
				else if (name == "Item_Weapon_Mk14_C")
				{

					name = "MK14";
				}
				else if (name == "Item_Weapon_FNFal_C")
				{

					name = "SLR";
				}
				else if (name == "Item_Weapon_M16A4_C")
				{

					name = "M16";
				}

				else if (name == "Item_Weapon_AK47_C")
				{

					name = "AKM";
				}
				else if (name == "Item_Weapon_AWM_C")
				{

					name = "AWM";
				}
				else if (name == "Item_Weapon_HK416_C")
				{

					name = "M4";
				}
				else if (name == "Item_Weapon_Kar98k_C")
				{

					name = "98K";
				}
				else if (name == "Item_Weapon_M24_C")
				{

					name = "M24";
				}
				else if (name == "Item_Weapon_M249_C")
				{

					name = "M249";
				}
				else if (name == "Item_Weapon_Mini14_C")
				{

					name = "Mini";
				}
				else if (name == "Item_Weapon_SCAR-L_C")
				{

					name = "SCARL";
				}
				else if (name == "Item_Weapon_SKS_C")
				{

					name = "SKS";
				}
				else if (name == "Item_Weapon_AUG_C")
				{

					name = "AUG";
				}
				else if (name == "Item_Weapon_UMP_C")
				{

					name = "UMP9";
				}
				else if (name == "Item_Weapon_UZI_C")
				{

					name = "UZI";
				}
				else if (name == "Item_Weapon_Vector_C")
				{

					name = "雷蛇";
				}
				else if (name == "Item_Weapon_Thompson_C")
				{

					name = "汤姆逊";
				}
				else if (name == "Item_Weapon_QBZ95_C")
				{

					name = "QBZ";
				}
				else if (name == "Item_Weapon_QBU88_C")
				{
					name = "QBU";
				}
				else if (name == "Item_Weapon_BerylM762_C")
				{
					name = "M762";
				}
				else if (name == "Item_Attach_Weapon_Stock_AR_Composite_C")
				{
					name = "枪托";
				}
				else if (name == "Item_Attach_Weapon_Lower_ThumbGrip_C")
				{
					name = "拇指";
				}
				else if (name == "Item_Attach_Weapon_Lower_HalfGrip_C")
				{
					name = "半截";
				}
				else if (name == "Item_Attach_Weapon_Lower_LightweightForeGrip_C")
				{
					name = "轻型";
				}
				else if (name == "Item_Attach_Weapon_Lower_AngledForeGrip_C")
				{
					name = "三角";
				}
				else if (name == "Item_Attach_Weapon_Lower_Foregrip_C")
				{
					name = "垂直";
				}
				else if (name == "Item_Attach_Weapon_Stock_SniperRifle_CheekPad_C")
				{
					name = "托腮";
				}
				else if (name == "Item_Attach_Weapon_Magazine_Extended_SniperRifle_C")
				{
					name = "狙扩";
				}
				else if (name == "Item_Attach_Weapon_Magazine_Extended_Large_C")
				{
					name = "步扩";
				}
				else if (name == "Item_Weapon_VSS_C")
				{
					name = "VSS";
				}
				else if (name == "Item_Weapon_Mk47Mutant_C")
				{
					name = "MK47";
				}
				else if (name == "Item_Weapon_G36C" || name == "Item_Weapon_G36C_C")
				{
					name = "G36";
				}
				else if (name == "Item_Weapon_vz61Skorpion_C")
				{
					name = "VZ61";
				}
				else if (name == "Item_Attach_Weapon_SideRail_DotSight_RMR_C")
				{
					name = "侧瞄";
				}
				else if (name == "Item_Weapon_FlareGun_C")
				{
					name = "信号枪";
				}
				CachedNames.push_back(name);

				printf("%-10d %s\n", i, name.c_str());
			}
			fclose(stdout);
			freopen("CON", "w", stdout);
			printf("[!] Cached Complete\n");
		}
		else
		{
			gnames = 0;
			g_GNames = 0;
		}

		
		return gnames;
	}

	Vector3 WorldToScreen(Vector3 location, FCameraCacheEntry cameracach)
	{
		Vector3 Screenlocation = Vector3(0, 0, 0);
		auto POV = cameracach.POV;
		FRotator Rotation = POV.Rotation;
		Vector3 vAxisX, vAxisY, vAxisZ;
		D3DMATRIX tempMatrix = Rotation.GetAxes();
		vAxisX = Vector3(tempMatrix.m[0][0], tempMatrix.m[0][1], tempMatrix.m[0][2]);
		vAxisY = Vector3(tempMatrix.m[1][0], tempMatrix.m[1][1], tempMatrix.m[1][2]);
		vAxisZ = Vector3(tempMatrix.m[2][0], tempMatrix.m[2][1], tempMatrix.m[2][2]);
		Vector3 vDelta = location - POV.Location;
		Vector3 vTransformed = Vector3(vDelta.Dot(vAxisY), vDelta.Dot(vAxisZ), vDelta.Dot(vAxisX));

		if (vTransformed.z < 1.f)
			vTransformed.z = 1.f;

		float FovAngle = POV.FOV;
		float ScreenCenterX = WIDTH / 2.0f;
		float ScreenCenterY = HEIGHT / 2.0f;

		Screenlocation.x = ScreenCenterX + vTransformed.x * (ScreenCenterX / tanf(FovAngle * (float)M_PI / 360.f)) / vTransformed.z;
		Screenlocation.y = ScreenCenterY - vTransformed.y * (ScreenCenterX / tanf(FovAngle * (float)M_PI / 360.f)) / vTransformed.z;
		return Screenlocation;
	}

	struct FQuat
	{
		float x;
		float y;
		float z;
		float w;
	};

	struct FTransform
	{
	public:
		FQuat rot;
		Vector3 translation;
		char pad[4];
		Vector3 scale;
		char pad1[4];
		D3DMATRIX ToMatrixWithScale()
		{
			D3DMATRIX m;
			m._41 = translation.x;
			m._42 = translation.y;
			m._43 = translation.z;

			float x2 = rot.x + rot.x;
			float y2 = rot.y + rot.y;
			float z2 = rot.z + rot.z;

			float xx2 = rot.x * x2;
			float yy2 = rot.y * y2;
			float zz2 = rot.z * z2;
			m._11 = (1.0f - (yy2 + zz2)) * scale.x;
			m._22 = (1.0f - (xx2 + zz2)) * scale.y;
			m._33 = (1.0f - (xx2 + yy2)) * scale.z;

			float yz2 = rot.y * z2;
			float wx2 = rot.w * x2;
			m._32 = (yz2 - wx2) * scale.z;
			m._23 = (yz2 + wx2) * scale.y;

			float xy2 = rot.x * y2;
			float wz2 = rot.w * z2;
			m._21 = (xy2 - wz2) * scale.y;
			m._12 = (xy2 + wz2) * scale.x;

			float xz2 = rot.x * z2;
			float wy2 = rot.w * y2;
			m._31 = (xz2 + wy2) * scale.z;
			m._13 = (xz2 - wy2) * scale.x;

			m._14 = 0.0f;
			m._24 = 0.0f;
			m._34 = 0.0f;
			m._44 = 1.0f;

			return m;
		}
	};

	D3DMATRIX MatrixMultiplication(D3DMATRIX pM1, D3DMATRIX pM2)
	{
		D3DMATRIX pOut;
		pOut._11 = pM1._11 * pM2._11 + pM1._12 * pM2._21 + pM1._13 * pM2._31 + pM1._14 * pM2._41;
		pOut._12 = pM1._11 * pM2._12 + pM1._12 * pM2._22 + pM1._13 * pM2._32 + pM1._14 * pM2._42;
		pOut._13 = pM1._11 * pM2._13 + pM1._12 * pM2._23 + pM1._13 * pM2._33 + pM1._14 * pM2._43;
		pOut._14 = pM1._11 * pM2._14 + pM1._12 * pM2._24 + pM1._13 * pM2._34 + pM1._14 * pM2._44;
		pOut._21 = pM1._21 * pM2._11 + pM1._22 * pM2._21 + pM1._23 * pM2._31 + pM1._24 * pM2._41;
		pOut._22 = pM1._21 * pM2._12 + pM1._22 * pM2._22 + pM1._23 * pM2._32 + pM1._24 * pM2._42;
		pOut._23 = pM1._21 * pM2._13 + pM1._22 * pM2._23 + pM1._23 * pM2._33 + pM1._24 * pM2._43;
		pOut._24 = pM1._21 * pM2._14 + pM1._22 * pM2._24 + pM1._23 * pM2._34 + pM1._24 * pM2._44;
		pOut._31 = pM1._31 * pM2._11 + pM1._32 * pM2._21 + pM1._33 * pM2._31 + pM1._34 * pM2._41;
		pOut._32 = pM1._31 * pM2._12 + pM1._32 * pM2._22 + pM1._33 * pM2._32 + pM1._34 * pM2._42;
		pOut._33 = pM1._31 * pM2._13 + pM1._32 * pM2._23 + pM1._33 * pM2._33 + pM1._34 * pM2._43;
		pOut._34 = pM1._31 * pM2._14 + pM1._32 * pM2._24 + pM1._33 * pM2._34 + pM1._34 * pM2._44;
		pOut._41 = pM1._41 * pM2._11 + pM1._42 * pM2._21 + pM1._43 * pM2._31 + pM1._44 * pM2._41;
		pOut._42 = pM1._41 * pM2._12 + pM1._42 * pM2._22 + pM1._43 * pM2._32 + pM1._44 * pM2._42;
		pOut._43 = pM1._41 * pM2._13 + pM1._42 * pM2._23 + pM1._43 * pM2._33 + pM1._44 * pM2._43;
		pOut._44 = pM1._41 * pM2._14 + pM1._42 * pM2._24 + pM1._43 * pM2._34 + pM1._44 * pM2._44;
		return pOut;
	}

	FTransform GetBoneIndex(DWORD_PTR mesh, int index)
	{
		unsigned long long boneArray = drv->RPM<unsigned long long>(mesh + g_offset_bones);
		return drv->RPM<FTransform>(boneArray + index * sizeof(FTransform), sizeof(FTransform));
	}

	Vector3 GetBoneWithRotation(DWORD_PTR mesh, int id)
	{
		FTransform bone = GetBoneIndex(mesh, id);
		FTransform ComponentToWorld = drv->RPM<FTransform>(mesh + g_offset_c2w, sizeof(FTransform));
		D3DMATRIX Matrix;
		Matrix = MatrixMultiplication(bone.ToMatrixWithScale(), ComponentToWorld.ToMatrixWithScale());
		return Vector3(Matrix._41, Matrix._42, Matrix._43);
	}

	driver *drv = 0;
	graphics *dx = 0;
	vector<string> CachedNames;
	FCameraCacheEntry FCameraCache;

	bool autobot = false;
	bool esp = true;
	bool espitem = false;
	bool espvehical = false;
	bool espaircraft = false;

	map<unsigned long long, float> AimMap;
	unsigned long long g_BestAimActor = 0;

	list<int> upper_part = { 5, 6, 15 };
	list<int> right_arm = { 5, 115, 116, 117 };
	list<int> left_arm = { 5, 88,89,90 };
	list<int> spine = { 5, 1 };
	list<int> lower_right = { 1, 174, 175, 176 };
	list<int> lower_left = { 1, 168,169,170 };
	list<list<int>> skeleton = { upper_part, right_arm, left_arm, spine, lower_right, lower_left };

	unsigned long long g_GNames = 0;
	unsigned long long g_Chunksize = 0;
	unsigned long long g_GObjects = 0;
	unsigned long long g_UWorld = 0;
	unsigned long long g_UInst = 0;
	unsigned long long g_ULevel = 0;
	unsigned long long g_AActors = 0;
	unsigned long long g_ULocal = 0;
	unsigned long long g_AControl = 0;
	unsigned long long g_UPlayerCameraManager = 0;
	unsigned long long g_DefaultPawn = 0;
	unsigned long long g_DefaultMesh = 0;


	unsigned int g_offset_gname = 0;
	unsigned int g_offset_uworld = 0;
	unsigned int g_offset_inst = 0;
	unsigned int g_offset_level = 0;
	unsigned int g_offset_actors = 0;
	unsigned int g_offset_local = 0;
	unsigned int g_offset_controler = 0;
	unsigned int g_offset_id = 0;
	unsigned int g_offset_playercamermgr = 0;
	unsigned int g_offset_defaultpawn = 0;
	unsigned int g_offset_mesh = 0;
	unsigned int g_offset_health = 0;
	unsigned int g_offset_groggyhealth = 0;
	unsigned int g_offset_droppeditems = 0;
	unsigned int g_offset_itempackages = 0;
	unsigned int g_offset_uitem = 0;
	unsigned int g_offset_root = 0;
	unsigned int g_offset_bones = 0;
	unsigned int g_offset_c2w = 0;
	unsigned int g_offset_relative = 0;


	inline bool isPlayer(int id)
	{
		if (id < CachedNames.size())
		{
			if (CachedNames[id] == "PlayerFemale_A" || CachedNames[id] == "PlayerFemale_A_C" || CachedNames[id] == "PlayerMale_A" || CachedNames[id] == "PlayerMale_A_C")
			{
				return true;
			}
		}
		return false;
	}

	inline bool isVehicle(int id)
	{
		if (id < CachedNames.size())
		{
			if (CachedNames[id] == "吉普" || CachedNames[id] == "轿车" || CachedNames[id] == "摩托" || CachedNames[id] == "三轮" || CachedNames[id] == "四驱" || CachedNames[id] == "游艇" || CachedNames[id] == "皮卡" || CachedNames[id] == "公交" || CachedNames[id] == "雪橇") {
				return true;
			}
		}
		return false;
	}

	inline bool isItems(int id)
	{
		if (id < CachedNames.size())
		{
			if (CachedNames[id] == "DroppedItemInteractionComponent" || CachedNames[id] == "DroppedItemGroup" || CachedNames[id] == "DroppedItem")
			{
				return true;
			}
		}
		return false;
	}

	inline bool isAircaft(int id)
	{
		if (id < CachedNames.size())
		{
			if (CachedNames[id] == "Carapackage_RedBox_C")
			{
				return true;
			}
		}
		return false;
	}

	inline bool isLoot(int id)
	{
		if (id < CachedNames.size())
		{
			if (CachedNames[id] == "DeathDropItemPackage_C")
			{
				return true;
			}
		}
		return false;
	}

	inline bool inScreen(Vector3 v)
	{
		return (v.x > 0 && v.x < WIDTH && v.y >0 && v.y < HEIGHT);
	}

	void DrawSkeleton(unsigned long long mesh, bool visual)
	{
		//1 f 2 M 0 FALSE
		// neck 5   head 6 
		Vector3 neckpos = GetBoneWithRotation(mesh, 5);
		Vector3 pelvispos = GetBoneWithRotation(mesh, 1);
		Vector3 previous(0, 0, 0);
		Vector3 current, p1, c1;
		for (auto a : skeleton)
		{
			previous = Vector3(0, 0, 0);
			for (int bone : a)
			{
				current = bone == 5 ? neckpos : (bone == 1 ? pelvispos : GetBoneWithRotation(mesh, bone));
				if (previous.x == 0.f || previous.y == 0.f)
				{
					previous = current;
					continue;
				}
				p1 = WorldToScreen(previous, FCameraCache);
				c1 = WorldToScreen(current, FCameraCache);
				if (p1.Distance(c1) > 1000.f)
				{
					previous = current;
					continue;
				}
				dx->DrawLine(p1.x, p1.y, c1.x, c1.y, visual ? VISUAL : UNVISUAL);
				previous = current;
			}
		}
	}

	D3DCOLOR getColor(string name)
	{
		if (name == "汤姆逊" || name == "UZI" || name == "UMP9" || name == "雷蛇" || name == "AKM" || name == "M16" || name == "M762"
			|| name == "7.62" || name == "止疼" || name == "饮料" || name == "大药"
			|| name == "红点" || name == "全息" || name == "2X镜" || name == "3X镜" || name == "三角" || name == "拇指" || name == "轻型")
		{
			return LIGHTBLUE;
		}
		else if (name == "三包" || name == "M4" || name == "M249" || name == "QBZ" || name == "QBU" || name == "二包" || name == "二甲" || name == "二头"
			|| name == "SCARL" || name == "Mini" || name == "SKS" || name == "SLR" || name == "AUG"
			|| name == "Goza" || name == "吉利服" || name == "医疗箱" || name == "MK14" || name == "AWM" || name == "马格南"
			|| name == "肾上腺" || name == "MK47" || name == "VSS"
			|| name == "4X镜" || name == "6X镜" || name == "15X镜" || name == "手雷" || name == "狙口" || name == "枪托" || name == "半截" || name == "托腮" || name == "VZ61" || name == "G36")
		{
			return PURPLE;
		}
		else if (name == "5.56")
		{
			return GREEN;
		}
		else if (name == "步口" || name == "垂直" || name == "狙快" || name == "狙扩" || name == "步扩")
		{
			return BLUE;
		}
		else if (name == "三头" || name == "三甲" || name == "步消" || name == "步快" || name == "狙消" || name == "M24" || name == "8X镜" || name == "侧瞄" || name == "信号枪" || name == "98K")
		{
			return RED;
		}

		return WHITE;

	}

	struct DroppedItem {
		__int64 group;
		__int64 UNKNOWN;
	};


};

#endif // !GAME_H




