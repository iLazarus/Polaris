#pragma once

extern "C" unsigned long long decrypt_uworld(unsigned long long uworld_encrypted);
extern "C" unsigned long long decrypt_gameinst(unsigned long long gameinst_encrypt);
extern "C" unsigned long long decrypt_level(unsigned long long level_encrypt);
extern "C" unsigned long long decrypt_actors(unsigned long long actors_encrypt);
extern "C" unsigned long long decrypt_local(unsigned long long local_encrypt);
extern "C" unsigned long long decrypt_controller(unsigned long long controller_encrypt);
extern "C" unsigned long long decrypt_property(unsigned long long geranal_encrypt);
extern "C" unsigned int decrypt_objectid(unsigned long long geranal_encrypt);