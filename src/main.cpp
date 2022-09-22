#include "Events.h"
#include "Serialization.h"


namespace
{
	void MessageHandler(SKSE::MessagingInterface::Message* a_msg)
	{
		if (a_msg->type == SKSE::MessagingInterface::kDataLoaded) {
			auto* source = RE::ScriptEventSourceHolder::GetSingleton();

			source->AddEventSink(Events::ShoutEquipHandler::GetSingleton());
			INFO("Shout equip handler registered"sv);
		}
	}
}


DLLEXPORT bool SKSEAPI SKSEPlugin_Load(const SKSE::LoadInterface* a_skse)
{
#ifndef NDEBUG 
	while (!IsDebuggerPresent()) { Sleep(100); }
#endif

	DKUtil::Logger::Init(Plugin::NAME, REL::Module::get().version().string());

	SKSE::Init(a_skse);

	INFO("{} v{} loaded", Plugin::NAME, Plugin::Version);

	const auto* messaging = SKSE::GetMessagingInterface();
	if (messaging->RegisterListener("SKSE", MessageHandler)) {
		INFO("Messaging interface registration successful"sv);
	} else {
		ERROR("Messaging interface registration failed!");
		return false;
	}

	const auto* serialization = SKSE::GetSerializationInterface();
	serialization->SetUniqueID(ShoutInfo::kHeader);
	serialization->SetSaveCallback(ShoutInfo::SaveCallback);
	serialization->SetLoadCallback(ShoutInfo::LoadCallback);
	serialization->SetRevertCallback(ShoutInfo::RevertCallback);

	return true;
}
