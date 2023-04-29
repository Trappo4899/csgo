#include "includes.h"

CWindow::CWindow()
{
	m_name			= { };

	m_size			= { };
	m_min_size		= { };

	m_resizable		= { };
	m_movable		= { };
	m_show			= { };
}

CWindow::CWindow(std::string name, Vector2 pos, Vector2 size, Vector2 min_size, bool resizable, bool movable, bool show)
{
	m_name			= name;

	m_position		= pos;

	m_size			= size;
	m_min_size		= min_size;

	m_resizable		= resizable;
	m_movable		= movable;
	m_show			= show;
}

void CWindow::handle_resizing()
{
	if (!m_resizable || m_hovering || m_moving)
	{
		return;
	}

	static   Vector2		start_size		= { };
	static   Vector2		start_position	= { };
	static   char			side			= { };

	/* bottom right corner */
	if (g_input->cursor_in_rect(m_position[0] + (m_size[0] - 6.f), m_position[1] + (m_size[1] - 6.f), 6.f, 6.f))
	{
		if (g_input->key_pressed(VK_LBUTTON))
		{
			side |= (1 << 2);

			m_resizing = true;

			auto cursor_pos = g_input->cursor_position();

			start_size[0] = m_size[0] - cursor_pos.x;
			start_size[1] = m_size[1] - cursor_pos.y;
		}
	}

	/* right side */
	else if (g_input->cursor_in_rect(m_position[0] + (m_size[0] - 4.f), m_position[1] + 4.f, 4.f, m_size[1] - 8.f))
	{
		if (g_input->key_pressed(VK_LBUTTON))
		{
			side |= (1 << 4);

			m_resizing = true;

			auto cursor_pos = g_input->cursor_position();

			start_size[0] = m_size[0] - cursor_pos.x;
			start_size[1] = m_size[1] - cursor_pos.y;
		}
	}
	/* bottom side */
	else if (g_input->cursor_in_rect(m_position[0] + 4.f, m_position[1] + (m_size[1] - 4.f), m_size[0] - 8.f, 4.f))
	{
		if (g_input->key_pressed(VK_LBUTTON))
		{
			side |= (1 << 6);

			m_resizing = true;

			auto cursor_pos = g_input->cursor_position();

			start_size[0] = m_size[0] - cursor_pos.x;
			start_size[1] = m_size[1] - cursor_pos.y;
		}
	}

	if (m_resizing)
	{
		auto cursor_pos = g_input->cursor_position();

		auto calc_size = Vector2( cursor_pos.x + start_size[0],
								  cursor_pos.y + start_size[1] );

		if (calc_size[0] < m_min_size[0])
		{
			calc_size[0] = m_min_size[0];
		}

		if (calc_size[1] < m_min_size[1])
		{
			calc_size[1] = m_min_size[1];
		}
	
		if (side & (1 << 2))
		{
			m_size[0] = calc_size[0];
			m_size[1] = calc_size[1];
		}
		if (side & (1 << 4))
		{
			m_size[0] = calc_size[0];
		}
		else if (side & (1 << 6))
		{
			m_size[1] = calc_size[1];
		}

		if (!g_input->key_held(VK_LBUTTON))
		{
			m_resizing = false;

			start_size = { };
			side = { };
		}
	}
}

void CWindow::handle_moving()
{
	if (!m_movable || m_hovering || m_resizing)
	{
		return;
	}

	static Vector2 start_relative = { };

	if (g_input->cursor_in_rect(m_position[0] + 5.f, m_position[1] + 5.f, m_size[0] - 10.f, m_size[1] - 10.f))
	{
		if (g_input->key_pressed(VK_LBUTTON))
		{
			m_moving = true;

			auto cursor_pos = g_input->cursor_position();

			start_relative[0] = (cursor_pos.x - m_position[0]);
			start_relative[1] = (cursor_pos.y - m_position[1]);
		}
	}

	if (m_moving)
	{
		auto cursor_pos = g_input->cursor_position();

		m_position = Vector2( cursor_pos.x - start_relative[0],
							  cursor_pos.y - start_relative[1] );

		if (!g_input->key_held(VK_LBUTTON))
		{
			m_moving = false;
		}
	}
}

void CWindow::draw()
{
	/* draw base */
	g_render->filled_rect(m_position[0] - 1, m_position[1] - 1, m_size[0] + 2, m_size[1] + 2, m_dark_outline);
	g_render->filled_rect(m_position[0], m_position[1], m_size[0], m_size[1], m_dark_base);
	g_render->rect(m_position[0], m_position[1], m_size[0], m_size[1], m_light_outline);
}

void CWindow::think()
{
	this->draw();
}