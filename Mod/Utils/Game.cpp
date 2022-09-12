﻿#include "Game.h"
#include "../Utils/Logger.h"
#include "../Utils/Utils.h"
#include "Player.h"
#include "Actor.h"
#include "AttributeInstance.h"
#include "GameMode.h"
#include "../Modules/ModuleManager.h"

bool Game::ModState = false;
ModuleManager* Game::modmag = nullptr;
LocalPlayer* Game::localplayer = nullptr;
BitmapFont* Game::mcfont = nullptr;
ClientInstance* Game::Cinstance = nullptr;

auto Game::init() -> void
{
	logF("[Game::init] is start runner");

	Game::ModState = true;
	Game::modmag = new ModuleManager;
	Game::modmag->Init();
	logF("[ModuleManager::Disable] now init");


	//获取生物位置指针的偏移
	{
		
		//48 89 5C 24 ? 57 48 83 EC ? F3 0F 10 02 48 8B D9 F3 0F 58 81
		/*auto ActorPos_sigOffset = FindSignature("48 89 5C 24 ? 57 48 83 EC ? F3 0F 10 02 48 8B D9 F3 0F 58 81");
		auto Xoffset = *reinterpret_cast<int*>(ActorPos_sigOffset + 21);
		Actor::PosXOffset1 = Xoffset;
		Actor::PosYOffset1 = Xoffset + 4;
		Actor::PosZOffset1 = Xoffset + 8;
		Actor::PosXOffset2 = Xoffset + 12;
		Actor::PosYOffset2 = Xoffset + 16;
		Actor::PosZOffset2 = Xoffset + 20;

		Actor::XHitBoxOffset = Xoffset + 24;
		Actor::YHitBoxOffset = Xoffset + 28;
		if (ActorPos_sigOffset == 0x00) {
			logF("[Game::init] [Error]Find Actor SetPostion/HitBox Offset is no working!!!,ActorPos_sigOffset=0");
		}*/
	}

	//获取玩家视角的偏移地址 +15
	{
		auto PlayerView_sigOffset = FindSignature("0F B6 D0 48 8B CE E8 ? ? ? ? F2 0F 10 86 ? ? ? ? F2 0F 11 86");
		auto offset = *reinterpret_cast<int*>(PlayerView_sigOffset + 15);
		Player::YView1 = offset;
		Player::XView1 = offset + 4;
		Player::YView2 = offset + 8;
		Player::XView2 = offset + 12;
		if (PlayerView_sigOffset == 0x00) {
			logF("[Game::init] [Error]Find Player PlayerView_sigOffset Offset is no working!!!,PlayerView_sigOffset=0");
		}
	}

	//获取 获取玩家血量函数的相关偏移
	{
		auto getHealthFun_sigOffset = FindSignature("48 8D 15 ? ? ? ? 48 8B CE FF 90 ? ? ? ? F3 0F 10 88 ? ? ? ? F3 0F 2C C9 66 0F 6E C1 0F 5B C0 8D 41 ? 0F 2F C1 0F 42 C8 85 C9");
		auto offset = *reinterpret_cast<int*>(getHealthFun_sigOffset + 3);
		auto HEALTHVal = *reinterpret_cast<__int64*>(getHealthFun_sigOffset + 7 + offset);

		auto vtoffset = *reinterpret_cast<int*>(getHealthFun_sigOffset + 12);
		auto gvoffset = *reinterpret_cast<int*>(getHealthFun_sigOffset + 20);
		Actor::GetAttributeInstance_HealthFunVT = vtoffset;
		AttributeInstance::getCurrentValueoffset = gvoffset;

		if (getHealthFun_sigOffset == 0x00) {
			logF("[Game::init] [Error]Find Player getHealthFun_sigOffset Offset is no working!!!,getHealthFun_sigOffset=0");
		}
		if (Attribute::HEALTH != HEALTHVal) {
			logF("[Game::init] [Error]Attribute::HEALTH is Error,should is :%ll", HEALTHVal);
		}
		if (vtoffset == 0x00) {
			logF("[Game::init] [Error]vtoffset == 0x00 ");
		}
		if (gvoffset == 0x00) {
			logF("[Game::init] [Error]gvoffset == 0x00 ");
		}
	}
}


auto Game::exit() -> void
{
	Game::modmag->Disable();
	delete[] Game::modmag;
	logF("[ModuleManager::Disable] now Disale");

	Game::ModState = false;
}

auto Game::GetModuleManager()->ModuleManager* {
	return Game::modmag;
}


auto Game::IsKeyDown(int key)->bool {
	static uintptr_t keyMap = 0;
	if (keyMap == 0x00) {
		auto sigOffset = FindSignature("4C 8D 05 ? ? ? ? 89 54 24 ? 88 4C 24");
		if (sigOffset != 0x0) {
			int offset = *reinterpret_cast<int*>((sigOffset + 3));      // Get Offset from code
			keyMap = sigOffset + offset + /*length of instruction*/ 7;  // Offset is relative
			logF("KeyMap: %llX", keyMap);
		}
	}
	// All keys are mapped as bools, though aligned as ints (4 byte)
	// key0 00 00 00 key1 00 00 00 key2 00 00 00 ...
	return *reinterpret_cast<bool*>(keyMap + ((uintptr_t)key * 0x4));
}

/// <summary>
/// 判断一个按键是否按下
/// </summary>
/// <param name="key"></param>
/// <returns>如果判断时已经按下，则等到松开时再返回true</returns>
auto Game::IsKeyPressed(int key)->bool {
	if (IsKeyDown(key)) {
		while (IsKeyDown(key))
			Sleep(1);
		return true;
	}
	return false;
}
