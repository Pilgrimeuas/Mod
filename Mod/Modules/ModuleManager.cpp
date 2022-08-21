#include "ModuleManager.h"

#include "Modules/HitBox.h"
#include "Modules/InstantDestroy.h"

//bool ModuleManager::isInit = false;
//std::vector<Module*> ModuleManager::moduleList = std::vector<Module*>();

//载入所有的Module到列表中
//每新建一个Module都在这里添加一次 new 
auto ModuleManager::Init()->void {
	if (isInit) return;

	moduleList.push_back((Module*)(new InstantDestroy()));
	moduleList.push_back((Module*)(new InstantDestroy()));

	isInit = true;
}


//关闭所有的 Module 并执行析构函数
auto ModuleManager::Disable()->void {
	if (!IsInitialized())
		return;
	for (auto pMod : moduleList) {
		if(pMod->isEnabled())
			pMod->setEnabled(false);
		delete[] pMod;
	}
}

auto ModuleManager::IsInitialized()->bool {
	return isInit;
}



auto ModuleManager::onKeyUpdate(int key, bool isenable)->void {
	if (!IsInitialized())
		return;
	for (auto pMod : moduleList) {
		pMod->onKeyUpdate(key, isenable);
	}
}

auto ModuleManager::onTick(GameMode* gm)->void {
	if (!IsInitialized())
		return;
	for (auto pMod : moduleList) {
		pMod->onTick(gm);
	}
}

auto ModuleManager::onAttack(Actor* actor)->bool {
	bool RunOriginalFun = true;
	if (!IsInitialized())
		return RunOriginalFun;
	for (auto pMod : moduleList) {
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
		if (!pMod->onKnockback(lp,v3))
			RunOriginalFun = false;
	}
	return RunOriginalFun;
}