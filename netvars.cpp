#include "includes.h"

class RecvTable;
class RecvProp;

Netvar::Netvar()
{
	m_table = nullptr;
	m_prop = nullptr;
}

Netvar::Netvar(RecvTable* table, RecvProp* prop)
{
	m_table = table;
	m_prop = prop;
}

Netvar::operator bool()
{
	return m_table != nullptr && m_prop != nullptr;
}

const char* Netvar::get_table_name()
{
	if (m_table != nullptr)
	{
		return m_table->m_pNetTableName;
	}

	return "";
}

const char* Netvar::get_prop_name()
{
	if (m_prop != nullptr)
	{
		return m_prop->m_pVarName;
	}

	return "";
}

int Netvar::get_offset()
{
	if (m_prop != nullptr)
	{
		return m_prop->m_Offset;
	}

	return -1;
}

NetvarManager::NetvarManager()
{
	m_vars = { };
}

NetvarManager::NetvarManager(ClientClass* cl)
{
	for (auto curr_table = cl; curr_table != nullptr; curr_table = curr_table->m_pNext)
	{
		auto recv_table = curr_table->m_pRecvTable;

		if (recv_table == nullptr || !recv_table)
		{
			continue;
		}

		dump(recv_table);
	}
}

NetvarManager::operator bool()
{
	return !m_vars.empty();
}

void NetvarManager::dump(RecvTable* table)
{
	auto prop_arr = table->m_pProps;

	for (int i = 0; i < table->m_nProps; ++i)
	{
			// some black ones that are numbers were not wanting also baseclass big gay no care
		if (prop_arr[i].m_pVarName[0] == '0' || // - these will be just as fast as integer comparison as its just 1 character
			prop_arr[i].m_pVarName[0] == '1' ||
			prop_arr[i].m_pVarName[0] == '2' ||
			prop_arr[i].m_pVarName[0] == '3' ||
			prop_arr[i].m_pVarName[0] == '4' ||
			prop_arr[i].m_pVarName[0] == '5' ||
			prop_arr[i].m_pVarName[0] == '6' ||
			prop_arr[i].m_pVarName[0] == '7' ||
			prop_arr[i].m_pVarName[0] == '8' ||
			prop_arr[i].m_pVarName[0] == '9' ||
			HASH(prop_arr[i].m_pVarName) == HASH("baseclass")) continue;

			// if its a data table then we want to use recursion to loop the new table ( idea from guided hacking thread )
		if (prop_arr[i].m_RecvType == DPT_DataTable && prop_arr[i].m_pDataTable != nullptr)
		{
			dump(prop_arr[i].m_pDataTable);
		}

		Netvar var = Netvar(table, &prop_arr[i]);

		m_vars.push_back(&var);
	}
}

Netvar* NetvarManager::get(const char* table_name, const char* prop_name)
{
	for (auto var : m_vars)
	{
		if (!var)
		{
			continue;
		}

		if ( _stricmp(var->get_table_name(), table_name)  == 0 && 
			 _stricmp(var->get_prop_name(), prop_name)    == 0    )
		{
			return var;
		}
	}

	return nullptr;
}