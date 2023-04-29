#pragma once

#include "checkbox.h"
#include "slider.h"
#include "dropdown.h"
#include "multidropdown.h"
#include "colourpicker.h"

class CGroup
{
public:

	enum class element_type_t
	{
		CHECKBOX,
		SLIDERINT,
		SLIDERFLT,
		DROPDOWN,
		MULTIDROPDOWN,
		COLOURPICKER,
	};

private:

	std::vector<std::pair<PVOID, element_type_t>> m_elements;

	std::string	m_name;

	Vector2	m_position;
	Vector2	m_size;

	Vector2 m_padding;

	bool m_resizable;
	bool m_movable;

	bool m_hovered;

	bool m_moving;
	bool m_resizing;

	int m_element_padding;

public:

	CGroup();

	CGroup(std::string name, Vector2 position, Vector2 size, bool resizable, bool movable);

public:

	void add_checkbox(CCheckbox* checkbox);
	void add_slider_int(CSliderInt* slider);
	void add_slider_flt(CSliderFlt* slider);
	void add_dropdown(CDropdown* dropdown);
	void add_multidropdown(CMultidropdown* multidropdown);
	void add_colourpicker(CColourPicker* colourpicker);

	void handle_elements(Vector2 position);
	void draw(Vector2 position);

public:

	void think(Vector2 position);
};