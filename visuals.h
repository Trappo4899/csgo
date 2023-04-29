#pragma once

class CVisuals
{
public:

	enum BOX_POSITION
	{
		TOP = 1,
		BOTTOM = 2,

		LEFT = 4,
		RIGHT = 8,
	};

private:

	Vector2 m_padding_top		= { };
	Vector2 m_padding_bottom	= { };
	Vector2 m_padding_left		= { };
	Vector2 m_padding_right		= { };

private:

	bool get_bounding_box(CBaseEntity* entity, Box& box);

private:

	void draw_box(Box box, Color col);
	void draw_bar(Box box, float val, float max, Color from, Color to, BOX_POSITION pos);

	void draw_text(Box box, vgui::HFont font, const wchar_t* text, Color col, int flags, BOX_POSITION pos);
	void draw_text(Box box, vgui::HFont font, const char* text, Color col, int flags, BOX_POSITION pos);

	void reset_padding();

private:

	void player(CBasePlayer* player);
	void weapon(CBaseEntity* weapon);

public:

	void think();
};