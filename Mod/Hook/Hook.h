﻿#pragma once
#pragma execution_character_set("utf-8")
#include <string>
#include "../../Memory/MinHook.h"
#include "../Utils/HMath.h"
#include "ClientInstance.h"

template <typename T>
inline MH_STATUS MH_CreateHookEx(LPVOID pTarget, LPVOID pDetour, T** ppOriginal)
{
	return MH_CreateHook(pTarget, pDetour, reinterpret_cast<LPVOID*>(ppOriginal));
}

class Hook
{
public:
	static auto init() ->void;
	static auto exit() ->void;
	static auto LockSprinting(void* a, void* b) ->void;
	static auto SetVelocity(class Player* ,vec3_t*)->void*;
	static auto Actor_isInWater(class Actor*) -> bool;
	static auto Actor_getShadowRadius(class Actor*)->float;										//执行对象是所有生物 但不包括玩家
	static auto ClientInstance_Tick(ClientInstance*, void*)->void;
	static auto Is_ShowCoordinates_Tick(void*)->bool;
	static auto NoFallDamage_Tick(class Player*,float*)->void*;
	static auto Level_Tick(class Level*) -> void;
	//Player 虚表Hook
	static auto LocalPlayer_getCameraOffset(class LocalPlayer*)->vec2_t*;
	static auto Player_tickWorld(class Player*, class Tick*)->void;
	static auto Player_getShadowRadius(class Player*)->float;
	static auto Player_startSwimming(class Player*) -> void;

	static auto AllActor_Tick(class Actor*, float*, float)->float*;
	//static auto Actor_moveBBs(class Actor*, vec3_t*)->void*;
	static auto KeyUpdate(__int64, int)->void*;
	static auto MouseUpdate(__int64, char, char, __int16, __int16, __int16, __int16, char)->void;
	static auto RenderDetour(void*, class MinecraftUIRenderContext*)->void;
	static auto Draw_Text(class MinecraftUIRenderContext*,class BitmapFont*, struct RectangleArea const&, class TextHolder*, struct UIColor const& , float , float , struct TextMeasureData*, class CaretMeasureData*)->void;
	static auto sendMessage(void*, TextHolder*)->__int64;
	static auto getLocalPlayerViewPerspective(void*)->int;
	static auto level_startLeaveGame(class Level*) -> void;
public:
	//虚表Hook
	static auto GameMode_attack(class GameMode*, class Actor*)->bool;
	static auto GameMode_tick(class GameMode*)->void*;
	static auto GameMode_startDestroyBlock(class GameMode* _this, vec3_ti* a2, uint8_t* face, void* a3, void* a4)->bool;
	static auto GameMode_useItem(class GameMode*,class ItemStack*)->bool;
	static auto GameMode_useItemOn(class GameMode*, class ItemStack*, vec3_ti*, uint8_t*, vec3_t*, class Block*)->bool;

	static auto ServerPlayer_TickWorld(class ServerPlayer* _this, void* tick)->void*;
	static auto RemotePlayer_TickWorld(class RemotePlayer* _this) -> void*;						//由于该函数只是个空架子,所以只能接受一个参数
};