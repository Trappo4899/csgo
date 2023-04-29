#pragma once

enum modtype_t
{
	mod_bad = 0,
	mod_brush,
	mod_sprite,
	mod_studio
};

struct RenderableInstance_t
{
	uint8_t m_nAlpha;
};

struct model_t
{
	void*				fnHandle;
	char				szPathName[260];
	int					nLoadFlags;	
	int					nServerCount;
	modtype_t			type;
	int					flags;		
	Vector3				mins;
	Vector3				maxs;
	float				radius;
};