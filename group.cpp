#include "includes.h"

CGroup::CGroup()
{
	m_name			= { };

	m_position		= { };
	m_size			= { };

	m_resizable		= { };
	m_movable		= { };

	m_elements		= { };

	m_element_padding = { };
}

CGroup::CGroup(std::string name, Vector2 position, Vector2 size, bool resizable, bool movable)
{
	m_name			= name;

	m_position		= position;
	m_size			= size;

	m_resizable		= resizable;
	m_movable		= movable;

	m_elements		= { };

	m_element_padding = 10;
}

void CGroup::add_checkbox(CCheckbox* checkbox)
{
	if (checkbox == nullptr)
	{
		return;
	}

	m_elements.push_back({ checkbox, element_type_t::CHECKBOX });
}

void CGroup::add_slider_int(CSliderInt* slider)
{
	if (slider == nullptr)
	{
		return;
	}

	m_elements.push_back({ slider, element_type_t::SLIDERINT });
}

void CGroup::add_slider_flt(CSliderFlt* slider)
{
	if (slider == nullptr)
	{
		return;
	}

	m_elements.push_back({ slider, element_type_t::SLIDERFLT });
}

void CGroup::add_dropdown(CDropdown* dropdown)
{
	if (dropdown == nullptr)
	{
		return;
	}

	m_elements.push_back({ dropdown, element_type_t::DROPDOWN });
}

void CGroup::add_multidropdown(CMultidropdown* multidropdown)
{
	if (multidropdown == nullptr)
	{
		return;
	}

	m_elements.push_back({ multidropdown, element_type_t::MULTIDROPDOWN });
}

void CGroup::add_colourpicker(CColourPicker* colourpicker)
{
	if (colourpicker == nullptr)
	{
		return;
	}

	m_elements.push_back({ colourpicker, element_type_t::COLOURPICKER });
}

void CGroup::handle_elements(Vector2 position)
{
	m_padding = { };

	for (auto elem : m_elements)
	{
		//auto elem = m_elements.at(i - 1);

		/* if the element is going to be drawn outside of our menu then 
		we dont want to draw it */

		auto base_elem = reinterpret_cast<CElement*>(elem.first);

		if (
				((m_position[0] + position[0]) + m_padding[0] + base_elem->m_size[0]) > ((m_position[0] + position[0]) + m_size[0] + base_elem->m_size[1])

				||

				((m_position[1] + position[1]) + m_padding[1] + base_elem->m_size[0]) > ((m_position[1] + position[1]) + m_size[1] + base_elem->m_size[1])
		   )
		{
			continue;
		}

		switch (elem.second)
		{
		case element_type_t::CHECKBOX: {
			auto checkbox = reinterpret_cast<CCheckbox*>(elem.first);

			checkbox->think({ ((m_position[0] + position[0])) + 10.f, ((m_position[1] + position[1]) + m_padding[1]) + 10.f }, m_size);

			g_render->rect(((m_position[0] + position[0])) + 8.f, ((m_position[1] + position[1]) + m_padding[1]) + 8.f, checkbox->m_size[0] + 4.f, checkbox->m_size[1] + 4.f, Color(255, 255, 255, 100));

			m_padding[1] += checkbox->m_size[1] + m_element_padding;

		} break;

		case element_type_t::SLIDERINT: {
			auto slider_int = reinterpret_cast<CSliderInt*>(elem.first);

			slider_int->think({ ((m_position[0] + position[0])) + 25.f, ((m_position[1] + position[1]) + m_padding[1]) + 10.f }, m_size);

			g_render->rect(((m_position[0] + position[0])) + 23.f, ((m_position[1] + position[1]) + m_padding[1]) + 8.f, slider_int->m_size[0] + 4.f, slider_int->m_size[1] + 4.f, Color(255, 255, 255, 100));

			m_padding[1] += slider_int->m_size[1] + m_element_padding;
		} break;

		case element_type_t::SLIDERFLT: {
			auto slider_flt = reinterpret_cast<CSliderFlt*>(elem.first);

			slider_flt->think({ ((m_position[0] + position[0])) + 25.f, ((m_position[1] + position[1]) + m_padding[1]) + 10.f }, m_size);

			g_render->rect(((m_position[0] + position[0])) + 23.f, ((m_position[1] + position[1]) + m_padding[1]) + 8.f, slider_flt->m_size[0] + 4.f, slider_flt->m_size[1] + 4.f, Color(255, 255, 255, 100));

			m_padding[1] += slider_flt->m_size[1] + m_element_padding;
		} break;

		case element_type_t::DROPDOWN: {
			auto dropdown = reinterpret_cast<CDropdown*>(elem.first);

			dropdown->think({ ((m_position[0] + position[0])) + 25.f, ((m_position[1] + position[1]) + m_padding[1]) + 10.f }, m_size);

			m_padding[1] += dropdown->m_size[1] + m_element_padding;
		} break;

		case element_type_t::MULTIDROPDOWN: {
			auto multidropdown = reinterpret_cast<CMultidropdown*>(elem.first);

			multidropdown->think({ ((m_position[0] + position[0])) + 25.f, ((m_position[1] + position[1]) + m_padding[1]) + 10.f }, m_size);

			m_padding[1] += multidropdown->m_size[1] + m_element_padding;
		} break;

		case element_type_t::COLOURPICKER: {
			auto colourpicker = reinterpret_cast<CColourPicker*>(elem.first);

			colourpicker->think({ ((m_position[0] + position[0]) - m_padding[0]) + 25.f, ((m_position[1] + position[1]) + m_padding[1]) + 10.f }, m_size);

			m_padding[0] += colourpicker->m_size[0] + m_element_padding;
		} break;

		default: {

		} break;
		}
	}
}

void CGroup::draw(Vector2 position)
{
	auto col = Color(175, 175, 175);

	if (g_input->cursor_in_rect(position[0] + m_position[0], position[1] + m_position[1], m_size[0], m_size[1]))
	{
		m_hovered = true;

		col = Color(200, 200, 200);
	}

	if (m_moving || m_resizing)
	{
		col = g_menu->m_accent;
	}

	g_render->rect(			position[0] + m_position[0] - 1,	position[1] + m_position[1] - 1, m_size[0], m_size[1], g_menu->m_dark_outline);
	g_render->filled_rect(	position[0] + m_position[0],		position[1] + m_position[1], m_size[0] - 2, m_size[1] - 2, g_menu->m_dark_base);
	g_render->rect(			position[0] + m_position[0],		position[1] + m_position[1], m_size[0] - 2, m_size[1] - 2, g_menu->m_light_outline);
	g_render->text(			g_render->m_font_menu,		m_name, (position[0] + m_position[0]) + 11, (position[1] + m_position[1]) - 5.f, 0, col);
}

void CGroup::think(Vector2 position)
{
	this->draw(position);
	this->handle_elements(position);
}