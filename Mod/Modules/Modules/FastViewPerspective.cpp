#pragma execution_character_set("utf-8")
#include "FastViewPerspective.h"
#include "../../Utils/Game.h"
#include "../../Utils/Utils.h"

#include "GameMode.h"
#include "LocalPlayer.h"


FastViewPerspective::FastViewPerspective() : Module(VK_F9, "FastViewPerspective", "����Ԥ���ڶ��˳��ӽ�") {
	//setEnabled(true);
}

auto FastViewPerspective::getBindKeyName()->std::string {
	//ret : CTRL + SHIFT + F
	std::string name = "(�����˼�) ";
	name += Module::getBindKeyName();
	return name;
}


auto FastViewPerspective::isToggle()->bool {
	return Game::IsMouseDown(VK_XBUTTON1);
	//return Game::IsKeyDown('R');
}

auto FastViewPerspective::onloadConfigFile(json& data)->void {
	setEnabled(config::readDataFromJson<bool>(data, "enable", true));
}
auto FastViewPerspective::onsaveConfigFile(json& data)->void {
	data["enable"] = isEnabled();
}