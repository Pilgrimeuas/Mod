#pragma once
#include <string>
//#include <WinUser.h>
#include "../Mod/Utils/Utils.h"

class Module
{
protected:
	Module(int key,std::string name,std::string info);
public:
	virtual ~Module();
private:
	bool enabled = false;
	int keybind = 0x00;
	std::string modulename;
	std::string moduleinfo;

public:
	virtual int getKeybind();
	virtual void setKeybind(int key);
	virtual std::string getModuleName();
	virtual void onTick(class GameMode*);
	virtual void onKeyUpdate(int key, bool isDown);
	virtual void onEnable();
	virtual void onDisable();
	virtual bool onAttack(class Actor*);				// 返回值可以拦截该事件
	virtual bool onKnockback(class LocalPlayer*, struct vec3_t*);
	virtual void onStartDestroyBlock(class GameMode* gm,struct vec3_ti* Bpos, uint8_t* Face);
	virtual void setEnabled(bool enabled);
	virtual void toggle();
	virtual bool isEnabled();
};