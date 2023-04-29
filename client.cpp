#include "includes.h"

#pragma warning(disable : 4996)

std::unique_ptr<Client>		g_cl		( new Client	);
std::unique_ptr<CSGO>		g_csgo		( new CSGO		);
std::unique_ptr<Renderer>	g_render	( new Renderer	);
std::unique_ptr<CFeatures>  g_features	( new CFeatures	);
std::unique_ptr<CInput>		g_input		( new CInput	);
std::unique_ptr<CMenu>		g_menu		( new CMenu		);

BOOL Client::init(HMODULE hModule)
{
	AllocConsole();
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "r", stdin);

	auto ret = g_csgo->setup();

	if (ret != 0x0)
	{
		std::string str = "Setup Failed: (0x" + std::to_string(ret) + ")";
		MessageBoxA(NULL, str.c_str(), "scouseware", MB_OK);
		FreeLibraryAndExitThread(hModule, 1);
	}

	while (!GetAsyncKeyState(VK_END))
	{
		Sleep(100);
	}

	FreeConsole();
	FreeLibraryAndExitThread(hModule, 0);
}

void Client::log(const char* text)
{
	auto str = (std::string("[scouseware] ") + std::string(text) + "\n");

	g_csgo->m_cvar->ConsoleColorPrintf(m_log_col, str.c_str());

	m_logs.push_back({ str, (float)g_csgo->m_system->GetCurrentTime() });
}

void Client::draw_logs()
{
	static const float max_time = 5.f;

	std::vector<std::pair<std::string, float>> logs = { };

	for (int i = 0; i < m_logs.size(); i++)
	{
		auto log = m_logs.at(i);

		if (g_csgo->m_system->GetCurrentTime() > (log.second + max_time) ||
			log.first.empty())
		{
			continue;
		}

		// auto time_percent = g_csgo->m_system->GetCurrentTime() / (log.second + max_time);

		g_render->text(g_render->m_font_csgo_small,
			log.first.c_str(),
			5,
			((g_csgo->m_surface->GetTextSize(g_render->m_font_csgo_small, log.first.c_str())[1] * (i + 1)) + 2),
			0,
			m_log_col
		);

		logs.push_back(log);
	}

	m_logs = logs;
}