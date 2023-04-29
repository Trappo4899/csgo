#include "includes.h"

CMenu::CMenu()
{
	m_name							= "Scouseware";

	m_position						= Vector2(250, 350);

	m_size							= Vector2(500, 400);
	m_min_size						= Vector2(300, 300);

	m_accent						= Color(164, 146, 243, 255);

	m_resizable						= true;
	m_movable						= true;

	m_dark_base						= Color(25, 25, 25, 255);
	m_light_base					= Color(35, 35, 35, 255);
	m_dark_outline					= Color( 0,  0,  0, 255);
	m_light_outline					= Color(45, 45, 45, 255);

	m_aimbot_tab					= CTab("Aimbot");
	m_aimbot_main_group				= CGroup("Main", Vector2(10, 10), Vector2(200, 250), true, true);
	m_aimbot_on						= CCheckbox("Aimbot On", false);
	m_test_slider					= CSliderFlt("Test", 50.f, 0.f, 5.f, "%", "#", "*");

	m_aimbot_main_group.add_slider_flt(&m_test_slider);
	m_aimbot_tab.add_group(&m_aimbot_main_group);
	m_tabs.add_tab(&m_aimbot_tab);

	m_visuals_tab					= CTab("Visuals");
	m_visuals_players_group			= CGroup("Players", Vector2(10, 10), Vector2(200, 250), true, true);
	m_visuals_players_box			= CCheckbox("Box", false);
	m_visuals_players_name			= CCheckbox("Name", false);
	m_visuals_players_healthbar		= CCheckbox("Healthbar", false);

	m_visuals_players_group.add_checkbox(&m_visuals_players_box);
	m_visuals_players_group.add_checkbox(&m_visuals_players_name);
	m_visuals_players_group.add_checkbox(&m_visuals_players_healthbar);
	m_visuals_tab.add_group(&m_visuals_players_group);
	m_tabs.add_tab(&m_visuals_tab);

	m_misc_tab						= CTab("Misc");

	m_tabs.add_tab(&m_misc_tab);
}

void CMenu::draw()
{
	/* draw menu base */
	g_render->filled_rect(	m_position[0] - 1,	m_position[1] - 1,	m_size[0] + 2,	m_size[1] + 2,	m_dark_outline);
	g_render->filled_rect(	m_position[0],		m_position[1],		m_size[0],		m_size[1],		m_dark_base);
	g_render->rect(			m_position[0],		m_position[1],		m_size[0],		m_size[1],		m_light_outline);

	/* draw base for groups */
	g_render->rect(			m_position[0] + 4,		m_position[1] + 4,		m_size[0] - 8,	m_size[1] - 8, m_dark_outline);
	g_render->filled_rect(	m_position[0] + 4.5,	m_position[1] + 4.5,	m_size[0] - 8.5, m_size[1] - 8.5, m_light_base);
	g_render->rect(			m_position[0] + 5,		m_position[1] + 5,		m_size[0] - 10, m_size[1] - 10, m_dark_outline);

	//g_render->text(g_render->m_font_csgo_small, "scouseware", m_position[0] + 4, m_position[1] + 8, 0, m_accent);
}

void CMenu::think()
{
	if (g_input->key_pressed(VK_INSERT))
	{
		m_show = !m_show;
	}

	if (!m_show)
	{
		return;
	}

	/* draw main menu */
	this->draw();

	/* draw all tabs and things inside them */
	m_tabs.think(this->m_position);

	/* handle moving and resizing of the menu */
	this->handle_moving();
	this->handle_resizing();
}