#pragma once

#include "tabs.h"
#include "group.h"
#include "element.h"
#include "checkbox.h"
#include "slider.h"
#include "dropdown.h"
#include "multidropdown.h"
#include "colourpicker.h"

class CMenu : public CWindow
{
	friend class CElement;
	friend class CTabs;
	friend class CTab;
	friend class CGroup;
	friend class CCheckbox;
	friend class CSliderInt;
	friend class CSliderFlt;
	friend class CMultidropdown;
	friend class CDropdown;
	friend class CColourPicker;

private:

	CTabs m_tabs;
	
	Color m_accent;

public:

	CTab m_aimbot_tab;
		CGroup m_aimbot_main_group;
			CCheckbox m_aimbot_on;
			CSliderFlt m_test_slider;

	CTab m_visuals_tab;
		CGroup m_visuals_players_group;
			CCheckbox m_visuals_players_box;
			CCheckbox m_visuals_players_name;
			CCheckbox m_visuals_players_healthbar;

	CTab m_misc_tab;

public:

	CMenu();

public:

	void draw() override;

	void think() override;
};

extern std::unique_ptr<CMenu> g_menu;