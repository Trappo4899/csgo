#include "includes.h"

CCheckbox::CCheckbox()
{
    m_name      = { };

    m_position  = { };
    m_size      = { };

    m_enabled   = { };
}

CCheckbox::CCheckbox(std::string name, bool enabled)
{
    m_name      = name;

    m_position  = { };
    m_size      = { 6.f, 6.f };

    m_enabled   = enabled;
}

bool CCheckbox::enabled() const
{
    return m_enabled;
}

void CCheckbox::think(Vector2 position, Vector2 group_size)
{
    Color col = Color(175, 175, 175);

    if (g_input->cursor_in_rect(position[0] - 5.f, position[1] - 5.f, (g_menu->m_size[0] / 2.f) - m_size[0], m_size[1] + 5.f))
    {
        col = Color(200, 200, 200);

        if (g_input->key_pressed(VK_LBUTTON))
        {
            m_enabled = !m_enabled;
        }
    }
    
    if (m_enabled)
    {
        col = g_menu->m_accent;
    }

    g_render->rect(position[0] - 1, position[1] - 1, m_size[0] + 2, m_size[1] + 2, g_menu->m_dark_outline);
    g_render->filled_rect(position[0], position[1], m_size[0], m_size[1], g_menu->m_light_outline);
    g_render->filled_rect(position[0], position[1], m_size[0], m_size[1], Color(col.r(), col.g(), col.b(), 50));
    g_render->text(g_render->m_font_menu, m_name, position[0] + m_size[1] + 9.f, position[1] - (m_size[1] / 2.f), 0, col);
}