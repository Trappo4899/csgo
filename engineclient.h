#pragma once

class INetChannelInfo;

struct player_info_t
{
	uint64_t			version;			// 0x0
	uint64_t			xuid;				// 0x8
	char				name[128];			// 0x10
	int					userID;				// 
	char				guid[32 + 1];
	uint32_t			friendsID;
	char				friendsName[128];
	bool				fakeplayer;
	bool				ishltv;
	unsigned int		customFiles[4];
	unsigned char		filesDownloaded;

};

class IVEngineClient
{
private:

	enum
	{
		GETSCREENSIZE = 5,
		SERVERCMD = 6,
		CLIENTCMD = 7,
		GETPLAYERINFO = 8,
		ISCONSOLEVISIBLE = 11,
		GETLOCALPLAYERINDEX = 12,
		GETVIEWANGLES = 18,
		SETVIEWANGLES = 19,
		ISINGAME = 26,
		CONSOLEPRINTF = 30,
		GETNETCHANNELINFO = 78,
	};

public:

	void GetScreenSize(int& w, int& h)
	{
		VMT::call<GETSCREENSIZE, void, int&, int&>(this, std::ref(w), std::ref(h));
	}

	void ServerCmd(const char* szCmdString, bool bReliable = true)
	{
		VMT::call<SERVERCMD, void, const char*, bool>(this, szCmdString, bReliable);
	}

	void ClientCmd(const char* szCmdString)
	{
		VMT::call<CLIENTCMD, void, const char*>(this, szCmdString);
	}

	bool GetPlayerInfo(int entnum, player_info_t* pInfo)
	{
		return VMT::call<GETPLAYERINFO, bool, int, player_info_t*>(this, entnum, pInfo);
	}

	bool IsConsoleVisible()
	{
		return VMT::call<ISCONSOLEVISIBLE, bool>(this);
	}

	int GetLocalPlayerIdx()
	{
		return VMT::call<GETLOCALPLAYERINDEX, int>(this);
	}

	void GetViewAngles(Vector3& viewangles)
	{
		VMT::call<GETVIEWANGLES, void, Vector3&>(this, viewangles);
	}

	void SetViewAngles(Vector3& viewangles)
	{
		VMT::call<SETVIEWANGLES, void, Vector3&>(this, viewangles);
	}

	bool IsInGame()
	{
		return VMT::call<ISINGAME, bool>(this);
	}

	void ConsolePrintf(int pos, _Printf_format_string_ const char* fmt, ...)
	{
		VMT::call<CONSOLEPRINTF, int, const char*>(this, fmt);
	}

	INetChannelInfo* GetNetChannelInfo()
	{
		return VMT::call<GETNETCHANNELINFO, INetChannelInfo*>(this);
	}
};