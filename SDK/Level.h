#pragma once
#include <cstdint>
#include <functional>

class Level {
public:
	static uintptr_t* forEachPlayerCall;
public:
	auto getAllPlayer()->std::vector<class Player*>;
public:
	auto forEachPlayer(std::function<bool(class Player&)>)->void;					/*222 / 223 �������붨λcall����� */
public:
	//�����
	auto getTime()->int;															/*111*/
	auto setTime(int)->void;														/*112*/
	
};