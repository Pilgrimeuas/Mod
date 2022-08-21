#pragma once
#include <string>
//#include <WinUser.h>
#include "../Mod/Utils/Utils.h"

enum KeyMode {
	Trigger = 0,						//���� ���� onTrigger();
	Switch = 1,							//����һ��  isenable ��ֵ���л�һ�� ͬʱҲ�ᴥ����Ӧ�� onEnable()  onDisable()
	Hold = 2							//���� ���� onEnable()   �ɿ�����  onDisable()
};


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
	KeyMode km = KeyMode::Trigger;
public:
	void SetKeyMode(KeyMode km);
	KeyMode GetKeyMode();
public:
	virtual int getKeybind();
	virtual void setKeybind(int key);
	virtual std::string getModuleName();
	virtual void onTick(class GameMode*);
	virtual void onKeyUpdate(int key, bool isDown);
	virtual void onTrigger();
	virtual void onEnable();
	virtual void onDisable();
	virtual bool onAttack(class Actor*);				// ����ֵ�������ظ��¼�
	virtual bool onKnockback(class LocalPlayer*, struct vec3_t*);
	virtual void onActorTick(class Actor*);
	virtual void onLocalPlayerTick(class LocalPlayer*);
	virtual void setEnabled(bool enabled);
	virtual void toggle();
	virtual bool isEnabled();
};