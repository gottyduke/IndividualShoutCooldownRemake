#pragma once


namespace Events
{
	class ShoutEquipHandler final :
		public DKUtil::model::Singleton<ShoutEquipHandler>,
		public RE::BSTEventSink<RE::TESEquipEvent>
	{
	public:
		virtual RE::BSEventNotifyControl ProcessEvent(const RE::TESEquipEvent* a_event, [[maybe_unused]] RE::BSTEventSource<RE::TESEquipEvent>* a_eventSource) override;
	};
}