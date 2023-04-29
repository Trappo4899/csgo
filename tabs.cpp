#include "includes.h"

CTab::CTab()
{
	m_name		= { };

	m_size		= { };
	m_position	= { };
}

CTab::CTab(std::string name)
{
	m_name		= name;

	m_size		= { 0.f, 20.f };
	m_position	= { };
}

void CTab::add_group(CGroup* group)
{
	m_groups.push_back(group);
}

void CTab::think(Vector2 position, Vector2 size, Color text_col, bool selected)
{
	if (selected)
	{
		for (auto group : m_groups)
		{
			group->think({ g_menu->m_position[0], position[1] + size[1]});
		}
	}

	g_render->rect(position[0] + 4, position[1] + 4, size[0], size[1], g_menu->m_dark_outline);
	g_render->filled_rect(position[0] + 5, position[1] + 5, size[0] - 2, size[1] - 2, g_menu->m_light_outline);
	g_render->text(g_render->m_font_menu, m_name, (position[0] + 5) + (size[0] / 2), (position[1] + 5) + (size[1] / 2), FONT_CENTERED, text_col);
}

void CTabs::add_tab(CTab* tab)
{
	m_tabs.push_back(tab);
}

void CTabs::think(Vector2 position)
{
	for (int i = 0; i < m_tabs.size(); i++)
	{
		auto tab = m_tabs.at(i);

		if (tab == nullptr)
		{
			continue;
		}

		auto width		= (g_menu->m_size[0] - 11.f) / m_tabs.size();
		auto height		= tab->m_size[1];

		if (i == m_selected)
		{
			tab->think({ position[0] + (i * width) + 1.f, position[1] + 1.f }, { width + 1.5f, height }, g_menu->m_accent, true);
		}
		else if (g_input->cursor_in_rect(position[0] + (i * width) + 1.f, position[1] + 1.f, width + 1.5f, height))
		{
			tab->think({ position[0] + (i * width) + 1.f, position[1] + 1.f }, { width + 1.5f, height }, Color(225, 225, 225), false);

			if (g_input->key_pressed(VK_LBUTTON))
			{
				m_selected = i;
			}
		}
		else
		{
			tab->think({ position[0] + (i * width) + 1.f, position[1] + 1.f }, { width + 1.5f, height }, Color(175, 175, 175), false);
		}
	}
}