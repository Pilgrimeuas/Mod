﻿#include "Loader.h"
#include "Utils/Logger.h"
#include "Utils/Game.h"
#include "Hook/Hook.h"
#include "Utils/Utils.h"
#include "Player.h"

#include "Hook/KeyBoard.hpp"

Player* LocalPlayer = nullptr;
int hookret;
//C2 A9 4D 6F 6A 61 6E 67 20 41 42 00 00 00 00 00 0B 00 00 00 00 00 00 00 0F 00 00 00 00 00 00 00 C2 A9 4D 6F 6A 61 6E 67 20 41 42 00  +32

//在线程
void Loader::init(void* hmoudle)
{
	logF("DLL HMODULE: %llX", hmoudle);
	hookret = MH_Initialize();
	if (hookret != MB_OK)
	{
		logF("MH_Initialize Error ret is %i ,Mod Return", hookret);
		return;
	}
	
	Game::init();

	Hook::init();
	auto enableHook = MH_EnableHook(MH_ALL_HOOKS);
	logF("MH_EnableHook = %i", enableHook);
	if (enableHook != MH_OK) {
		logF("MH_EnableHook Error");
	}
	
	//捕获按键
	KeyBoard::init((HMODULE)hmoudle);

}

void Loader::exit(void* hmoudle)
{
	if (hookret)
	{
		logF("Hook::exit() Hook IS UnLoad");
		Hook::exit();
	}
	Game::exit();

	KeyBoard::exit((HMODULE)hmoudle);

	logF("Removing logger");
	Logger::Disable();
	//关闭被注入程序的时候会调用
}
