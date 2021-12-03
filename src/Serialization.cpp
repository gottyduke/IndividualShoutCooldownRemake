#include "Serialization.h"


void ShoutInfo::SaveCallback(SKSE::SerializationInterface* a_intfc)
{
	INFO("Saving skse file..."sv);

	if (!a_intfc->OpenRecord(kHeader, kVersion)) {
		ERROR("Failed to open record"sv)
	}

	auto total = GetSingleton()->_data.size();
	if (!a_intfc->WriteRecordData(&total, sizeof(total))) {
		ERROR("Failed to write serialized data"sv);
	}

	for (auto& data : GetSingleton()->_data) {
		if (!a_intfc->WriteRecordData(&data, sizeof(data))) {
			ERROR("Failed to write serialized data"sv);
		}
	}
}


void ShoutInfo::LoadCallback(SKSE::SerializationInterface* a_intfc)
{
	INFO("Loading skse file...");
	
	std::uint32_t type, version, length;
	while (a_intfc->GetNextRecordInfo(type, version, length)) {
		if (type != kHeader) {
			break;
		}

		std::size_t total;
		if (!a_intfc->ReadRecordData(&total, sizeof(total))) {
			ERROR("Failed to read serialized data"sv);
		}

		for (auto i = 0; i < total; ++i) {
			std::pair<RE::FormID, std::pair<float, float>> data;

			if (!a_intfc->ReadRecordData(&data, sizeof(data))) {
				continue;
			}

			if (!a_intfc->ResolveFormID(data.first, data.first)) {
				continue;
			}

			auto* shout = RE::TESForm::LookupByID<RE::TESShout>(data.first);
			if (!shout) {
				continue;
			}

			GetSingleton()->_data.insert(data);
		}
	}
}


void ShoutInfo::RevertCallback([[maybe_unused]] SKSE::SerializationInterface* a_intfc)
{
	INFO("Swapping skse files..."sv);
	
	GetSingleton()->_data.clear();
}


auto ShoutInfo::operator[](const RE::FormID a_formId)
-> std::pair<float, float>&
{
	if (!_data.count(a_formId)) {
		_data.emplace(std::make_pair(a_formId, std::make_pair(0.0f, 0.0f)));
	}
	
	return _data[a_formId];
}
