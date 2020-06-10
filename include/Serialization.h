#pragma once


#include "DKUtil/Template.hpp"
#include "RE/Skyrim.h"
#include "SKSE/Interfaces.h"


class ShoutInfo final :
	public SDM<ShoutInfo>
{
public:
	enum : UInt32
	{
		kInvalid = static_cast<UInt32>(-1),
		kVersion = 1000,
		kHeader = 'ISCR'
	};

	
	// serialize
	void Clear();
	bool Save(SKSE::SerializationInterface* a_intfc, UInt32 a_version) const;
	bool Load(SKSE::SerializationInterface* a_intfc, UInt32 a_version);

	// callback
	static void SaveCallback(SKSE::SerializationInterface* a_intfc);
	static void LoadCallback(SKSE::SerializationInterface* a_intfc);
	static void RevertCallback(SKSE::SerializationInterface* a_intfc);
	
	// accessor
	std::pair<float, float>& operator[](RE::FormID a_formId);
	
private:
	// formId, record time, duration
	std::unordered_map<RE::FormID, std::pair<float, float>> _data{};
};
