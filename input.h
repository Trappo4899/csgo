#pragma once

class CInput
{
private:

	struct keystate_t
	{
		bool down;
		bool pressed;

		int		tick;
		int		oldtick;
	};

private:

	std::array<keystate_t, 0x100>	m_keys;
	POINT							m_cursor;
	std::string						m_buffer;

public:

	void update();

	void handle_wndproc(UINT message, WPARAM wp);

public:

	bool key_pressed(unsigned int key);

	bool key_held(unsigned int key);

	POINT cursor_position();

public:

	bool cursor_in_rect(float x, float y, float w, float h, bool show_bounds = false);
};

extern std::unique_ptr<CInput> g_input;