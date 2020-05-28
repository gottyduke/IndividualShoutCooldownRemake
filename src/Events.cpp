#include "Events.h"


namespace Events
{
	auto ShoutCastHandler::ProcessEvent(const RE::BSAnimationGraphEvent* a_event, [[maybe_unused]] RE::BSTEventSource<RE::BSAnimationGraphEvent>* a_eventSource)
	-> EventResult
	{
		if (!a_event || !a_event->holder || !a_event->holder->IsPlayer() && !a_event->holder->IsPlayerRef()) {
			return EventResult::kContinue;
		}

		if (a_event->tag == _anim) {
			// process shout
		}
		
		return EventResult::kContinue;
	}


	auto PlayerLoadHandler::ProcessEvent(const RE::TESObjectLoadedEvent* a_event, RE::BSTEventSource<RE::TESObjectLoadedEvent>* a_eventSource)
	-> EventResult
	{
		if (!a_event) {
			return EventResult::kContinue;
		}

		// sink
		auto* const player = RE::PlayerCharacter::GetSingleton();
		if (a_event->formID == player->formID) {
			AnimationGraphEventHandler(ShoutCastHandler::GetSingleton());
		}

		// process serialize
		
		return EventResult::kContinue;
	}
	
	
	bool AnimationGraphEventHandler(RE::BSTEventSink<RE::BSAnimationGraphEvent>* a_sink)
	{
		auto* const player = RE::PlayerCharacter::GetSingleton();
		RE::BSAnimationGraphManagerPtr graphManager;
		player->GetAnimationGraphManager(graphManager);
		
		if (graphManager) {
			auto sinked = false;
			
			for (auto& animationGraph : graphManager->graphs) {
				if (sinked) {
					break;
				}

				auto eventSource = animationGraph->GetEventSource<RE::BSAnimationGraphEvent>();
				for (auto& sink : eventSource->sinks) {
					if (sink == a_sink) {
						sinked = true;
						break;
					}
				}
			}

			if (!sinked) {
				graphManager->graphs.front()->GetEventSource<RE::BSAnimationGraphEvent>()->AddEventSink(a_sink);
				_MESSAGE("Registered animation event handler");

				return true;
			}
		}
		return false;
	}
}
