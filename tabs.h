#pragma once

#include "element.h"

class CTab
{
	friend class CTabs;

private:

	std::vector<CGroup*> m_groups;

	std::string		m_name;

	Vector2			m_position;
	Vector2			m_size;

public:

	CTab();

	CTab(std::string name);

public:

	void add_group(CGroup* group);

public:

	void think(Vector2 position, Vector2 size, Color text_col, bool selected = false);
};

class CTabs
{
	friend class CTab;

private:

	std::vector<CTab*> m_tabs;
	unsigned int m_selected;

public:

	void add_tab(CTab* tab);

public:

	void think(Vector2 position);
};