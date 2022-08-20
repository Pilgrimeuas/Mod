#include "../Mod/Utils/Utils.h"
#include "ServerPlayer.h"
#include "LocalPlayer.h"

uintptr_t** ServerPlayer::vfTables = nullptr;

template <typename TRet, typename... TArgs>
auto ServerPlayer::GetVFtableFun(int a)->auto* {
	return reinterpret_cast<TRet(__fastcall*)(TArgs...)>(vfTables[a]);
}

auto ServerPlayer::GetVFtableFun(int a)->uintptr_t* {
	return vfTables[a];
}

auto ServerPlayer::GetVFtables()->uintptr_t** {
	return vfTables;
}

auto ServerPlayer::SetVFtables(uintptr_t** vfTable)->void {
	vfTables = vfTable;
}


//�麯�� �ص�
uintptr_t* ServerPlayer::tickWorldCall = nullptr;

auto ServerPlayer::onAllPlayerTick()->void {
	return;
	//�ж��Ƿ������ ��д����
	if (1 || this->isPlayer()) {
		if (GETKEYSTATE(VK_CAPITAL)) {
			if (this != (Actor*)LocalPlayer::GetLocalPlayer()) {
				this->setHitBox(vec2_t(6.0f, 6.0f));
			}
		}
		else {
			this->resetHitBox();
		}
	}
}



//�麯��
//����ԭʼ���ܵĵ���
auto ServerPlayer::tickWorld(class struck* Tick)->void* {
	using Fn = void*(__fastcall*)(ServerPlayer*, class struck*);
	return reinterpret_cast<Fn>(tickWorldCall)(this, Tick);
}