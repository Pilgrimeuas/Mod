﻿#pragma once
#include "../Mod/Utils/Utils.h"


class GameMode {
protected:
	static uintptr_t** vfTables;
public:
	template <typename TRet, typename... TArgs>
	static auto GetVFtableFun(int)->auto*;
	static auto GetVFtableFun(int)->uintptr_t*;
	static auto GetVFtables()->uintptr_t**;
	static auto SetVFtables(uintptr_t** vTables)->void;

// 虚表函数被Hook后 具有原始功能的调用
public:
	static uintptr_t* startDestroyBlockCall;
	static uintptr_t* attackCall;
	static uintptr_t* tickCall;

//调用具有原始功能的被Hook的函数
public:
	auto startDestroyBlock(vec3_ti* Bpos, uint8_t* Face, void* a1, void* a2)->bool;				/*1*/
	auto tick()->void*;																			/*9错  8*/
	auto attack(class Actor*) ->bool;															/*14*/

// 虚表函数
public:

	auto destroyBlock(vec3_ti* Bpos, uint8_t* Face)->bool;			/*2*/
	

};
