#pragma once

#include "DKUtil/Template.hpp"
#include "RE/Skyrim.h"


namespace Events
{
	class ShoutEquipHandler final :
		public SDM<ShoutEquipHandler>,
		public RE::BSTEventSink<RE::TESEquipEvent>
	{
	public:
		using EventResult = RE::BSEventNotifyControl;

		EventResult ProcessEvent(const RE::TESEquipEvent* a_event, [[maybe_unused]] RE::BSTEventSource<RE::TESEquipEvent>* a_eventSource) override;
	};
}