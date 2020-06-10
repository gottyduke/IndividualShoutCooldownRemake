#include "Serialization.h"

#include "DKUtil/Hash.hpp"


/*
 * data layout
 * - total size, size_t
 * - [formID, duration], UInt32 + float
 * - repeat for (total size) times
 */


void ShoutInfo::Clear()
{
	_data.clear();
}


bool ShoutInfo::Save(SKSE::SerializationInterface* a_intfc, UInt32 a_version) const
{
	a_intfc->OpenRecord(kHeader, kVersion);

	auto total = this->_data.size();
	if (!a_intfc->WriteRecordData(&total, sizeof total)) {
		_ERROR("Failed to write serialized data");
		return false;
	}

	for (auto& data : _data) {
		if (!a_intfc->WriteRecordData(&data, sizeof data)) {
			_ERROR("Failed to write serialized data");
			return false;
		}
	}
	
	return true;
}


bool ShoutInfo::Load(SKSE::SerializationInterface* a_intfc, UInt32 a_version)
{
	std::size_t total;
	if (!a_intfc->ReadRecordData(&total, sizeof total)) {
		_ERROR("Failed to read serialized data");
		return false;
	}
	
	for (auto i = 0; i < total; ++i) {
		std::pair<RE::FormID, std::pair<float, float>> data;

		if (!a_intfc->ReadRecordData(&data, sizeof data)) {
			continue;
		}

		if (!a_intfc->ResolveFormID(data.first, data.first)) {
			continue;
		}

		auto* shout = RE::TESForm::LookupByID<RE::TESShout>(data.first);
		if (!shout) {
			continue;
		}

		_data.insert(data);
	}
	
	return true;
}


void ShoutInfo::SaveCallback(SKSE::SerializationInterface* a_intfc)
{
	_MESSAGE("Saving skse file...");

	GetSingleton()->Save(a_intfc, kVersion);
}


void ShoutInfo::LoadCallback(SKSE::SerializationInterface* a_intfc)
{
	_MESSAGE("Loading skse file...");
	
	UInt32 type, version, length;

	while (a_intfc->GetNextRecordInfo(type, version, length)) {
		if (type != kHeader) {
			_ERROR("Failed to read serialized data, expected '%.4s' but encountered '%.4s'", DECODE(kHeader), DECODE(type));
			break;
		}

		GetSingleton()->Load(a_intfc, version);
	}
}


void ShoutInfo::RevertCallback(SKSE::SerializationInterface* a_intfc)
{
	_MESSAGE("Swapping skse files...");
	
	GetSingleton()->Clear();
}


std::pair<float, float>& ShoutInfo::operator[](const RE::FormID a_formId)
{
	if (!_data.count(a_formId)) {
		_data.emplace(std::make_pair(a_formId, std::make_pair(0.0f, 0.0f)));
	}
	
	return _data[a_formId];
}
