#pragma once
#include "../Mod/Utils/Utils.h"


class GameMode {
protected:
	static uintptr_t** vfTables;
public:
	static auto GetVFtableFun(int)->uintptr_t*;
	static auto GetVFtables()->uintptr_t**;
	static auto SetVFtables(uintptr_t** vTables)->void;

// �������Hook�� ����ԭʼ���ܵĵ���
public:
	static uintptr_t* startDestroyBlockCall;
	static uintptr_t* attackCall;


//���þ���ԭʼ���ܵı�Hook�ĺ���
public:
	auto startDestroyBlock(vec3_ti* Bpos, uint8_t* Face, void* a1, void* a2)->bool;				/*1*/
	auto attack(class Actor*) ->bool;															/*14*/

// �����
public:

	
	auto destroyBlock(vec3_ti* Bpos, uint8_t* Face)->bool;			/*2*/

};
