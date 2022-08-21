﻿#include "Loader.h"
#include "Utils/Logger.h"
#include "Utils/Game.h"
#include "Hook/Hook.h"
#include "Utils/Utils.h"
#include "Player.h"
#include "Modules/ModuleManager.h"

int hookret;
//C2 A9 4D 6F 6A 61 6E 67 20 41 42 00 00 00 00 00 0B 00 00 00 00 00 00 00 0F 00 00 00 00 00 00 00 C2 A9 4D 6F 6A 61 6E 67 20 41 42 00  +32

//在线程
void Loader::init(void* hmoudle)
{
	logF("DLL HMODULE: %llX", hmoudle);
	logF("Minecraft.Windows.exe base: %llX", Utils::getBase());

	hookret = MH_Initialize();
	if (hookret != MH_OK)
	{
		logF("MH_Initialize Error ret is %i ,Mod Return", hookret);
		return;
	}
	
	Game::init();
	Hook::init();
	ModuleManager::Init();

	auto enableHook = MH_EnableHook(MH_ALL_HOOKS);
	logF("MH_EnableHook = %i", enableHook);
	if (enableHook != MH_OK) {
		logF("MH_EnableHook Error");
	}
	

}

void Loader::exit(void* hmoudle)
{
	if (hookret == MH_OK)
	{
		logF("Hook::exit() Hook IS UnLoad");
		Hook::exit();
	}
	Game::exit();

	logF("Removing logger");
	Logger::Disable();
	//关闭被注入程序的时候会调用
}
