#pragma once

#include "DKUtil/Template.hpp"
#include "RE/Skyrim.h"


namespace Events
{
	class ShoutCastHandler final :
		public DKUtil::Template::SDM<ShoutCastHandler>,
		public RE::BSTEventSink<RE::BSAnimationGraphEvent>
	{
	public:
		using EventResult = RE::BSEventNotifyControl;

		EventResult ProcessEvent(const RE::BSAnimationGraphEvent* a_event, [[maybe_unused]] RE::BSTEventSource<RE::BSAnimationGraphEvent>* a_eventSource) override;

	private:
		RE::BSFixedString _anim{ "BeginCastVoice" };
	};


	class PlayerLoadHandler final :
		public DKUtil::Template::SDM<PlayerLoadHandler>,
		public RE::BSTEventSink<RE::TESObjectLoadedEvent>
	{
	public:
		using EventResult = RE::BSEventNotifyControl;

		EventResult ProcessEvent(const RE::TESObjectLoadedEvent* a_event, RE::BSTEventSource<RE::TESObjectLoadedEvent>* a_eventSource) override;
	};


	bool AnimationGraphEventHandler(RE::BSTEventSink<RE::BSAnimationGraphEvent>* a_sink);
}