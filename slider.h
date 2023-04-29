#pragma once

/* tried using template class for
the difference in types compiler didnt
like it re using code it is */

class CSliderInt : public CElement
{
private:

	int m_max;
	int m_min;
	int m_val;

	std::string m_min_val_char;
	std::string m_max_val_char;
	std::string m_val_char;

	bool m_sliding;
	bool m_hovered;

public:

	CSliderInt();

	CSliderInt(std::string name, int max, int min, int val, std::string val_char = "", std::string min_val_char = "", std::string max_val_char = "");

	void think(Vector2 position, Vector2 group_size) override;
};

class CSliderFlt : public CElement
{
private:

	float m_max;
	float m_min;
	float m_val;

	std::string m_min_val_char;
	std::string m_max_val_char;
	std::string m_val_char;

	bool m_sliding;
	bool m_hovered;

public:

	CSliderFlt();

	CSliderFlt(std::string name, float max, float min, float val, std::string val_char = "", std::string min_val_char = "", std::string max_val_char = "");

public:

	void think(Vector2 position, Vector2 group_size) override;
};