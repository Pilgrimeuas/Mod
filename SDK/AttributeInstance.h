#pragma once

enum Attribute : __int64 {
	HEALTH = 25769804032,						//25769804032
	MOVEMENT_SPEED = 38654705921				//���� Player��292������� Player::getSpeed 38654705921
};

class AttributeInstance {
public:
	static int getCurrentValueoffset;

public:
	auto getCurrentValue()->float;
};