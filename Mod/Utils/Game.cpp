﻿#include "Game.h"
#include "../Utils/Logger.h"
#include "../Utils/Utils.h"
#include "Player.h"
#include "Actor.h"
#include "GameMode.h"

float* Game::ArmsLength = nullptr;
bool Game::ModState = false;

uintptr_t SpeedDestroyBlock;

auto Game::init() -> void
{
	logF("Game::init is start runner……");
	Game::ModState = true;

	//定位修改攻击距离
	{
		//84 C0 74 ? C7 45 ? ? ? ? ? 48 8D 85 ? ? ? ? 48 8D 4D ? 44 0F 2F 25 ? ? ? ? 48 0F 43 C1
		auto sigOffset = FindSignature("84 C0 74 ? C7 45 ? ? ? ? ? 48 8D 85 ? ? ? ? 48 8D 4D ? 44 0F 2F 25 ? ? ? ? 48 0F 43 C1");
		auto offset = *reinterpret_cast<int*>(sigOffset + 52);
		ArmsLength = reinterpret_cast<float*>(sigOffset + 56 + offset);//52(22) 56(56-30=26)

		if (ArmsLength == 0x0 || sigOffset == 0x0) {
			logF("Survival mode ArmsLength not working!!!");
			ArmsLength = 0x00;
		}
		else {
			DWORD old_Page;
			bool b = VirtualProtect(ArmsLength, sizeof(float), PAGE_READWRITE, &old_Page);
			if (b) {
				logF("[Game::init]Survival mode ArmsLength is %lf,new Modify to %lf", *ArmsLength, 7.0f);
				*ArmsLength = 7.0f;
				VirtualProtect(ArmsLength, sizeof(float), old_Page, &old_Page);
			}

		}
	}

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

	//GameMode虚表地址获取
	{
		auto GameModeVTable_sigOffset = FindSignature("48 8D 05 ? ? ? ? 48 89 01 48 89 51 ? 48 C7 41 ? ? ? ? ? C7 41 ? ? ? ? ? 44 88 61");
		auto offsize = *reinterpret_cast<int*>(GameModeVTable_sigOffset + 3);
		auto GameModeVTables = reinterpret_cast<uintptr_t**>(GameModeVTable_sigOffset + offsize + 7);
		GameMode::SetVtables(GameModeVTables);
		if (GameModeVTable_sigOffset == 0x00 || offsize == 0x00) {
			logF("[GameMode::SetVtables] [Error]Find GameMode GameModeVTable_sigOffset Offset is no working!!!,GameModeVTable_sigOffset=0");
		}
		else {
			logF("[GameMode::SetVtables] GameModeVTable = %llX", GameModeVTables);
		}
	}

}


auto Game::exit() -> void
{
	//长臂管辖
	if (ArmsLength != 0x00) {
		DWORD old_Page;
		bool b = VirtualProtect(ArmsLength, sizeof(float), PAGE_READWRITE, &old_Page);
		if (b) {
			*ArmsLength = 3.0f;
			logF("[Game::exit]Survival mode ArmsLength Modify to %lf", *ArmsLength);
			VirtualProtect(ArmsLength, sizeof(float), old_Page, &old_Page);
		}
	}


	Game::ModState = false;
}