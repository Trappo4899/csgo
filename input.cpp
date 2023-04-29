#include "includes.h"

void CInput::update()
{
	GetCursorPos(&m_cursor);

	for (int i = 0; i < 255; i++)
	{
		auto key = &m_keys[i];

		if (key == nullptr)
		{
			continue;
		}

		key->pressed = false;

		if (key->down && key->tick > key->oldtick)
		{
			key->oldtick = key->tick;

			key->pressed = true;
		}
	}
}

void CInput::handle_wndproc(UINT message, WPARAM wp)
{
	switch (message)
	{
	case WM_LBUTTONDOWN:
		m_keys.at(VK_LBUTTON).down = true;
		m_keys.at(VK_LBUTTON).tick = GetTickCount();
		break;

	case WM_LBUTTONUP:
		m_keys.at(VK_LBUTTON).down = false;
		break;

	case WM_RBUTTONDOWN:
		m_keys.at(VK_RBUTTON).down = true;
		m_keys.at(VK_RBUTTON).tick = GetTickCount();
		break;

	case WM_RBUTTONUP:
		m_keys.at(VK_RBUTTON).down = false;
		break;

	case WM_MBUTTONDOWN:
		m_keys.at(VK_MBUTTON).down = true;
		m_keys.at(VK_MBUTTON).tick = GetTickCount();
		break;

	case WM_MBUTTONUP:
		m_keys.at(VK_MBUTTON).down = false;
		break;

	case WM_XBUTTONDOWN:
		if (GET_XBUTTON_WPARAM(wp) == XBUTTON1)
		{
			m_keys.at(VK_XBUTTON1).down = true;
			m_keys.at(VK_XBUTTON1).tick = GetTickCount();
		}
		else if (GET_XBUTTON_WPARAM(wp) == XBUTTON2)
		{
			m_keys.at(VK_XBUTTON2).down = true;
			m_keys.at(VK_XBUTTON2).tick = GetTickCount();
		}

		break;

	case WM_XBUTTONUP:
		if (GET_XBUTTON_WPARAM(wp) == XBUTTON1)
		{
			m_keys.at(VK_XBUTTON1).down = false;
		}
		else if (GET_XBUTTON_WPARAM(wp) == XBUTTON2)
		{
			m_keys.at(VK_XBUTTON2).down = false;
		}

		break;

	case WM_KEYDOWN:
		if ((size_t)wp < m_keys.size())
		{
			m_keys.at(wp).down = true;
			m_keys.at(wp).tick = GetTickCount();
		}

		break;

	case WM_KEYUP:
		if ((size_t)wp < m_keys.size())
		{
			m_keys.at(wp).down = false;
		}

		break;

	case WM_SYSKEYDOWN:
		if (wp == VK_MENU)
		{
			m_keys.at(VK_MENU).down = true;
			m_keys.at(VK_MENU).tick = GetTickCount();
		}

		break;

	case WM_SYSKEYUP:
		if (wp == VK_MENU)
		{
			m_keys.at(VK_MENU).down = false;
		}

		break;

	case WM_CHAR:

		switch (wp)
		{
		case VK_BACK:
			if (!m_buffer.empty())
			{
				m_buffer.pop_back();
			}
			break;

		case VK_ESCAPE:
		case VK_TAB:
		case VK_RETURN:
			break;

		default:
			if (std::isdigit(static_cast<char>(wp)))
			{
				m_buffer += static_cast<char>(wp);
			}

			break;
		}

		break;

	default:
		break;
	}
}

bool CInput::key_pressed(unsigned int key)
{
	if (key < 0 || key > m_keys.size())
	{
		return false;
	}

	return m_keys.at(key).pressed;
}

bool CInput::key_held(unsigned int key)
{
	if (key < 0 || key > m_keys.size())
	{
		return false;
	}

	return m_keys.at(key).down;
}

POINT CInput::cursor_position()
{
    return m_cursor;
}

bool CInput::cursor_in_rect(float x, float y, float w, float h, bool show_bounds)
{
	if (show_bounds)
	{
		g_render->rect(x, y, w, h, Color(255, 255, 255, 100), 10 /* precedence level 10 so it will almost certainly draw over everything */);
	}

    return (
        (m_cursor.x >= x && m_cursor.x <= x + w) &&
        (m_cursor.y >= y && m_cursor.y <= y + h));
}