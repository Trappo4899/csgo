#pragma once

class CWindow
{
protected:

	std::string m_name;

	Vector2 m_position;

	Vector2 m_size;
	Vector2 m_min_size;

	bool m_resizable;
	bool m_movable;
	bool m_show;

	bool m_moving;
	bool m_resizing;
	bool m_hovering;

	Color m_dark_base;
	Color m_light_base;
	Color m_dark_outline;
	Color m_light_outline;

public:

	CWindow();

	CWindow(std::string name, Vector2 pos, Vector2 size, Vector2 min_size, bool resizable, bool movable, bool show = true);

public:

	void handle_resizing();
	void handle_moving();

public:

	virtual void draw();
	
	virtual void think();
};