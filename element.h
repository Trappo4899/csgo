#pragma once

class CElement
{
	friend class CGroup;

protected:

	std::string		m_name;

	Vector2			m_position;
	Vector2			m_size;

public:

	virtual void think(Vector2 position, Vector2 group_size) = 0;
};