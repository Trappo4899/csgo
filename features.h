#pragma once

/* we will include all feature header files here */
#include "aimbot.h"
#include "visuals.h"
#include "misc.h"

/* class for containing all classes */
class CFeatures
{
public:

	/* no m_ because creating member functions for 
	accessing these is just unecessary */
	CAimbot		aimbot;
	CVisuals	visuals;
	CMisc		misc;
};

extern std::unique_ptr<CFeatures> g_features;