#pragma once

typedef bool(__stdcall* tFunction)();

namespace util
{
	std::wstring string_to_wstring(const std::string& string);
	std::string wstring_to_string(const std::wstring& string);

	void wait_for_object(tFunction func);

	template<typename In = PVOID, typename Out = PVOID>
	Out force_cast(In in)
	{
		union
		{
			In input;
			Out output;
		}

		u = { in };

		return u.output;
	}
}