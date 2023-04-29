#pragma once

enum {
	GENERIC = 0,	// must be first and is default group
	LOCALPLAYER,	// bytes for local player entity update
	OTHERPLAYERS,	// bytes for other players update
	ENTITIES,		// all other entity bytes
	SOUNDS,			// game sounds
	EVENTS,			// event messages
	TEMPENTS,		// temp entities
	USERMESSAGES,	// user messages
	ENTMESSAGES,	// entity messages
	VOICE,			// voice data
	STRINGTABLE,	// a stringtable update
	MOVE,			// client move cmds
	STRINGCMD,		// string command
	SIGNON,			// various signondata
	PAINTMAP,			// paintmap data
	ENCRYPTED,		// encrypted data
	TOTAL,			// must be last and is not a real group
};

enum ENetworkEventType_t
{
	k_ENetworkEventType_Generic = 0,		// Generic network event
	k_ENetworkEventType_TimedOut = 1,		// Network connection timed out
};

class INetChannelInfo
{
private:

	enum
	{

	};

public:

};