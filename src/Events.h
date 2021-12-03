#pragma once


namespace Events
{
	class ShoutEquipHandler final :
		public RE::BSTEventSink<RE::TESEquipEvent>
	{
	public:
		inline static ShoutEquipHandler* GetSingleton()
		{
			static ShoutEquipHandler handler;
			return std::addressof(handler);
		}


		ShoutEquipHandler(const ShoutEquipHandler&) = delete;
		ShoutEquipHandler(ShoutEquipHandler&&) = delete;
		ShoutEquipHandler& operator=(const ShoutEquipHandler&) = delete;
		ShoutEquipHandler& operator=(ShoutEquipHandler&&) = delete;


		RE::BSEventNotifyControl ProcessEvent(const RE::TESEquipEvent* a_event, [[maybe_unused]] RE::BSTEventSource<RE::TESEquipEvent>* a_eventSource) override;

	private:
		ShoutEquipHandler() = default;
	};
}