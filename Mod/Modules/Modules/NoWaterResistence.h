﻿#pragma once
#include "../Module.h"

class NoWaterResistence : public Module {
public:
	NoWaterResistence();

	virtual auto onEnable() -> void override;
	virtual auto onloadConfigFile(json& data) -> void override;
	virtual auto onsaveConfigFile(json& data) -> void override;
};
