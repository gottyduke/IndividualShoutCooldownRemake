#include "Events.h"


namespace Events
{
	auto SpellHandler::ProcessEvent(const RE::TESSpellCastEvent* a_event, [[maybe_unused]] RE::BSTEventSource<RE::TESSpellCastEvent>* a_eventSource)
	-> EventResult
	{
		if (!a_event) {
			return EventResult::kContinue;
		}

		auto* shout = static_cast<RE::TESShout*>(RE::TESForm::LookupByID(a_event->spellID));
		if (!shout) {
			return EventResult::kContinue;
		}
		
		_MESSAGE(shout->GetName());
		
		return EventResult::kContinue;
	}


	auto ShoutEquipHandler::ProcessEvent(const RE::TESEquipEvent* a_event, [[maybe_unused]] RE::BSTEventSource<RE::TESEquipEvent>* a_eventSource)
	-> EventResult
	{
		if (!a_event || !a_event->actor || !a_event->actor->IsPlayer() && !a_event->actor->IsPlayerRef()) {
			return EventResult::kContinue;
		}

		auto* shout = static_cast<RE::TESShout*>(RE::TESForm::LookupByID(a_event->baseObject));
		if (!shout) {
			return EventResult::kContinue;
		}

		if (a_event->equipped) {
			// recalculate cooldown
		} else {
			// record cooldown
		}
		
		return EventResult::kContinue;
	}
}
