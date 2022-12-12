#pragma execution_character_set("utf-8")
#include "GameTimeLock.h"
#include "GameMode.h"
#include "LocalPlayer.h"
#include "Level.h"
#include "Game.h"

GameTimeLock::GameTimeLock() : Module(0, "GameTimeLock", "����Ϸʱ��̶���һ�����õ�ʱ��,����ı���ʵʱ��") {
	AddIntUIValue("ʱ��", &time, 0, 1000000,true);
	AddButtonUIEvent("�峿", false, [this]() {
		time = 0;
		if (Game::localplayer->isValid() && Game::localplayer->getLevel()) {
			Game::localplayer->getLevel()->setTime(time);
		}
	});
	AddButtonUIEvent("����", true, [this]() {
		time = 6000;
		if (Game::localplayer->isValid() && Game::localplayer->getLevel()) {
			Game::localplayer->getLevel()->setTime(time);
		}
	});
	AddButtonUIEvent("����", true, [this]() {
		time = 12000;
		if (Game::localplayer->isValid() && Game::localplayer->getLevel()) {
			Game::localplayer->getLevel()->setTime(time);
		}
	});
	AddButtonUIEvent("��ҹ", true, [this]() {
		time = 18000;
		if (Game::localplayer->isValid() && Game::localplayer->getLevel()) {
			Game::localplayer->getLevel()->setTime(time);
		}
	});
}

auto GameTimeLock::onTick(GameMode* gm)->void {
	return;
	auto lp = gm->GetLocalPlayer();
	if (lp && lp->getLevel()) {
		if (isEnabled()) {
			lp->getLevel()->setTime(time);
		}
		else {
			time = lp->getLevel()->getTime();
		}
	}
}

auto GameTimeLock::onLevelTick(Level* level)->void
{
	if (isEnabled()) {
		level->setTime(time);
	}
	else {
		time = level->getTime();
	}
}

auto GameTimeLock::onloadConfigFile(json& data)->void {
	setEnabled(config::readDataFromJson<bool>(data, "enable", false));
	time = config::readDataFromJson<int>(data, "time", 0);
}

auto GameTimeLock::onsaveConfigFile(json& data)->void {
	data["enable"] = isEnabled();
	data["time"] = time;
}