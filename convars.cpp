#include "includes.h"

bool ConVar::IsFlagSet(int flag)
{
	return VMT::call<ISFLAGSET, bool, int>(this, flag);
}

const char* ConVar::GetName()
{
	return VMT::call<GETNAME, const char*>(this);
}

void ConVar::AddFlags(int flags)
{
	return VMT::call<ADDFLAGS, void, int>(this, flags);
}

void ConVar::RemoveFlags(int flags)
{
	return VMT::call<REMOVEFLAGS, void, int>(this, flags);
}

int ConVar::GetFlags()
{
	return VMT::call<GETFLAGS, int>(this);
}

bool ConVar::IsCommand()
{
	return VMT::call<ISCOMMAND, bool>(this);
}

float ConVar::GetFloat()
{
	return VMT::call<GETFLOAT, float>(this);
}

int ConVar::GetInt()
{
	return VMT::call<GETINT, int>(this);
}

void ConVar::SetValue(const char* pValue)
{
	VMT::call<SETVALUECSTRING, void, const char*>(this, pValue);
}

void ConVar::SetValue(float flValue)
{
	VMT::call<SETVALUEFLOAT, void, float>(this, flValue);
}

void ConVar::SetValue(int nValue)
{
	VMT::call<SETVALUEINT, void, int>(this, nValue);
}

void ConVar::SetValue(Color value)
{
	VMT::call<SETVALUECOLOR, void, Color>(this, value);
}

ConVar* CCVar::FindVar(const char* cvar)
{
	return VMT::call<GETCVAR, ConVar*, const char*>(this, cvar);
}

CVarManager::~CVarManager()
{
	this->unhide_all();
}

CVarManager::CVarManager()
{
	m_cvars = { };
}

CVarManager::CVarManager(CCVar* cvar)
{
		// read the pointer to the CCVar class
	auto cvar_addr = Address(cvar);

	if (!cvar_addr || !cvar_addr.at())
	{
		return;
	}
			   	 // read the first ConVar class
	for (auto curr_cvar = cvar_addr.at<ConVar*>(0x30); curr_cvar != nullptr; curr_cvar = curr_cvar->m_pNext)
	{
		m_cvars.push_back(curr_cvar);
	}
}

CVarManager::operator bool()
{
	return !m_cvars.empty();
}

ConVar* CVarManager::get(const char* name)
{
	for (auto curr : m_cvars)
	{
		if (HASH(curr->m_pszName) == HASH(name))
		{
			return curr;
		}
	}

	return nullptr;
}

void CVarManager::unhide_all()
{
	for (auto curr : m_cvars)
	{
		if (curr->IsFlagSet(FCVAR_HIDDEN) && curr->IsFlagSet(FCVAR_DEVELOPMENTONLY))
		{
			m_hidden.push_back({ curr, FCVAR_HIDDEN | FCVAR_DEVELOPMENTONLY });

			curr->RemoveFlags(FCVAR_HIDDEN);
			curr->RemoveFlags(FCVAR_DEVELOPMENTONLY);
		}
		else if (curr->IsFlagSet(FCVAR_HIDDEN))
		{
			m_hidden.push_back({ curr, FCVAR_HIDDEN });

			curr->RemoveFlags(FCVAR_HIDDEN);
		}
		else if (curr->IsFlagSet(FCVAR_DEVELOPMENTONLY))
		{
			m_hidden.push_back({ curr, FCVAR_DEVELOPMENTONLY });

			curr->RemoveFlags(FCVAR_DEVELOPMENTONLY);
		}
	}
}

void CVarManager::rehide_all()
{
	for (auto curr : m_hidden)
	{
		curr.first->AddFlags(curr.second);
	}
}