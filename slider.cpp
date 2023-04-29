#include "includes.h"

CSliderInt::CSliderInt()
{
	m_name			= { };

	m_position		= { };
	m_size			= { };

	m_max			= { };
	m_min			= { };
	m_val			= { };

	m_min_val_char	= { };
	m_max_val_char	= { };
	m_val_char		= { };

	m_sliding		= { };
	m_hovered		= { };
}

CSliderInt::CSliderInt(std::string name, int max, int min, int val, std::string val_char, std::string min_val_char, std::string max_val_char)
{
	m_name			= name;

	m_position		= { };
	m_size			= { 0.f, 19.f };

	m_max			= max;
	m_min			= min;
	m_val			= val;

	m_min_val_char	= min_val_char;
	m_max_val_char	= max_val_char;
	m_val_char		= val_char;

	m_sliding		= { };
	m_hovered		= { };
}

void CSliderInt::think(Vector2 position, Vector2 group_size)
{
	/* make it so that the width of the 
	slider is relative to menu size */
	m_size[0] = (group_size[0] / 1.75f);

	auto text_size = g_csgo->m_surface->GetTextSize(g_render->m_font_menu, m_name.c_str());

	g_render->rect(			position[0] - 1,	position[1]     + text_size[1], m_size[0] + 2,					m_size[1] - text_size[1] + 2,	g_menu->m_dark_outline);
	g_render->filled_rect(	position[0],		position[1] + 1 + text_size[1], m_size[0],						m_size[1] - text_size[1],		g_menu->m_light_base);
	g_render->filled_rect(	position[0],		position[1] + 1 + text_size[1], ((m_val * m_size[0]) / m_max),	m_size[1] - text_size[1],		g_menu->m_accent);

	auto col = Color(175, 175, 175);

	if (g_input->cursor_in_rect(position[0] - 2, position[1] - 2, m_size[0] + 6, m_size[1] + 6, false))
	{
		col = Color(200, 200, 200);

		if (g_input->key_pressed(VK_LBUTTON))
		{
			m_sliding = true;
		}
	}
	else if (m_sliding)
	{
		col = Color(200, 200, 200);
	}

	auto val_str = std::to_string(m_val);

	if (m_val == m_min && m_min_val_char.size())
	{
		if (m_min_val_char.size() > 1)
		{
			val_str = m_min_val_char;
		}
		else
		{
			val_str += m_min_val_char;
		}
	}
	else if (m_val == m_max && m_max_val_char.size())
	{
		if (m_max_val_char.size() > 1)
		{
			val_str = m_max_val_char;
		}
		else
		{
			val_str += m_max_val_char;
		}
	}
	else
	{
		val_str += m_val_char;
	}

	g_render->text(g_render->m_font_menu, m_name, position[0], position[1], 0, col);
	g_render->text(g_render->m_font_menu, val_str, (position[0] + m_size[0]) - g_csgo->m_surface->GetTextSize(g_render->m_font_menu, val_str.c_str())[0], position[1], 0, col);

	if (m_sliding)
	{
		auto pixels = (g_input->cursor_position().x - position[0]);

		auto clmp = std::clamp<float>(pixels, 0.f, m_size[0]);

		m_val = (clmp / m_size[0]) * m_max;

		if (!g_input->key_held(VK_LBUTTON))
		{
			m_sliding = false;
		}
	}
}

CSliderFlt::CSliderFlt()
{
	m_name			= { };

	m_position		= { };
	m_size			= { };

	m_max			= { };
	m_min			= { };
	m_val			= { };

	m_min_val_char	= { };
	m_max_val_char	= { };
	m_val_char		= { };

	m_sliding		= { };
	m_hovered		= { };
}

CSliderFlt::CSliderFlt(std::string name, float max, float min, float val, std::string val_char, std::string min_val_char, std::string max_val_char)
{
	m_name			= name;

	m_position		= { };
	m_size			= { 0.f, 19.f };

	m_max			= max;
	m_min			= min;
	m_val			= val;

	m_min_val_char	= min_val_char;
	m_max_val_char	= max_val_char;
	m_val_char		= val_char;

	m_sliding		= { };
	m_hovered		= { };
}

void CSliderFlt::think(Vector2 position, Vector2 group_size)
{
	/* make it so that the width of the
	slider is relative to menu size */
	m_size[0] = (group_size[0] / 1.75f);

	auto text_size = g_csgo->m_surface->GetTextSize(g_render->m_font_menu, m_name.c_str());

	g_render->rect(position[0] - 1, position[1] + text_size[1], m_size[0] + 2, m_size[1] - text_size[1] + 2, g_menu->m_dark_outline);
	g_render->filled_rect(position[0], position[1] + 1 + text_size[1], m_size[0], m_size[1] - text_size[1], g_menu->m_light_base);
	g_render->filled_rect(position[0], position[1] + 1 + text_size[1], ((m_val * m_size[0]) / m_max), m_size[1] - text_size[1], g_menu->m_accent);

	auto col = Color(175, 175, 175);

	if (g_input->cursor_in_rect(position[0] - 2, position[1] - 2, m_size[0] + 6, m_size[1] + 6, false))
	{
		col = Color(200, 200, 200);

		if (g_input->key_pressed(VK_LBUTTON))
		{
			m_sliding = true;
		}
	}
	else if (m_sliding)
	{
		col = Color(200, 200, 200);
	}

	auto val_str = std::to_string(m_val);

	val_str = val_str.substr(val_str.size() - 5);

	if (m_val == m_min && m_min_val_char.size())
	{
		if (m_min_val_char.size() > 1)
		{
			val_str = m_min_val_char;
		}
		else
		{
			val_str += m_min_val_char;
		}
	}
	else if (m_val == m_max && m_max_val_char.size())
	{
		if (m_max_val_char.size() > 1)
		{
			val_str = m_max_val_char;
		}
		else
		{
			val_str += m_max_val_char;
		}
	}
	else
	{
		val_str += m_val_char;
	}

	g_render->text(g_render->m_font_menu, m_name, position[0], position[1], 0, col);
	g_render->text(g_render->m_font_menu, val_str, (position[0] + m_size[0]) - g_csgo->m_surface->GetTextSize(g_render->m_font_menu, val_str.c_str())[0], position[1], 0, col);

	if (m_sliding)
	{
		auto pixels = (g_input->cursor_position().x - position[0]);

		auto clmp = std::clamp<float>(pixels, 0.f, m_size[0]);

		m_val = (clmp / m_size[0]) * m_max;

		if (!g_input->key_held(VK_LBUTTON))
		{
			m_sliding = false;
		}
	}
}