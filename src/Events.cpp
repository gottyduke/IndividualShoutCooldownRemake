#include "Events.h"
#include "Serialization.h"


namespace Events
{
	auto ShoutEquipHandler::ProcessEvent(const RE::TESEquipEvent* a_event, [[maybe_unused]] RE::BSTEventSource<RE::TESEquipEvent>* a_eventSource)
	-> RE::BSEventNotifyControl
	{
		if (!a_event || !a_event->actor || !a_event->actor->IsPlayer() && !a_event->actor->IsPlayerRef()) {
			return RE::BSEventNotifyControl::kContinue;
		}

		const auto form = a_event->baseObject;
		auto* shout = static_cast<RE::TESShout*>(RE::TESForm::LookupByID(form));
		if (!shout) {
			return RE::BSEventNotifyControl::kContinue;
		}
		auto* player = RE::PlayerCharacter::GetSingleton();
		if (!player) {
			return RE::BSEventNotifyControl::kContinue;
		}

		auto& runtimeData = player->GetActorRuntimeData();
		auto* process = runtimeData.currentProcess;
		if (!process) {
			return RE::BSEventNotifyControl::kContinue;
		}

		auto* highData = process->high;
		if (!highData) {
			return RE::BSEventNotifyControl::kContinue;
		}

		auto* calendar = RE::Calendar::GetSingleton();
		const auto now = calendar->GetCurrentGameTime() * 3600 * 24 / calendar->GetTimescale();

		auto& time = (*ShoutInfo::GetSingleton())[form];

		if (a_event->equipped) {
			float remaining;
			
			if (time.first == 0.0f) {
				// first time equipping, no previous data found
				// proceed with new cooldown
				remaining = 0.0f;
			} else {
				// recalculate cooldown
				remaining = time.second - (now - time.first);
				remaining = remaining < 0.0f ? 0.0f : remaining;
			}
			
			highData->voiceRecoveryTime = remaining;
		} else {
			// write record
			time = std::move(std::make_pair(now, highData->voiceRecoveryTime));
		}
		
		return RE::BSEventNotifyControl::kContinue;
	}
}
