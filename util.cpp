#include "includes.h"

std::wstring util::string_to_wstring(const std::string& string)
{
	return std::wstring(string.begin(), string.end());
}

std::string util::wstring_to_string(const std::wstring& string)
{
	return std::string(string.begin(), string.end());
}

void util::wait_for_object(tFunction func)
{
	while (!func())
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(5));
	}
}