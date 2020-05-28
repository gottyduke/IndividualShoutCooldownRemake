#include "version.h"

#include "Events.h"
#include "Hooks.h"
#include "Settings.h"

#include "SKSE/API.h"


namespace
{
	void MessageHandler(SKSE::MessagingInterface::Message* a_msg)
	{
		if (a_msg->type == SKSE::MessagingInterface::kDataLoaded) {
			auto* source = RE::ScriptEventSourceHolder::GetSingleton();
			
			source->AddEventSink(Events::ShoutEquipHandler::GetSingleton());
			_MESSAGE("Shout equip handler registered");

			source->AddEventSink(Events::SpellHandler::GetSingleton());
			_MESSAGE("Spell cast handler registered");
		}
	}
}


extern "C"
{
	bool SKSEPlugin_Query(const SKSE::QueryInterface* a_skse, SKSE::PluginInfo* a_info)
	{
		SKSE::Logger::OpenRelative(FOLDERID_Documents, L"\\My Games\\Skyrim Special Edition\\SKSE\\IndividualShoutCooldownRemake.log");
		SKSE::Logger::UseLogStamp(true);
		SKSE::Logger::SetPrintLevel(SKSE::Logger::Level::kDebugMessage);
		SKSE::Logger::SetFlushLevel(SKSE::Logger::Level::kDebugMessage);
		SKSE::Logger::TrackTrampolineStats(true);

		_MESSAGE("IndividualShoutCooldownRemake v%s", ISCR_VERSION_VERSTRING);

		a_info->infoVersion = SKSE::PluginInfo::kVersion;
		a_info->name = "ISCR";
		a_info->version = ISCR_VERSION_MAJOR;

		if (a_skse->IsEditor()) {
			_FATALERROR("Loaded in editor, marking as incompatible!\n");
			return false;
		}

		const auto ver = a_skse->RuntimeVersion();
		if (ver <= SKSE::RUNTIME_1_5_39) {
			_FATALERROR("Unsupported runtime version %s!", ver.GetString().c_str());
			return false;
		}

		return true;
	}


	bool SKSEPlugin_Load(const SKSE::LoadInterface* a_skse)
	{
		_MESSAGE("IndividualShoutCooldownRemake loaded");

		if (!Init(a_skse)) {
			return false;
		}

		if (Settings::LoadSettings()) {
			_MESSAGE("Settings loaded successfully");
		} else {
			_FATALERROR("Failed to load json settings!\n");
			return false;
		}

		const auto* const messaging = SKSE::GetMessagingInterface();
		if (messaging->RegisterListener("SKSE", MessageHandler)) {
			_MESSAGE("Messaging interface registration successful");
		} else {
			_FATALERROR("Messaging interface registration failed!\n");
			return false;
		}

		if (!SKSE::AllocTrampoline(1 << 6)) {
			_FATALERROR("Failed to allocate trampoline");
			return false;
		}

		if (Hooks::InstallHooks()) {
			_MESSAGE("Hooks installed successfully");
		} else {
			_FATALERROR("Failed to install hooks!\n");
			return false;
		}

		return true;
	}
};
