#pragma once

class CDropdown : public CElement
{
private:

	std::vector<std::string> m_options;
	int m_selected;

public:

	CDropdown();

	CDropdown(std::string name, Vector2 size, std::vector<std::string> options, int selected);

public:

	void think(Vector2 position, Vector2 group_size) override;
};