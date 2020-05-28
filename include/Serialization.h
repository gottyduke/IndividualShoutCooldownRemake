#pragma once

#include <chrono>

#include "RE/Skyrim.h"
#include "SKSE/Interfaces.h"


class ShoutInfo
{
public:
	ShoutInfo();
	ShoutInfo(ShoutInfo&) = default;
	ShoutInfo(ShoutInfo&&) = default;
	~ShoutInfo() = default;

	ShoutInfo& operator=(const ShoutInfo&) = default;
	ShoutInfo& operator=(ShoutInfo&&) = default;

	void Clear();
	bool Save(SKSE::SerializationInterface* a_intfc, UInt32 a_type, UInt32 a_version) const;
	bool Save(SKSE::SerializationInterface* a_intfc) const;
	bool Load(SKSE::SerializationInterface* a_intfc);
	void SetShout(RE::TESShout* a_shout);
	[[nodiscard]] RE::TESShout* GetShout() const { return _shout; }

private:
	RE::TESShout* _shout;
};
