#include "game.h"
#pragma warning(disable : 4996)

game::game()
{
}


game::~game()
{
}



void game::Init(driver *pDrv, graphics *pDx)
{
	drv = pDrv;
	dx = pDx;
}

void game::ScanOffset()
{
	// base
	unsigned long long base = drv->GetGameModule();
	printf("0x%-12IX GameBase\n", base);
	unsigned long imagesize = (unsigned long)drv->GetImageSize();
	printf("0x%-12X ImageSize\n", imagesize);
	// dump
	unsigned char *dump;
	dump = (unsigned char*)malloc(imagesize);
	if (!dump) throw "variable initialization memory failed in function [ScanOffset]";
	drv->RPM(base, dump, imagesize);
	// uworld
	unsigned long long *result;
	result = (unsigned long long*)calloc(0x1FFFF, sizeof(unsigned long long));
	if (!result)  throw "variable initialization memory failed in function [ScanOffset]";
	long long count = FindPattern(dump, imagesize, "48 8D 15 ? ? ? ?", result);
	printf("[!] Total Fount Count %Id\n", count);
	for (int i = 0; i < count; i++)
	{
		if (*(unsigned int*)(dump + result[i] + 3) > 0x0f000000) continue;
		char name[512];
		name[0] = '\0';
		memcpy(name, (dump + result[i] + (*(unsigned int*)(dump + result[i] + 3)) + 7), 512);
		if (!wcsicmp((wchar_t *)name, L"BRO.ClearIDCLevel"))
		{
			printf("0x%-12IX BRO.ClearIDCLevel \n", result[i]);

			unsigned long long dec_out[5];
			if (FindPattern(dump + result[i] - 100, 200, "48 8D 05 ? ? ? ? 48 ? ? ? E8", dec_out))
			{
				unsigned long long dec_offset_2nd = result[i] - 100 + dec_out[0];

				unsigned int dec_offset_3rd = *(unsigned int*)(dump + dec_offset_2nd + 3);
				unsigned int uworld_function_offset = (unsigned int)(dec_offset_2nd + dec_offset_3rd + 7);
				printf("0x%-12X UWorld Call\n", uworld_function_offset);

				unsigned int uworldoffset = *(unsigned int*)(dump + dec_offset_2nd + dec_offset_3rd + 7 + 4 + 3);
				g_offset_uworld = (unsigned int)(dec_offset_2nd + dec_offset_3rd + 7 + 4 + 7 + uworldoffset);
				printf("0x%-12X UWorld Offset\n", g_offset_uworld);

				//
				break;
			}
		}
	}
	free(result);
	result = 0;

	// game inst
	unsigned long long instcall = FindPattern(dump, imagesize, "E8 ? ? ? ? 48 8B C8 33 D2 E8 ? ? ? ? 48 ? ? 48 ? ? 0F");
	unsigned int instcalloffset = (unsigned int)(instcall + *(unsigned long*)(dump + instcall + 1) + 5);
	printf("0x%-12X Inst Call\n", instcalloffset);
	g_offset_inst = *(unsigned int*)(dump + instcalloffset + FindPattern(dump + instcalloffset, 100, "48 8b ? ? ? ? ? 75 ?") + 3);
	printf("0x%-12X Inst\n", g_offset_inst);

	// level actors
	unsigned long long levelcall = FindPattern(dump, imagesize, "E8 ? ? ? ? 39 5C 24 48 7E 29");
	unsigned int levelcalloffset = (unsigned int)(levelcall + *(unsigned long*)(dump + levelcall + 1) + 5);
	printf("0x%-12X Level Call\n", levelcalloffset);
	printf("0x%-12X Actors Call\n", levelcalloffset);
	g_offset_level = *(unsigned int*)(dump + levelcalloffset + FindPattern(dump + levelcalloffset, 100, "48 8b 81 ? ? ? ?") + 3);
	printf("0x%-12X Level\n", g_offset_level);
	g_offset_actors = *(unsigned int*)(dump + levelcalloffset + FindPattern(dump + levelcalloffset, 500, "49 8b 85 ? ? ? ?") + 3);
	printf("0x%-12X Actors\n", g_offset_actors);


	// local controller
	unsigned long long localcall = FindPattern(dump, imagesize, "48 8B C8 33 D2 E8 ? ? ? ? 48 3B C6 0F 85 ? ? ? ?") + 5;
	unsigned int localcalloffset = (unsigned int)(localcall + *(unsigned long*)(dump + localcall + 1) + 5);
	printf("0x%-12X Local Call\n", localcalloffset);
	printf("0x%-12X Controller Call\n", localcalloffset);
	g_offset_local = *(unsigned int*)(dump + localcalloffset + FindPattern(dump + localcalloffset, 100, "48 8B 99 ? ? ? ?") + 3);
	printf("0x%-12X Local\n", g_offset_local);
	g_offset_controler = *(unsigned char*)(dump + localcalloffset + FindPattern(dump + localcalloffset, 300, "48 8b ? ? 4d") + 3);
	printf("0x%-12X Controller\n", g_offset_controler);


	// Chunk Size
	unsigned long long chunksizeprefix = FindPattern(dump, imagesize, "c1 ? ? 8b ? c1 ? 1f 03 ? 69 ? ? ? ? ? 44 2b f8");
	unsigned int chunksizeoffset = *(unsigned int*)(dump + chunksizeprefix + 12);
	printf("0x%-12X ChunkSize\n", chunksizeoffset);
	// Initialize Chunsize
	g_Chunksize = chunksizeoffset;

	unsigned long long gnamecall = FindPattern(dump, imagesize, "48 8D 3D ? ? ? ? 33 C0 B9 ? ? ? ? F3 48 AB 48 8D 3D ? ? ? ? B9 ? ? ? ? F3 48 AB 48 8B 3D");
	unsigned int gnameoffset = *(unsigned int*)(dump + gnamecall + 3);
	g_offset_gname = (unsigned int)(gnamecall + gnameoffset + 7);
	printf("0x%-12X GName\n", g_offset_gname);

	// actor id
	unsigned long long objidprefix = FindPattern(dump, imagesize, "48 8D 15 ? ? ? ? 48 8D 4C 24 ? E8 ? ? ? ? 45 33 C9 48 8D 0D ? ? ? ? 45 33 C0 48 8B 10 E8 ? ? ? ?");
	unsigned long long objidcalladdr = objidprefix + FindPattern(dump + objidprefix, 200, "E8 ? ? ? ? 48 8D 0D");
	unsigned int objidoffset = (unsigned int)(*(unsigned int*)(dump + objidcalladdr + 1) + objidcalladdr + 5);
	printf("0x%-12X ObjectId Call\n", objidoffset);
	g_offset_id = *(unsigned char*)(dump + objidoffset + FindPattern(dump + objidoffset, 500, "8b 5b ? e8 ? ? ? ? e8 ? ? ? ? e8 ? ? ? ?") + 2);
	printf("0x%-12X ActorId \n", g_offset_id);

	// player camera manager
	unsigned long long pcmprefix = FindPattern(dump, imagesize, "41 ff 90 ? ? ? ? ? 8b ? ? ? ? ? 48 85 c9 74 ? 48 8b 01 4c 8d");
	g_offset_playercamermgr = *(unsigned int*)(dump + pcmprefix + 10);
	printf("0x%-12X PlayerCameraManager\n", g_offset_playercamermgr);

	// self 48 89 5C 24 10 48 89 4C 24 08 55 56 57 41 54 41 55 41 56 41 57 48 8D 6C 24 D9 48 81 EC 90 ? ? ? 48
	//unsigned long long selfcall = FindPattern(dump, imagesize, "48 89 5C 24 10 48 89 4C 24 08 55 56 57 41 54 41 55 41 56 41 57 48 8D 6C 24 D9 48 81 EC 90 ? ? ? 48") + 5;
	//unsigned int selfcalloffset = (unsigned int)(localcall + *(unsigned long*)(dump + selfcall + 1) + 5);
	unsigned long long pawnprefix = FindPattern(dump, imagesize, "BF ? ? ? ? 89 3D ? ? ? ? 49 8B 8E ? ? ? ? 48 83 3D ? ? ? ? ?");
	g_offset_defaultpawn = *(unsigned int*)(dump + pawnprefix + 14);
	printf("0x%-12X Self\n", g_offset_defaultpawn);

	// mesh
	unsigned long long meshprefix = FindPattern(dump, imagesize, "48 8B 99 ? ? ? ? 48 ? ? 48 ? ? 0F 84 ? ? ? ? 0F 10");
	g_offset_mesh = *(unsigned int*)(dump + meshprefix + 3);
	printf("0x%-12X Mesh\n", g_offset_mesh);

	// health groggyhealth
	unsigned long long healthprefix = FindPattern(dump, imagesize, "0F 57 C0 0F 2F 81 ? ? ? ? 72 0C");
	g_offset_health = *(unsigned int*)(dump + healthprefix + 6);
	g_offset_groggyhealth = *(unsigned int*)(dump + healthprefix + 15);
	printf("0x%-12X Health\n", g_offset_health);
	printf("0x%-12X GroggyHealth\n", g_offset_groggyhealth);

	// DroppedItemArray
	unsigned long long droppeditemsprefix = FindPattern(dump, imagesize, "44 0F B6 81 ? ? ? ? 41 0F B6 C0 24 01 3A C2 74 13 41 80 E0 FE 44 0A C2 44 88 81 ? ? ? ? E9 ? ? ? ?");
	unsigned long long droppeditemsaddr = droppeditemsprefix + FindPattern(dump + droppeditemsprefix, 100, "E9 ? ? ? ?");
	unsigned int droppeditemscall = (unsigned int)(*(unsigned int*)(dump + droppeditemsaddr + 1) + droppeditemsaddr + 5);
	g_offset_droppeditems = *(unsigned int*)(dump + droppeditemscall + FindPattern(dump + droppeditemscall, 200, "4c 8d ? ? ? ? ? c7 45 d7") + 3);
	printf("0x%-12X DroppedItemArray\n", g_offset_droppeditems);

	// ItemPackage
	unsigned long long itempackageprefix = FindPattern(dump, imagesize, "48 8B 8F ? ? ? ? 48 63 D3 48 8B 14 D1 48");
	g_offset_itempackages = *(unsigned int*)(dump + itempackageprefix + 3);
	printf("0x%-12X ItemPackage\n", g_offset_itempackages);

	// UItem
	unsigned long long uitemprefix = FindPattern(dump, imagesize, "0F B6 F8 48 85 D2 74 13 4C 8B CE 4C 8B C5 49 8B CE ? ? ? ? ? ? ? ? ? ? ? ? ? ? ?");
	g_offset_uitem = *(unsigned int*)(dump + uitemprefix - 4);
	printf("0x%-12X UItem\n", g_offset_uitem);

	// RootComponent
	unsigned long long rootprefix = FindPattern(dump, imagesize, "83 F8 03 74 08 48 8B CB E8 ? ? ? ? B0 01 48 8B 4D ? 48 33 CC E8");
	unsigned long long rootaddr = rootprefix + FindPattern(dump + rootprefix, 50, "E8 ? ? ? ?");
	unsigned int rootcall = (unsigned int)(*(unsigned int*)(dump + rootaddr + 1) + rootaddr + 5);
	g_offset_root = *(unsigned int*)(dump + rootcall + FindPattern(dump + rootcall, 200, "48 8b ? ? ? ? ? 75 0d") + 3);
	printf("0x%-12X RootComponent\n", g_offset_root);

	// BoneArray ComponentToWorld
	unsigned long long bonesprefix = FindPattern(dump, imagesize, "41 3B 84 C8 ? ? ? ? 0F 8D ? ? ? ? 0F 10 ?");
	g_offset_bones = *(unsigned int*)(dump + bonesprefix + 4) - 8;
	g_offset_c2w = *(unsigned int*)(dump + bonesprefix + 17);
	printf("0x%-12X BoneArray\n", g_offset_bones);
	printf("0x%-12X ComponentToWorld\n", g_offset_c2w);

	// RelativeLocation
	unsigned long long realtivelocationprefix = FindPattern(dump, imagesize, "48 85 C0 74 23 0F 10 88 ?? ?? 00 00 0F 28 C1");
	g_offset_relative = *(unsigned int*)(dump + realtivelocationprefix + 8);
	printf("0x%-12X RelativeLocation\n", g_offset_relative);

	free(dump);
	dump = 0;
	printf("[!] Scan Complete\n");

	// gname
	g_GNames = ScanGNames(g_offset_gname);
	
}

void game::RefreshOffset()
{

	/* Outer
	E8 ? ? ? ? 45 0F B6 45 ? 48 8D 55 DF
	*/



	/*
	E8 ? ? ? ? E8 ? ? ? ?  E8 ? ? ? ? ? ? ? ? ? ? 48 8d ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? E8
	C1 E2 10 81 F2 ? ? ? ? 33 D3 89 17 E8  
	*/
	g_GObjects = decrypt_gobjects(drv->RPM<unsigned long long>(drv->GetGameModule() + 0x6C88F88  + 0x10));
	printf("0x%-12IX GObjects\n", g_GObjects);
	printf("[!] Scan Object Array\n");

	fclose(stdout);
	freopen("obj_scan.txt", "w", stdout);
	//0x166848
	int i = 0;
	unsigned long long obj = 0;
	int id = 0;
	do
	{
		string name = string("");
		obj = drv->RPM<unsigned long long>(g_GObjects + 0x18 * i);
		id = decrypt_objectid(drv->RPM<unsigned long long>(obj + g_offset_id));
		name.append(GetGNameById(id));
		size_t pos = name.rfind('/');
		if (pos != string::npos) name = string(name.substr(pos + 1, string::npos));
		reverse(name.begin(), name.end());
		unsigned long long parent = decrypt_outer(drv->RPM<unsigned long long>(obj + 0x18));
		while (parent)
		{
			id = decrypt_objectid(drv->RPM<unsigned long long>(parent + g_offset_id));
			string tmp = GetGNameById(id);
			pos = tmp.rfind('/');
			if (pos != string::npos) tmp = string(tmp.substr(pos + 1, string::npos));
			reverse(tmp.begin(), tmp.end());
			name.append("::").append(tmp);
			parent = decrypt_outer(drv->RPM<unsigned long long>(parent + 0x18));
			if (!parent) break;
		}
		if (obj)
		{
			reverse(name.begin(), name.end());

			
			printf("[ %0.6d ] \t [0x%0.6x] \t 0x%-11IX \t %0.6d \t %s\n", i, drv->RPM<unsigned int>(obj + 0x58), obj, decrypt_objectid(drv->RPM<unsigned long long>(obj + g_offset_id)), name.c_str());
		}
		
		i++;
	} 
	while (obj);
	fclose(stdout);
	freopen("CON", "w", stdout);
	printf("[!] Scan Object Array Completed [%d]\n", i );
	//fclose(stdout);
	//freopen("object.txt", "w", stdout);
	//for (size_t i = 0; i < 100; i++)
	//{
	//	unsigned long long ptr = drv->RPM<unsigned long long>(g_GObjects + 0x18 * i);
	//	unsigned long long enid = drv->RPM<unsigned long long>(ptr + g_offset_id);
	//	int id = decrypt_objectid(enid);
	//	printf("0x%-12IX %-12d %-10d %s\n", ptr, enid, id, GetGNameById(id).c_str());
	//}
	//fclose(stdout);
	//freopen("CON", "w", stdout);

	g_UWorld = decrypt_uworld(drv->RPM<unsigned long long>(drv->GetGameModule() + g_offset_uworld));
	printf("0x%-12IX UWorld\n", g_UWorld);
	g_UInst = decrypt_gameinst(drv->RPM<unsigned long long>(g_UWorld + g_offset_inst));
	printf("0x%-12IX UGameInst\n", g_UInst);
	g_ULevel = decrypt_level(drv->RPM<unsigned long long>(g_UWorld + g_offset_level));
	printf("0x%-12IX ULevel\n", g_ULevel);
	g_AActors = decrypt_actors(drv->RPM<unsigned long long>(g_ULevel + g_offset_actors));
	printf("0x%-12IX AActors\n", g_AActors);
	printf("0x%-12X AActorID\n", g_offset_id);
	g_ULocal = decrypt_local(drv->RPM<unsigned long long>(drv->RPM<unsigned long long>(g_UInst + g_offset_local)));
	printf("0x%-12IX Local\n", g_ULocal);
	g_AControl = decrypt_controller(drv->RPM<unsigned long long>(g_ULocal + g_offset_controler));
	printf("0x%-12IX Controller\n", g_AControl);
	g_UPlayerCameraManager = drv->RPM<unsigned long long>(g_AControl + g_offset_playercamermgr);
	printf("0x%-12IX PlayerCameraManager\n", g_UPlayerCameraManager);
	g_DefaultPawn = decrypt_property(drv->RPM<unsigned long long>(g_AControl + g_offset_defaultpawn));
	printf("0x%-12IX DefaultPawn\n", g_DefaultPawn);
	g_DefaultMesh = drv->RPM<unsigned long long>(g_DefaultPawn + g_offset_mesh);
	printf("0x%-12IX DefaulMesh\n", g_DefaultMesh);
	int entitycount = drv->RPM<unsigned int>(g_AActors + 0x8);
	printf("%-14d EntityCount\n", entitycount);
	AimMap.erase(AimMap.begin(), AimMap.end());
	// F R L
	
	/*
	for (int i = 0; i < 0x2000; i++)
	{
		unsigned long long targ = g_UPlayerCameraManager + i + 0x0;

		if (drv->RPM<float>(targ) == -9428.892578f)
		{
			if (drv->RPM<float>((targ + 0x4)) == 3444.159424f)
			{
				if (drv->RPM<float>((targ + 0x8)) == 6187.039551f)
				{
					printf("%X\t%s\r\n", i, "Location");
				}
			}
		}

		if (drv->RPM<float>(targ) == 55.00000f)
		{
			printf("%X\t%s\r\n", i, "Fov");
		}


		if (drv->RPM<float>(targ) == -21.43337822f)
		{
			if (drv->RPM<float>((targ + 0x4)) == -41.44004059f)
			{
				if (drv->RPM<float>((targ + 0x8)) == 9.421803474f)
				{
					printf("%X\t%s\r\n", i, "Roator");
				}
			}
		}
	}
	printf("[!] F.R.L Scan Complete\n");
	*/
	
}

bool cmp(const pair<unsigned long long, float>& a, const pair<unsigned long long, float>& b) {
	return a.second < b.second;
}


void game::FilterActors()
{

	if (autobot) dx->DrawString(false, (float)(WIDTH / 2.0 - FONT_SIZE / 2.0), (float)(HEIGHT / 2.0 - FONT_SIZE / 2.0), GREEN, "⊙");
	if (espitem) dx->DrawString(false, 5, 50, RED, "物品");
	if (espvehical) dx->DrawString(false, 45, 50, RED, "车辆");

	unsigned long long aactor_ptr = g_AActors;
	int entitycount = drv->RPM<int>(aactor_ptr + 0x8);
	dx->DrawString(false, 5, 20, RED, "Draw Count = %d Bot Target = %d", entitycount, AimMap.size());
	if (entitycount < 1) return;
	unsigned long long actors = drv->RPM<unsigned long long>(aactor_ptr);
	if (!actors) return;

	drv->RPM(g_UPlayerCameraManager + CAMERACACHE - 0x10, &FCameraCache, sizeof(FCameraCacheEntry));

	for (int i = 0; i < entitycount; i++)
	{
		unsigned long long actor = drv->RPM<unsigned long long>(actors + (unsigned long long)i * 8);
		if (!actor || actor == g_DefaultPawn) continue;

		int id = decrypt_objectid(drv->RPM<unsigned long long>(actor + g_offset_id));
		if (id > 1 && id < CachedNames.size())
		{

			if (esp && isPlayer(id))
			{
				Vector3 localLocation = FCameraCache.POV.Location;
				unsigned long long root = decrypt_property(drv->RPM<unsigned long long>(actor + g_offset_root));
				Vector3 actor_location = drv->RPM<Vector3>(root + g_offset_relative, sizeof(Vector3));
				Vector3 actorScreen = WorldToScreen(actor_location, FCameraCache);

				float distance = (actor_location - localLocation).Length() / 100.0f;
				// team
				if (decrypt_property(drv->RPM<unsigned long long>(actor + TEAM))) continue;
				float health = drv->RPM<float>(actor + g_offset_health);
				float groggyHealth = drv->RPM<float>(actor + g_offset_groggyhealth);

				if (abs(actor_location.x - localLocation.x) < 25001 && abs(actor_location.y - localLocation.y) < 25001 && (health > 0 || groggyHealth > 0))
				{
					float radarx = (actor_location.x - localLocation.x) / 10000 * 64 + (WIDTH - 167);
					float radary = (actor_location.y - localLocation.y) / 10000 * 64 + (HEIGHT - 160);
					dx->DrawString(true, radarx, radary, RED, "⊙");
				}

				if (inScreen(actorScreen))
				{
					unsigned long long mesh = drv->RPM<unsigned long long>(actor + g_offset_mesh);
					bool canVisual = drv->RPM<float>(mesh + LASTRENDERONSCREEN) == drv->RPM<float>(g_DefaultMesh + LASTRENDERONSCREEN);
					int headId = 15;
					Vector3 headLocation = GetBoneWithRotation(mesh, headId);
					actorScreen = WorldToScreen(headLocation, FCameraCache);

					if (canVisual && distance < 800)
					{
						float toCenterDistance = (float)(pow(actorScreen.x - WIDTH / 2.0, 2) + pow(actorScreen.y - HEIGHT / 2.0, 2));
						if (toCenterDistance < AIMLIMITEDSIZE) AimMap.insert_or_assign(actor, toCenterDistance);						
					}

					if (health > 0.0f) {
						if (actor == g_BestAimActor && autobot) // aimbot
						{
							dx->DrawString(true, actorScreen.x, actorScreen.y - 20.0f + (distance / 50) * 1.0f, RED, "[%.0f] [%.0f]", distance, health);
						}
						else
						{
							dx->DrawString(true, actorScreen.x, actorScreen.y - 20.0f + (distance / 50) * 1.0f, canVisual ? VISUAL : UNVISUAL, "[%.0f]", distance);
						}

						if (distance < 250)
						{
							DrawSkeleton(mesh, canVisual);
						}
					}
					else
					{
						if (groggyHealth > 0.0f) {
							dx->DrawString(true, actorScreen.x, actorScreen.y, WHITE, "倒[%0.0f][%0.0f]", distance, groggyHealth);
						}
					}
				}
			}

			if (espvehical && isVehicle(id))
			{
				Vector3 localLocation = FCameraCache.POV.Location;
				uint64_t root = decrypt_property(drv->RPM<unsigned long long>(actor + g_offset_root));
				Vector3 actor_location = drv->RPM<Vector3>(root + g_offset_relative, sizeof(Vector3));
				Vector3 actorScreen = WorldToScreen(actor_location, FCameraCache);
				float distance = (actor_location - localLocation).Length() / 100.0f;
				if (inScreen(actorScreen))
				{
					dx->DrawString(true, actorScreen.x, actorScreen.y, getColor(CachedNames[id]), "%s [%0.0f]", CachedNames[id].c_str(), distance);
				}
			}

			if (espitem && isItems(id))
			{
				Vector3 localLocation = FCameraCache.POV.Location;
				uint64_t root = decrypt_property(drv->RPM<unsigned long long>(actor + g_offset_root));
				Vector3 actor_location = drv->RPM<Vector3>(root + g_offset_relative, sizeof(Vector3));

				int count = drv->RPM<int>(actor + g_offset_droppeditems + 8);
				if (count < 1) continue;
				int z = 0;

				DroppedItem di[64];
				drv->RPM(drv->RPM<unsigned long long>(actor + g_offset_droppeditems), &di, sizeof(DroppedItem) * count);

				for (int j = 0; j < count; j++)
				{
					unsigned long long UItem = drv->RPM<unsigned long long>(di[j].group + g_offset_uitem);
					int uid = decrypt_objectid(drv->RPM<int>(UItem + g_offset_id));

					if (uid < CachedNames.size() &&  uid > 0 && strlen(CachedNames[uid].c_str()) < 7)
					{
						Vector3 goods_location = drv->RPM<Vector3>(di[j].group + g_offset_relative, sizeof(Vector3));
						Vector3 goods_screen = WorldToScreen(goods_location, FCameraCache);
						float d = (goods_location - localLocation).Length() / 100.0f;
						goods_screen.y -= (z++) * 8;
						dx->DrawString(true, goods_screen.x, goods_screen.y, getColor(CachedNames[uid]), "%s [%0.0f]", CachedNames[uid].c_str(), d);
					}
				}

			}

			if (espitem && isLoot(id))
			{
				Vector3 localLocation = FCameraCache.POV.Location;
				uint64_t root = decrypt_property(drv->RPM<unsigned long long>(actor + g_offset_root));
				Vector3 actor_location = drv->RPM<Vector3>( root + g_offset_relative, sizeof(Vector3));
				Vector3 actorScreen = WorldToScreen(actor_location, FCameraCache);
				float distance = (actor_location - localLocation).Length() / 100.0f;
				if (distance < 250.0f)
				{
					DWORD_PTR Items = drv->RPM<unsigned long long>(actor + g_offset_itempackages);
					int Count = drv->RPM<int>(actor + g_offset_itempackages + 8);
					if (Count < 1 || Count > 64) continue;
					uint64_t itemarray[64];
					drv->RPM(Items, &itemarray, 8 * Count);
					for (int j = 0; j < Count; j++)
					{
						int uid = decrypt_objectid(drv->RPM<int>(itemarray[j] + g_offset_id));
						if (uid < CachedNames.size() && strlen(CachedNames[uid].c_str()) < 7 && uid > 0)
						{
							actorScreen.y += 14;
							dx->DrawString(true, actorScreen.x, actorScreen.y, getColor(CachedNames[uid]), "%s [%0.0f]", CachedNames[uid].c_str(), distance);
						}
					}
				}
			}

			if (espitem && isAircaft(id))
			{
				Vector3 localLocation = FCameraCache.POV.Location;
				uint64_t root = decrypt_property(drv->RPM<unsigned long long>(actor + g_offset_root));
				Vector3 actor_location = drv->RPM<Vector3>(root + g_offset_relative, sizeof(Vector3));
				Vector3 actorScreen = WorldToScreen(actor_location, FCameraCache);
				float distance = (actor_location - localLocation).Length() / 100.0f;

				if (inScreen(actorScreen))
				{
					unsigned long long Items = drv->RPM<unsigned long long>(actor + g_offset_itempackages);
					int Count = drv->RPM<int>(actor + g_offset_itempackages + 8);
					if (Count < 1 || Count > 64) continue;
					unsigned long long itemarray[64];
					drv->RPM(Items, &itemarray, 8 * Count);
					dx->DrawString(true, actorScreen.x, actorScreen.y, BLUE, "%s [%0.0f]", "空投", distance);
					for (int j = 0; j < Count; j++)
					{
						int uid = decrypt_objectid(drv->RPM<int>(itemarray[j] + g_offset_id));
						if (uid < CachedNames.size() && strlen(CachedNames[uid].c_str()) < 7 && uid > 0)
						{
							actorScreen.y += 14;
							dx->DrawString(true, actorScreen.x, actorScreen.y, getColor(CachedNames[uid]), "%s [%0.0f]", CachedNames[uid].c_str(), distance);
						}
					}


				
				}
			}

		}
	}

	//if ((GetAsyncKeyState(VK_LBUTTON) & 0x8000) != 0 || (GetAsyncKeyState(VK_LSHIFT) & 0x8000) != 0) return;

	vector<pair<unsigned long long, float>> vec(AimMap.begin(), AimMap.end());
	sort(vec.begin(), vec.end(), cmp);
	if (vec.size() > 0)
	{
		if ((GetAsyncKeyState(VK_LBUTTON) & 0x8000) == 0 && (GetAsyncKeyState(VK_LSHIFT) & 0x8000) == 0)
		{
			g_BestAimActor = vec[0].first;
		}
	}

}

void game::Fire()
{
	if (!autobot) return;
	if ((GetAsyncKeyState(VK_LBUTTON) & 0x8000) == 0 && (GetAsyncKeyState(VK_LSHIFT) & 0x8000) == 0) return;
	if (!g_BestAimActor) return;
	if (!g_DefaultPawn) return;
	if (!g_DefaultMesh) return;
	unsigned long long mesh = drv->RPM<unsigned long long>(g_BestAimActor + g_offset_mesh);
	if (!mesh) return;
	unsigned long long root = decrypt_property(drv->RPM<unsigned long long>(g_BestAimActor + g_offset_root));
	if (!root) return;
	bool canVisual = drv->RPM<float>(mesh + LASTRENDERONSCREEN) == drv->RPM<float>(g_DefaultMesh + LASTRENDERONSCREEN);
	if (!canVisual) return;

	drv->RPM(g_UPlayerCameraManager + CAMERACACHE - 0x10, &FCameraCache, sizeof(FCameraCacheEntry));
	int headId = ((GetAsyncKeyState(VK_RBUTTON) & 0x8000) != 0) ? 5 : 15;
	Vector3 headLocation = GetBoneWithRotation(mesh, headId);

	uint64_t VehicleRiderComponent = drv->RPM<unsigned long long>(g_BestAimActor + VEHICLERIDERCOMPONENT);
	int SeatIndex = drv->RPM<int>(VehicleRiderComponent + SEATINDEX);
	Vector3 Velocity;

	if (SeatIndex == -1)
	{
		Velocity = drv->RPM<Vector3>(root + COMPONENTVELOCITY, sizeof(Vector3));
	}
	else {
		Velocity = drv->RPM<Vector3>(drv->RPM<unsigned long long>(VehicleRiderComponent + LASTVEHICLEPAWN) + REPLICATEDMOVEMENT, sizeof(Vector3));
	}

	float distance = (headLocation - FCameraCache.POV.Location).Length() / 100.0f;

	unsigned long long WeaponProcessor = drv->RPM<unsigned long long>(g_DefaultPawn + WEAPONPROCESSOR);
	unsigned long long EquippedWeapons = drv->RPM<unsigned long long>(WeaponProcessor + EQUIPPEDWEAPONS);
	unsigned char CurrentWeaponIndex = drv->RPM<unsigned char>(WeaponProcessor + EQUIPPEDWEAPONS + 0x20 + 0x1);
	float speed = 800.0f;
	if (CurrentWeaponIndex >= 0 && CurrentWeaponIndex < 3)
	{
		unsigned long long pWeapon = drv->RPM<unsigned long long>(EquippedWeapons + (unsigned long long)CurrentWeaponIndex * 8);
		if (pWeapon)
		{
			unsigned long long pData = drv->RPM<unsigned long long>(pWeapon + WEAPONTRAJECTORYDATA);
			float BulletSpeed = drv->RPM<float>(pData + TRAJECTORYCONFIG); // BulletSpeed
			float drag = drv->RPM<float>(pData + TRAJECTORYCONFIG + VDRAGCOEFFICIENT); // VDragCoefficient
			speed =  BulletSpeed * drag;
			if (speed > 1500) speed = 800.0f;
			if (speed < 100) speed = 800.0f;
			
		}
	}

	float flTime = distance / speed;

	Vector3 PredictedPos{0, 0, 0};
	PredictedPos.x = headLocation.x + (Velocity.x * flTime);
	PredictedPos.y = headLocation.y + (Velocity.y * flTime);
	float cz = 0.00f;
	if (distance > 100.0f)
	{
		float t = (distance - 100.000000f) / speed;
		cz = 0.500000f * 9.80665f * t * t * 95;
		PredictedPos.z = headLocation.z + (Velocity.z * t) + cz;
	}
	else
	{
		PredictedPos.z = headLocation.z + (Velocity.z * flTime);
	}

	unsigned long long AnimScriptInst = drv->RPM<unsigned long long>(g_DefaultMesh + ANIMSCRIPTINSTANCE);
	FRotator ControlRotation_CP = drv->RPM<FRotator>(AnimScriptInst + CONTROLROTATION_CP, sizeof(FRotator));
	FCameraCache.POV.Rotation = ControlRotation_CP;
	Vector3 aimScreen = WorldToScreen(PredictedPos, FCameraCache);

	int x = (int)(aimScreen.x - (WIDTH / 2.0));
	int y = (int)(aimScreen.y - (HEIGHT / 2.0));
	if (abs(x) < 400 && abs(y) < 300)
	{
		mouse_event(MOUSEEVENTF_MOVE, x, y, 0, 0);
	}
}


void game::HotKey()
{
	if (GetAsyncKeyState(VK_HOME) & 1)
	{
		RefreshOffset();
	}
	if (GetAsyncKeyState(VK_F8) & 1)
	{
		autobot = !autobot;
	}
	if (GetAsyncKeyState(VK_F5) & 1)
	{
		espitem = !espitem;
	}
	if (GetAsyncKeyState(VK_F6) & 1)
	{
		espvehical = !espvehical;
	}
	if (GetAsyncKeyState(VK_END) & 1)
	{
		//DebugOffset();
	}
}




