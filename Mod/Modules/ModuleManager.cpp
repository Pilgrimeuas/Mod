#include "ModuleManager.h"

#include "Modules/HitBox.h"
#include "Modules/InstantDestroy.h"
#include "Modules/NoKnockback.h"
#include "Modules/Traverse.h"
#include "Modules/ShowCoordinates.h"

//bool ModuleManager::isInit = false;
//std::vector<Module*> ModuleManager::moduleList = std::vector<Module*>();

//�������е�Module���б���
//ÿ�½�һ��Module�����������һ�� new 
auto ModuleManager::Init()->void {
	if (isInit) return;

	moduleList.push_back((Module*)(new HitBox()));
	moduleList.push_back((Module*)(new InstantDestroy()));
	moduleList.push_back((Module*)(new NoKnockback()));
	moduleList.push_back((Module*)(new Traverse()));
	moduleList.push_back((Module*)(new ShowCoordinates()));
	isInit = true;
}


//�ر����е� Module ��ִ����������
auto ModuleManager::Disable()->void {
	if (!IsInitialized())
		return;
	for (auto pMod : moduleList) {
		if(pMod->isEnabled())
			pMod->setEnabled(false);
		delete[] pMod;
	}
	isInit = false;
	moduleList.clear();
}

auto ModuleManager::IsInitialized()->bool {
	return isInit;
}



auto ModuleManager::onKeyUpdate(int key, bool isenable)->void {
	if (!IsInitialized())
		return;
	for (auto pMod : moduleList) {
		auto bindkey = pMod->getKeybind();
		if (bindkey != 0 && bindkey == key && pMod->checkcontrolkeys()) {
			switch (pMod->GetKeyMode())
			{
			case Hold:
				pMod->setEnabled(isenable);
				break;
			case Trigger:
				if (isenable) {
					pMod->onTrigger();
				}
				break;
			case Switch:
				if (isenable) {
					pMod->toggle();
				}
				break;
			}
		}
		pMod->onKeyUpdate(key, isenable);
	}
}

auto ModuleManager::onTick(GameMode* gm)->void {
	if (!IsInitialized())
		return;
	for (auto pMod : moduleList) {
		if (pMod->isEnabled())
			pMod->onTick(gm);
	}
}

auto ModuleManager::onAttack(Actor* actor)->bool {
	bool RunOriginalFun = true;
	if (!IsInitialized())
		return RunOriginalFun;
	for (auto pMod : moduleList) {
		if (pMod->isEnabled())
			if (!pMod->onAttack(actor))
				RunOriginalFun = false;
	}
	return RunOriginalFun;
}

auto ModuleManager::onKnockback(LocalPlayer* lp, vec3_t* v3)->bool {
	bool RunOriginalFun = true;
	if (!IsInitialized())
		return RunOriginalFun;
	for (auto pMod : moduleList) {
		if (pMod->isEnabled())
			if (!pMod->onKnockback(lp,v3))
				RunOriginalFun = false;
	}
	return RunOriginalFun;
}

auto ModuleManager::onActorTick(Actor* actor)->void {
	if (!IsInitialized())
		return;
	for (auto pMod : moduleList) {
		if(pMod->isEnabled())
			pMod->onActorTick(actor);
	}
}

auto ModuleManager::onLocalPlayerTick(LocalPlayer* lp)->void {
	if (!IsInitialized())
		return;
	for (auto pMod : moduleList) {
		if (pMod->isEnabled())
			pMod->onLocalPlayerTick(lp);
	}
}