#pragma once

enum Attribute : __int64 {
	HEALTH = 30064771328,						//25769804032 30064771328
	MOVEMENT_SPEED = 38654705921				//���� Player��292������� Player::getSpeed 38654705921
};

class AttributeInstance {
public:
	static int getCurrentValueoffset;

public:
	auto getCurrentValue()->float;
};