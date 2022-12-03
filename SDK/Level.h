#pragma once
#include <cstdint>
#include <functional>

class Level {
public:
	static uintptr_t* forEachPlayerCall;
	static uintptr_t* tickCall;
public:
	auto getAllPlayer()->std::vector<class Player*>;
public:
	//�����
	auto getTime()->int;															/*111*/
	auto setTime(int)->void;														/*112*/
	
	//�����Hook
	auto Tick()->void;																/*101*/
	auto forEachPlayer(std::function<bool(class Player&)>) -> void;					/*222 / 223 �������붨λcall����� */
};