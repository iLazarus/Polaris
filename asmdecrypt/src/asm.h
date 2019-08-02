#pragma once

extern "C" unsigned long long decrypt_class(unsigned long long encrypt);
extern "C" unsigned long long decrypt_outer(unsigned long long encrypt);
extern "C" unsigned long long decrypt_gobjects(unsigned long long encrypt);
extern "C" unsigned long long decrypt_uworld(unsigned long long encrypt);
extern "C" unsigned long long decrypt_gameinst(unsigned long long encrypt);
extern "C" unsigned long long decrypt_level(unsigned long long encrypt);
extern "C" unsigned long long decrypt_actors(unsigned long long encrypt);
extern "C" unsigned long long decrypt_local(unsigned long long encrypt);
extern "C" unsigned long long decrypt_controller(unsigned long long encrypt);
extern "C" unsigned long long decrypt_property(unsigned long long encrypt);
extern "C" unsigned int decrypt_objectid(unsigned long long encrypt);
extern "C" unsigned int decrypt_objectnumber(unsigned long long encrypt);