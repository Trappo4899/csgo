#pragma once

class CSGO;

class Client
{
private:

	Color m_log_col = Color(125, 94, 224, 255);

	std::vector<std::pair<std::string, float>> m_logs;

public:

	void log(const char* text);
	void draw_logs();

public:

	static BOOL init(HMODULE hModule);
};

extern std::unique_ptr<Client> g_cl;