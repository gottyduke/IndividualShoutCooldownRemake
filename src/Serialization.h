#pragma once


class ShoutInfo
{
public:
	enum : std::uint32_t
	{
		kInvalid = static_cast<std::uint32_t>(-1),
		kVersion = 1000,
		kHeader = 'ISCR'
	};


	inline static ShoutInfo* GetSingleton()
	{
		static ShoutInfo shoutInfo;
		return std::addressof(shoutInfo);
	}


	ShoutInfo(const ShoutInfo&) = delete;
	ShoutInfo(ShoutInfo&&) = delete;
	ShoutInfo& operator=(const ShoutInfo&) = delete;
	ShoutInfo& operator=(ShoutInfo&&) = delete;

	// callback
	static void SaveCallback(SKSE::SerializationInterface* a_intfc);
	static void LoadCallback(SKSE::SerializationInterface* a_intfc);
	static void RevertCallback(SKSE::SerializationInterface* a_intfc);
	
	// accessor
	std::pair<float, float>& operator[](RE::FormID a_formId);
	
private:



	// formId, <record time, duration>
	std::unordered_map<RE::FormID, std::pair<float, float>> _data{};

	ShoutInfo() = default;
};
