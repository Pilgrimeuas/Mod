#include "FastViewPerspective.h"
#include "../../Utils/Game.h"
#include "../../Utils/Utils.h"

#include "GameMode.h"
#include "LocalPlayer.h"
#pragma execution_character_set("utf-8")

FastViewPerspective::FastViewPerspective() : Module(VK_F9, "FastViewPerspective", "����Ԥ���ڶ��˳��ӽ�") {
	//setEnabled(true);
}

auto FastViewPerspective::getBindKeyName()->std::string {
	//ret : CTRL + SHIFT + F
	std::string name = "(R) ";
	name += Utils::getKeybindName(this->getKeybind());
	return name;
}


auto FastViewPerspective::isToggle()->bool {
	return Game::IsKeyDown('R');
}

auto FastViewPerspective::onTick(GameMode* gm)->void {
	if (!isEnabled()) return;
	if (gm->GetLocalPlayer() == nullptr) return;
	return;
	//(�������ϣ� ����Rʱ���ƶ��ӽǲ��ƶ������ɿ�Rʱ����ı䷽��)
	static vec2_t srot(0,0);
	if (!isToggle()) {
		srot = *gm->GetLocalPlayer()->getRotEx2();
	}
	else {
		//�����ʾ�Ұ�����R
		//���Գ��������� �������ӽ�
		vec2_t nrot(srot.x,srot.y);
		gm->GetLocalPlayer()->setRot(&nrot);
	}
}

auto FastViewPerspective::onloadConfigFile(json& data)->void {
	setEnabled(config::readDataFromJson<bool>(data, "enable", true));
}
auto FastViewPerspective::onsaveConfigFile(json& data)->void {
	data["enable"] = isEnabled();
}