#pragma once
#include "..\Mod\Utils\HMath.h"
#include "Actor.h"
#include "Mob.h"

class Player : public Mob
{
protected:
	static uintptr_t** vfTables;
public:
	template <typename TRet, typename... TArgs>
	static auto GetVFtableFun(int)->auto*;
	static auto GetVFtableFun(int)->uintptr_t*;
	static auto GetVFtables()->uintptr_t**;
	static auto SetVFtables(uintptr_t** vTables)->void;

public:
	
	static int Rot1;	//ƫ��ָ�� vec2_t ָ��
	static int Rot2;	//ƫ��ָ�� vec2_t ָ��

public:
	//ret->x ��ʾ��ֱ�����ֵ
	auto getRotEx1()->vec2_t*;
	//ret->x ��ʾ��ֱ�����ֵ
	auto getRotEx2()->vec2_t*;

public:
	//�����
	//44
	auto teleportTo(vec3_t*, bool, unsigned int, unsigned int)->void;

	auto displayChatMessage(class TextHolder*, class TextHolder*)->__int64;
};