#pragma once

#include "DKUtil/Template.hpp"
#include "RE/Skyrim.h"


namespace RE
{
	class TESObjectREFR;

	struct TESSpellCastEvent
	{
		// members
		NiPointer<TESObjectREFR>	caster;
		FormID						spellID{};
	};
}


namespace Events
{
	using EventResult = RE::BSEventNotifyControl;

	class SpellHandler final :
		public DKUtil::Template::SDM<SpellHandler>,
		public RE::BSTEventSink<RE::TESSpellCastEvent>
	{
	public:
		EventResult ProcessEvent(const RE::TESSpellCastEvent* a_event, [[maybe_unused]] RE::BSTEventSource<RE::TESSpellCastEvent>* a_eventSource) override;
	};
	
	
	class ShoutEquipHandler final :
		public DKUtil::Template::SDM<ShoutEquipHandler>,
		public RE::BSTEventSink<RE::TESEquipEvent>
	{
	public:
		EventResult ProcessEvent(const RE::TESEquipEvent* a_event, [[maybe_unused]] RE::BSTEventSource<RE::TESEquipEvent>* a_eventSource) override;
	};
}