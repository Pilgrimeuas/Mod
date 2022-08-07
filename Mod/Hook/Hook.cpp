﻿#include "Hook.h"
#include "../Utils/Logger.h"
#include "../Utils/Utils.h"
#include "Player.h"


ClientInstance* instance;

using PlayerKBCALL = void(__fastcall*)(Player*, vec3_t*);
PlayerKBCALL playercall;
uintptr_t playerkb;

using ClientInstance_Tick = void(__fastcall*)(ClientInstance* _this, void* a1);
ClientInstance_Tick clientInstance_Tickcall;
uintptr_t clientInstanceTick;

// 获取一个值 是否在屏幕上显示位置
using Is_ShowCoordinates_Tick = bool(__fastcall*)(void* _this);
Is_ShowCoordinates_Tick is_ShowCoordinates_Tickcall;
uintptr_t is_ShowCoordinatesTick;


using GetHungerValAddress_Tick = void* (__fastcall*)(void* _this, const char* a1,void* a2);
GetHungerValAddress_Tick getHungerValAddress_Tickcall;
uintptr_t getHungerValAddressTick;

//
using DestroyBlockingAddress = float (__fastcall*)(void* _this, void* a1, int a2, float a3);
DestroyBlockingAddress destroyBlockingAddresscall;
uintptr_t destroyBlockingAddress;


auto Hook::init() -> void
{
	logF("Hook::init is start runner……");

	playerkb = FindSignature("8B 02 89 81 ? ? 00 00 8B 42 04 89 81 ? ? 00 00 8B 42 08 89 81 ? ? 00 00 C3");
	Player::SpeedXOffset = *reinterpret_cast<int*>(playerkb + 4);
	Player::SpeedYOffset = *reinterpret_cast<int*>(playerkb + 13);
	Player::SpeedZOffset = *reinterpret_cast<int*>(playerkb + 22);
	MH_CreateHookEx((LPVOID)playerkb, &Hook::PlayerKB, &playercall);
	MH_EnableHook((LPVOID)playerkb);

	//clientInstance::Tick
	clientInstanceTick = FindSignature("48 89 5C 24 ?? 48 89 74 24 ?? 57 48 83 EC ?? 48 8B F9 48 8B 01");
	MH_CreateHookEx((LPVOID)clientInstanceTick, &Hook::ClientInstance_Tick, &clientInstance_Tickcall);
	MH_EnableHook((LPVOID)clientInstanceTick);

	//是否显示坐标 Tick
	is_ShowCoordinatesTick = FindSignature("48 83 EC ? 48 8B 49 ? 48 8B 01 FF 90 ? ? ? ? 48 85 C0 74 ? 48 8B 88");
	MH_CreateHookEx((LPVOID)is_ShowCoordinatesTick, &Hook::Is_ShowCoordinates_Tick, &is_ShowCoordinates_Tickcall);
	MH_EnableHook((LPVOID)is_ShowCoordinatesTick);

	//获取饥饿值的地址的函数  实际上被用来做修改玩家速度
	getHungerValAddressTick = FindSignature("4C 8B D1 44 0F B6 CA 49 BB ? ? ? ? ? ? ? ? 48 B8 ? ? ? ? ? ? ? ? 4C 33 C8 8B C2 4D 0F AF CB C1 E8 08 44 0F B6 C0 8B C2 4D 33 C8 C1 E8 10 4D 8B 42 08 4D 0F AF CB 0F B6 C8 4C 33 C9 8B C2 49 8B 4A 30 4D 0F AF CB 48 C1 E8 18 4C 33 C8 4D 0F AF CB 49 23 C9 48 C1 E1 04 49 03 4A 18 48 8B 41 08 49 3B C0 74 27 48 8B 09 3B 50 10 74 0E 48 3B C1 74 1A 48 8B 40 08 3B 50 10 75 F2 48 85 C0 49 0F 44 C0 49 3B C0 74 05 ? ? ? ? C3 48 8D 05 ? ? ? ? C3");
	MH_CreateHookEx((LPVOID)getHungerValAddressTick, &Hook::GetHungerValAddress_Tick, &getHungerValAddress_Tickcall);
	MH_EnableHook((LPVOID)getHungerValAddressTick);


	//获取能够加上偏移得出破坏进度的地址(第一个参数) 可用来快速破坏方块
	destroyBlockingAddress = FindSignature("48 89 5C 24 ? 48 89 6C 24 ? 56 57 41 56 48 83 EC 30 48 8B D9 0F 29 74 24 ? 48 8B 49 08");
	MH_CreateHookEx((LPVOID)destroyBlockingAddress, &Hook::DestroyBlocking, &destroyBlockingAddresscall);
	MH_EnableHook((LPVOID)destroyBlockingAddress);

}

auto Hook::exit() -> void {
	MH_DisableHook(MH_ALL_HOOKS);
	Sleep(10);
}

//无击退效果
auto Hook::PlayerKB(Player* player,vec3_t* kb) -> void
{
	//kb->y *= 3;
	//player->setSpeed(vec3_t(0.0f,5.0f,0.0f));
	//playercall(player,kb);
	/*
	auto p = (Player*)(instance->LocalPlayer());
	if(p != nullptr)
		p->setSpeed(vec3_t(0.0f, 2.0f, 0.0f));
	*/
	/*
	logF("this fun Player Ptr at: %llX", player);
	if (instance != nullptr) {
		logF("instance Ptr at: %llX", instance);
		logF("LocalPlayer Ptr at: %llX", instance->LocalPlayer());
		logF("no offset");
	}
	*/
}
//2.Hook后的函数 3.具有原来的功能的可以调用的函数
//MH_CreateHook(&MessageBoxW, &DetourMessageBoxW, reinterpret_cast<LPVOID*>(&fpMessageBoxW))
//Utils::FindSignatureModule("Minecraft.Windows.exe","8B 02 89 81 ? ? 00 00 8B 42 04 89 81 ? ? 00 00 8B 42 08 89 81 ? ? 00 00 C3");

auto Hook::ClientInstance_Tick(ClientInstance* _this, void* a1) -> void
{
	if (_this != nullptr) instance = _this;
	clientInstance_Tickcall(_this, a1);
}


auto Hook::Is_ShowCoordinates_Tick(void* _this)->bool
{
	is_ShowCoordinates_Tickcall(_this);
	return true;
}


// 实际很多变量都调用这个函数，速度 血量，饥饿，附加血量等
auto Hook::GetHungerValAddress_Tick(void* _this, const char* a1, void* a2)->void*
{
	auto ret = getHungerValAddress_Tickcall(_this, a1, a2);	// +0x84 = 132
	auto hunger = reinterpret_cast<float*>(reinterpret_cast<INT64>(ret) + 0x84);
	//速度
	if (*hunger == 0.1000000015f) {
		*hunger = 0.135f;
	}
	return ret;
}



auto Hook::DestroyBlocking(void* _this, void* a1, int a2, float a3)->float
{
	auto speedDestroy = reinterpret_cast<float*>(reinterpret_cast<INT64>(_this) + 0x24);
	if (*speedDestroy>0.0f&&*speedDestroy<1.0f) {
		*speedDestroy = 1.0f;
	}
	auto ret = destroyBlockingAddresscall(_this, a1,a2,a3);
	return ret;
}