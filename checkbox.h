#pragma once

class CCheckbox : public CElement
{
private:

	bool m_enabled;

public:

	CCheckbox();

	CCheckbox(std::string name, bool enabled);

public:

	bool enabled() const;

public:

	void think(Vector2 position, Vector2 group_size) override;
};