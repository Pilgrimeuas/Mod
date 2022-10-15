#include "ShowCoordinates.h"
#pragma execution_character_set("utf-8")

ShowCoordinates::ShowCoordinates() : Module(0, "ShowCoordinates", "������ǿ����ʾ���Ͻ�����") {
	//setEnabled(true);
}

auto ShowCoordinates::onloadConfigFile(json& data)->void {
	setEnabled(config::readDataFromJson<bool>(data, "enable", true));
}
auto ShowCoordinates::onsaveConfigFile(json& data)->void {
	data["enable"] = isEnabled();
}