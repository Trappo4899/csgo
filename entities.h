#pragma once
#undef GetClassName

#include "model.h"

//__const:0088BC38; public C_BaseEntity :
//__const:0088BC38;        public /* offset 0x0 */ IClientEntity:
//__const:0088BC38;            public /* offset 0x0 */ IClientUnknown:
//__const:0088BC38;                public /* offset 0x0 */ IHandleEntity,
//__const:0088BC38;                public /* offset 0x4 */ IClientRenderable,
//__const:0088BC38;                public /* offset 0x8 */ IClientNetworkable,
//__const:0088BC38;                public /* offset 0xC */ IClientThinkable

class CTeam;
class CBaseCombatCharacter;
class CBaseCombatWeapon;

class CBaseEntity
{
private:

	enum Entity
	{
		// IClientUnknown methods
		GETCOLLIDEABLE = 3,
		GETCLIENTNETWORKABLE = 4,
		GETCLIENTRENDERABLE = 5,
		GETCLIENTENTITY = 6,
		GETCBASEENTITY = 7,
		GETCLIENTTHINKABLE = 8,
		GETCLIENTALPHAPROPERTY = 9,

		// IClientEntity methods
		GETABSORIGIN = 10,
		GETABSANGLES = 11,

		// CBaseEntity methods
		GETTEAM = 87,
		GETTEAMNUMBER = 88,
		GETPENDINGTEAMNUMBER = 89,
		CHANGETEAM = 90,
		GETRENDERTEAMNUMBER = 91,
		ISINSAMETEAM = 92,
		INLOCALTEAM = 93,
		GETHEALTH = 122,
		GETMAXHEALTH = 123,
		GETCLASSNAME = 141,
		GETPLAYERNAME = 142,

		ISALIVE = 156,
		ISPLAYER = 158,
		ISCOMBATCHARACTER = 160,
		GETCOMBATCHARACTER = 161,
		ISNPC = 162,
		ISWEAPON = 166,
		GETWEAPON = 167,
		GETEYEANGLES = 170,
		GETLOCALEYEANGLES = 171,
	};

	enum Renderable
	{
		GETMODEL = 8,
		DRAWMODEL = 9,
		SETUPBONES = 13,
		SETUPWEIGHTS = 14,
		DOANIMATIONEVENTS = 15,
		GETRENDERBOUNDS = 17,
		GETRENDERBOUNDSWORLDSPACE = 18,
		GETRENDERABLETOWORLDTRANSFORM = 32,
	};

	enum Networkable
	{
		GETCLIENTCLASS = 2,
		ISDORMANT = 9,
		ENTINDEX = 10,
	};

	enum Thinkable
	{
		// only useless functions
	};

public: /* CBaseEntity, IClientEntity, IClientUnknown, IHandleEntity */

	Vector3 GetAbsOrigin()
	{
		return VMT::call<GETABSORIGIN, const Vector3&>(this);
	}

	const Vector3& GetAbsAngles()
	{
		return VMT::call<GETABSANGLES, const Vector3&>(this);
	}

	CTeam* GetTeam()
	{
		return VMT::call<GETTEAM, CTeam*>(this);
	}

	int GetTeamNumber()
	{
		return VMT::call<GETTEAMNUMBER, int>(this);
	}

	int GetPendingTeamNumber()
	{
		return VMT::call<GETPENDINGTEAMNUMBER, int>(this);
	}

	void ChangeTeam( int iTeamNum )
	{
		VMT::call<CHANGETEAM, void, int>(this, iTeamNum);
	}

	int GetRenderTeamNumber()
	{
		return VMT::call<GETRENDERTEAMNUMBER, int>(this);
	}

	bool InSameTeam( CBaseEntity* pEntity )
	{
		return VMT::call<ISINSAMETEAM, bool, CBaseEntity*>(this, pEntity);
	}

	bool InLocalTeam()
	{
		return VMT::call<INLOCALTEAM, bool>(this);
	}

	int GetHealth()
	{
		return VMT::call<GETHEALTH, int>(this);
	}

	int GetMaxHealth()
	{
		return VMT::call<GETMAXHEALTH, int>(this);
	}

	const char* GetClassName()
	{
		return VMT::call<GETCLASSNAME, const char*>(this);
	}

	/* haram */
	const char* GetPlayerName()
	{
		return VMT::call<GETPLAYERNAME, const char*>(this);
	}

	bool IsAlive()
	{
		return VMT::call<ISALIVE, bool>(this);
	}

	bool IsPlayer()
	{
		return VMT::call<ISPLAYER, bool>(this);
	}

	bool IsCombatCharacter()
	{
		return VMT::call<ISCOMBATCHARACTER, bool>(this);
	}

	CBaseCombatCharacter* GetBaseCombatCharacter()
	{
		return VMT::call<GETCOMBATCHARACTER, CBaseCombatCharacter*>(this);
	}

	bool IsNpc()
	{
		return VMT::call<ISNPC, bool>(this);
	}

	bool IsWeapon()
	{
		return VMT::call<ISWEAPON, bool>(this);
	}

	CBaseCombatWeapon* GetBaseCombatWeapon()
	{
		return VMT::call<GETWEAPON, CBaseCombatWeapon*>(this);
	}

	const Vector3& GetEyeAngles()
	{
		return VMT::call<GETEYEANGLES, const Vector3&>(this);
	}

	const Vector3& GetLocalEyeAngles()
	{
		return VMT::call<GETLOCALEYEANGLES, const Vector3&>(this);
	}

public: /* IClientRenderable	| +0x4 */

	model_t* GetModel()
	{
		return VMT::call<GETMODEL, model_t*>(this + 0x4);
	}

	int DrawModel(int flags, const RenderableInstance_t& instance)
	{
		return VMT::call<DRAWMODEL, int, int, const RenderableInstance_t&>(this + 0x4, flags, instance);
	}

	bool SetupBones(matrix3x4_t* pBoneToWorldOut, int nMaxBones, int boneMask, float currentTime)
	{
		return VMT::call<SETUPBONES, bool, matrix3x4_t*, int, int, float>(this + 0x4, pBoneToWorldOut, nMaxBones, boneMask, currentTime);
	}

	void SetupWeights(const matrix3x4_t* pBoneToWorld, int nFlexWeightCount, float* pFlexWeights, float* pFlexDelayedWeights)
	{
		VMT::call<SETUPWEIGHTS, void, const matrix3x4_t*, int, float*, float*>(this + 0x4, pBoneToWorld, nFlexWeightCount, pFlexWeights, pFlexDelayedWeights);
	}

	void DoAnimationEvents()
	{
		VMT::call<DOANIMATIONEVENTS, void>(this + 0x4);
	}

	void GetRenderBounds(Vector3& mins, Vector3& maxs)
	{
		VMT::call<GETRENDERBOUNDS, void, Vector3&, Vector3&>(this + 0x4, std::ref(mins), std::ref(maxs));
	}

	void GetRenderBoundsWorldspace(Vector3& absMins, Vector3& absMaxs)
	{
		VMT::call<GETRENDERBOUNDSWORLDSPACE, void, Vector3&, Vector3&>(this + 0x4, std::ref(absMins), std::ref(absMaxs));
	}

	const matrix3x4_t& GetRenderableToWorldTransform()
	{
		return VMT::call <GETRENDERABLETOWORLDTRANSFORM, const matrix3x4_t&>(this + 0x4);
	}

public: /* IClientNetworkable	| +0x8 */

	ClientClass* GetClientClass()
	{
		return VMT::call<GETCLIENTCLASS, ClientClass*>(this + 0x8);
	}

	bool IsDormant()
	{
		return VMT::call<ISDORMANT, bool>(this + 0x8);
	}

	int EntIndex()
	{
		return VMT::call<ENTINDEX, int>(this + 0x8);
	}
};

class CTeam : public CBaseEntity
{
private:

	enum
	{

	};

public:


};

class CBaseCombatCharacter
{
private:

	enum
	{

	};

public:


};

class CBaseCombatWeapon
{
private:

	enum
	{

	};

public:


};

class CBasePlayer : public CBaseEntity
{
private:

	enum
	{

	};

public:


};