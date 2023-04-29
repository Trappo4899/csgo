#include "includes.h"

Module::Module() : m_address{ }, m_pe{ }, m_name{ nullptr } { }

Module::Module(Address addr, const wchar_t* name) : m_address{ addr }, m_pe{ PE(addr) }, m_name{ name } { }

Address Module::get_address()
{
	return m_address ? m_address : Address{ };
}

PE Module::get_pe()
{
	return m_pe ? m_pe : PE{ };
}

const wchar_t* Module::get_name()
{
	return m_name ? m_name : L"";
}

Address Module::scan(const char* pattern, const char* mask)
{
	MEMORY_BASIC_INFORMATION	mbi			= { };
	PBYTE						address		= { m_address.as<PBYTE>() };
	SIZE_T						size		= { m_pe.get_optional()->SizeOfImage };

		// current region = module address ; while we are still in our module ; go to next memory region
	for (auto current_region = address; current_region < address + size; current_region += mbi.RegionSize)
	{
			// skip bad memory
		if (!VirtualQuery(current_region, &mbi, sizeof(mbi)) || mbi.State != MEM_COMMIT || mbi.Protect == PAGE_NOACCESS) continue;

			// scan the current region for our pattern
		for (int i = 0; i < mbi.RegionSize; ++i)
		{
			bool pattern_found = true;

			for (int j = 0; j < strlen(mask); ++j)
			{
					// if currently not a wildcard and pattern doesent match with address then go to next byte
				if (mask[j] != '?' && pattern[j] != m_address.at<char>(i + j))
				{
					pattern_found = false;
					break;
				}
			}

			if (pattern_found)
			{
				return m_address.as(i);
			}
		}
	}

	return Address{ };
}

Address Module::scan(const char* ida_pattern)
{
	bool once = false;

	std::string pattern = "\\x";
	std::string mask = "";

	for (int i = 0; i < strlen(ida_pattern); i++)
	{
		if (ida_pattern[i] == ' ')
		{
			pattern += "\\x";
		}
		else if (ida_pattern[i] == '?')
		{
			pattern += "00";
			mask += '?';
		}
		else
		{
			pattern += ida_pattern[i];

			if (!once)
			{
				mask += 'x';
			}

			once = !once;
		}
	}

	return this->scan(pattern.c_str(), mask.c_str());
}

Modules::Modules()
{
	do
	{
#ifdef _WIN64
		auto peb = reinterpret_cast<_PEB*>(__readgsqword(0x60));
#else
		auto peb = reinterpret_cast<_PEB*>(__readfsdword(0x30));
#endif

		if (peb == nullptr || !peb)
		{
			break;
		}

		auto ldr = peb->Ldr;

		if (ldr == nullptr || !ldr)
		{
			break;
		}

		for (auto curr = ldr->InLoadOrderModuleList.Flink; curr != &ldr->InLoadOrderModuleList; curr = curr->Flink)
		{
			auto entry = CONTAINING_RECORD(curr->Flink, LDR_DATA_TABLE_ENTRY, InLoadOrderLinks);

			if (entry != nullptr && entry->BaseDllName.Buffer)
			{
				m_modules.push_back(Module(Address(entry->DllBase), entry->BaseDllName.Buffer));
			}
		}

		return;

	} while (false);

	m_modules = { };
}

Address Modules::get_module(const wchar_t* name)
{
	do
	{
#ifdef _WIN64
		auto peb = reinterpret_cast<_PEB*>(__readgsqword(0x60));
#else
		auto peb = reinterpret_cast<_PEB*>(__readfsdword(0x30));
#endif

		if (peb == nullptr || !peb)
		{
			break;
		}

		auto ldr = peb->Ldr;

		if (ldr == nullptr || !ldr)
		{
			break;
		}

		for (auto curr = ldr->InLoadOrderModuleList.Flink; curr != &ldr->InLoadOrderModuleList; curr = curr->Flink)
		{
			auto entry = CONTAINING_RECORD(curr->Flink, LDR_DATA_TABLE_ENTRY, InLoadOrderLinks);

			if (entry != nullptr && entry->BaseDllName.Buffer)
			{
				if (HASH(entry->BaseDllName.Buffer) ==  HASH(name))
				{
					return entry->DllBase;
				}
			}
		}

	} while (false);

	return Address{ };
}

void Modules::Print()
{
	for (auto m : m_modules)
	{
		printf("[%ws] -> 0x%X\n", m.get_name(), m.get_address().as<uintptr_t>());
		//m.get_pe().get_imports().Print();
		//m.get_pe().get_exports().Print();
		//printf("\n\n");
	}
}

Modules::operator bool()
{
	return !m_modules.empty();
}

Module Modules::get(const wchar_t* name)
{
	for (auto m : m_modules)
	{
		if (HASH(m.get_name()) == HASH(name))
		{
			return m;
		}
	}

	return Module{ };
}

std::vector<Module> Modules::get_modules()
{
	return m_modules;
}