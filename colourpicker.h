#pragma once

class CColourPicker : public CElement
{
private:

	Color m_original;
	Color m_color;

public:

	CColourPicker();

	CColourPicker(std::string name, Vector2 size, Color original);

public:

	void think(Vector2 position, Vector2 group_size) override;
};