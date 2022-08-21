#pragma once
#include <string>


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
	virtual bool onAttack(class Actor*);				// ����ֵ�������ظ��¼�
	virtual bool onKnockback(class LocalPlayer*, struct vec3_t*);
	virtual void setEnabled(bool enabled);
	virtual void toggle();
	virtual bool isEnabled();
};