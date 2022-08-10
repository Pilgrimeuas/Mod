#include "Player.h"
#include "../Mod/Utils/Utils.h"

Player* Player::LocalPlayer = nullptr;

int Player::SpeedXOffset = 0;
int Player::SpeedYOffset = 0;
int Player::SpeedZOffset = 0;

int Player::PosXOffset1 = 0;
int Player::PosYOffset1 = 0;
int Player::PosZOffset1 = 0;
int Player::PosXOffset2 = 0;
int Player::PosYOffset2 = 0;
int Player::PosZOffset2 = 0;

int Player::XHitBoxOffset = 0;
int Player::YHitBoxOffset = 0;

int Player::YView1 = 0;
int Player::XView1 = 0;
int Player::YView2 = 0;
int Player::XView2 = 0;

auto Player::getSpeed()->vec3_t {
	if (SpeedXOffset == 0 || SpeedYOffset == 0 || SpeedZOffset == 0) {
		return vec3_t(0.0f, 0.0f, 0.0f);
	}
	float* Xspeed = (float*)(this + SpeedXOffset);
	float* Yspeed = (float*)(this + SpeedYOffset);
	float* Zspeed = (float*)(this + SpeedZOffset);
	return vec3_t(*Xspeed, *Yspeed, *Zspeed);
}

auto Player::setSpeed(vec3_t v) ->void {
	if (SpeedXOffset == 0 || SpeedYOffset == 0 || SpeedZOffset == 0) {
		return;
	}
	float* Xspeed = (float*)(this + SpeedXOffset);
	float* Yspeed = (float*)(this + SpeedYOffset);
	float* Zspeed = (float*)(this + SpeedZOffset);
	*Xspeed = v.x;
	*Yspeed = v.y;
	*Zspeed = v.z;
}

auto Player::getPos()->vec3_t {
	if (PosXOffset1 == 0) {
		return vec3_t(0.0f, 0.0f, 0.0f);
	}
	float* Xpos = (float*)(this + PosXOffset1);
	float* Ypos = (float*)(this + PosYOffset1);
	float* Zpos = (float*)(this + PosZOffset1);
	return vec3_t(*Xpos, *Ypos, *Zpos);
}

auto Player::getPos2()->vec3_t {
	if (PosXOffset2 == 0) {
		return vec3_t(0.0f, 0.0f, 0.0f);
	}
	float* Xpos = (float*)(this + PosXOffset2);
	float* Ypos = (float*)(this + PosYOffset2);
	float* Zpos = (float*)(this + PosZOffset2);
	return vec3_t(*Xpos, *Ypos, *Zpos);
}

auto Player::setPos(vec3_t p)->void {
	if (PosXOffset1 == 0) {				//后面的偏移都是根据这个来的，所以只需要判断这一个就可以
		return;
	}
	float* Xpos1 = (float*)(this + PosXOffset1);
	float* Ypos1 = (float*)(this + PosYOffset1);
	float* Zpos1 = (float*)(this + PosZOffset1);

	float* Xpos2 = (float*)(this + PosXOffset2);
	float* Ypos2 = (float*)(this + PosYOffset2);
	float* Zpos2 = (float*)(this + PosZOffset2);

	*Xpos1 = p.x;
	*Ypos1 = p.y;
	*Zpos1 = p.z;
	*Xpos2 = p.x + 0.5999756f;
	*Ypos2 = p.y + 1.80000305f;
	*Zpos2 = p.z + 0.60002518f;
}

auto Player::getHitBox()->vec2_t {
	if (XHitBoxOffset == 0 || YHitBoxOffset == 0) {
		return vec2_t(0.0f, 0.0f);
	}
	auto hbx = *(float*)(this + XHitBoxOffset);
	auto hby = *(float*)(this + YHitBoxOffset);
	return vec2_t(hbx, hby);
}

auto Player::setHitBox(vec2_t hb)->void {
	if (XHitBoxOffset == 0 || YHitBoxOffset == 0) {
		return;
	}
	*(float*)(this + XHitBoxOffset) = hb.x;
	*(float*)(this + YHitBoxOffset) = hb.y;
}

auto Player::resetHitBox()->void {
	Player::setHitBox(vec2_t(0.6000000238f, 1.799999952f));
}

auto Player::getViewYX()->const vec2_t {
	if (YView1 == 0 || XView1 == 0) {
		return vec2_t(0.0f, 0.0f);
	}
	auto viewy = *(float*)(this + YView1);
	auto viewx = *(float*)(this + XView1);
	return vec2_t(viewy, viewx);
}

auto Player::getViewYX2()->const vec2_t {
	if (YView2 == 0 || XView2 == 0) {
		return vec2_t(0.0f, 0.0f);
	}
	auto viewy = *(float*)(this + YView2);
	auto viewx = *(float*)(this + XView2);
	return vec2_t(viewy, viewx);
}

auto Player::onLocalPlayerTick()->void {
	LocalPlayer = this;
}

auto Player::onAllPlayerTick()->void {
	//判断是否大写锁定
	if (GETKEYSTATE(VK_CAPITAL)){
		if (this != LocalPlayer) {
			this->setHitBox(vec2_t(6.0f, 6.0f));
		}
	}
	else {
		this->resetHitBox();
	}
}