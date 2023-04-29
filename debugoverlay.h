#pragma once

class IVDebugOverlay
{
private:

	enum
	{
		ADDTEXTOVERLAY = 0,
		SCREENPOSITION = 13,
	};

public:

	void AddEntityTextOverlay(int ent_index, int line_offset, float duration, int r, int g, int b, int a, _Printf_format_string_ const char* format, ...)
	{
		VMT::call<ADDTEXTOVERLAY, void, int, int, float, int, int, int, int, _Printf_format_string_ const char*>(this, ent_index, line_offset, duration, r, g, b, a, format);
	}

	bool WorldToScreen(const Vector3& point, Vector3& screen)
	{
		/* https://gitlab.com/KittenPopo/csgo-2018-source/-/blob/main/engine/gl_rmain.cpp#L849 - calls this function */
		bool behind = VMT::call<SCREENPOSITION, int, const Vector3&, Vector3&>(this, point, screen);
		return behind == false;
	}
};