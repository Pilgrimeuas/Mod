#pragma once
#include "../Mod/Utils/Utils.h"


class GameMode {
protected:
	static uintptr_t** vTables;
public:
	static auto GetVtableFun(int)->uintptr_t*;
	static auto SetVtables(uintptr_t** vTables)->void;

// �������Hook�� ����ԭʼ���ܵĵ���
public:
	static uintptr_t* startDestroyBlockCall;


//���þ���ԭʼ���ܵı�Hook�ĺ���
public:
	auto startDestroyBlock(vec3_ti* Bpos, uint8_t* Face, void* a1, void* a2)->bool;

// �����
public:

	
	auto destroyBlock(vec3_ti* Bpos, uint8_t* Face)->bool;			/*2*/

};
