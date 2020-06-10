#include "Events.h"
#include "Serialization.h"


namespace Events
{
	auto ShoutEquipHandler::ProcessEvent(const RE::TESEquipEvent* a_event, [[maybe_unused]] RE::BSTEventSource<RE::TESEquipEvent>* a_eventSource)
	-> EventResult
	{
		if (!a_event || !a_event->actor || !a_event->actor->IsPlayer() && !a_event->actor->IsPlayerRef()) {
			return EventResult::kContinue;
		}

		const auto form = a_event->baseObject;
		auto* shout = static_cast<RE::TESShout*>(RE::TESForm::LookupByID(form));
		if (!shout) {
			return EventResult::kContinue;
		}
		
		auto* process = RE::PlayerCharacter::GetSingleton()->currentProcess;
		if (!process) {
			return EventResult::kContinue;
		}

		auto* highData = process->high;
		if (!highData) {
			return EventResult::kContinue;
		}

		auto* calendar = RE::Calendar::GetSingleton();
		const auto now = calendar->GetCurrentGameTime() * 3600 * 24 / calendar->GetTimescale();

		auto* shoutInfo = ShoutInfo::GetSingleton();
		auto& time = (*shoutInfo)[form];

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
		
		return EventResult::kContinue;
	}
}
