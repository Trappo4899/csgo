#pragma once

#include "element.h"

class CMultidropdown : public CElement
{
private:

	std::vector<std::string> m_options;
	std::vector<bool> m_selected;

public:

	CMultidropdown();

	CMultidropdown(std::string name, Vector2 size, std::vector<std::string> options, std::vector<bool> selected);

public:

	void think(Vector2 position, Vector2 group_size) override;
};