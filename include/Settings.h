#pragma once

#include "Json2Settings.h"


namespace J2S = Json2Settings;

class Settings
{
public:
	Settings() = delete;

	static bool LoadSettings(bool a_dumpParse = false);

private:
	static constexpr auto FILE_NAME = R"(Data\SKSE\Plugins\IndividualShoutCooldownRemake.json)";
};