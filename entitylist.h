#pragma once

class CBaseEntity;

class IClientEntityList
{
private:

	enum
	{
		GETCLIENTENTITY = 3,
		NUMBEROFENTITIES = 5,
	};

public:

	CBaseEntity* GetClientEntity( int entnum )
	{
		return VMT::call<GETCLIENTENTITY, CBaseEntity*, int>(this, entnum);
	}

	int NumberOfEntities( bool bIncludeNoneNetworkable )
	{
		return VMT::call<NUMBEROFENTITIES, int, bool>(this, bIncludeNoneNetworkable);
	}
};