#include "includes.h"

Export::Export() : m_address{ }, m_name{ nullptr } { }
Export::Export(Address address, const char* name) : m_address{ address }, m_name{ name } { }

Export::operator bool()
{
	Address name((PVOID)m_name);

	return m_address && name;
}

Address Export::get_address()
{
	return m_address ? m_address : Address{ };
}

const char* Export::get_name()
{
	Address name((PVOID)m_name);

	return name ? m_name : "";
}

Exports::Exports() : m_exports{ } { }

Exports::Exports(PIMAGE_OPTIONAL_HEADER optional)
{
	do
	{
		if (optional == nullptr || !optional)
		{
			break;
		}

		auto export_dir = optional->DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT];

		if (!export_dir.Size || !export_dir.VirtualAddress)
		{
			break;
		}
		
		auto exports = Address(optional->ImageBase + export_dir.VirtualAddress);

		if (!exports.valid())
		{
			break;
		}

		auto address_of_functions = Address(optional->ImageBase + exports.as<PIMAGE_EXPORT_DIRECTORY>()->AddressOfFunctions);

		if (!address_of_functions.valid())
		{
			break;
		}

		auto address_of_names = Address(optional->ImageBase + exports.as<PIMAGE_EXPORT_DIRECTORY>()->AddressOfNames);

		if (!address_of_names.valid())
		{
			break;
		}

		for (int i = 0; i < exports.as<PIMAGE_EXPORT_DIRECTORY>()->NumberOfNames; ++i)
		{
			auto curr_function	= Address(optional->ImageBase + address_of_functions.as<DWORD*>()[i]);
			auto curr_fn_name	= Address(optional->ImageBase + address_of_names.as<DWORD*>()[i]);

			if (!curr_function.valid() || !curr_fn_name.valid())
			{
				continue;
			}

			m_exports.emplace_back(Export(curr_function, curr_fn_name.as<LPCSTR>()));
		}

		return;

	} while (false);

	m_exports = { };
}

Exports::operator bool()
{
	return !m_exports.empty();
}

Export Exports::get(const char* name)
{
	for (auto ex : m_exports)
	{
		if (HASH(ex.get_name()) == HASH(name))
		{
			return ex;
		}
	}

	return Export{ };
}

void Exports::Print()
{
	for (auto ex : m_exports)
	{
		if (ex && ex.get_name())
		{
			printf("[EXPORT] %s\n", ex.get_name());
		}
	}
}

Import::Import() : m_address{ }, m_name{ nullptr } { }

Import::Import(Address address, const char* name) : m_address{ address }, m_name{ name } { }

Import::operator bool()
{
	Address name((PVOID)m_name);

	return m_address && name;
}

Address Import::get_address()
{
	return m_address;
}

const char* Import::get_name()
{
	Address name((PVOID)m_name);

	return name ? m_name : "";
}

Imports::Imports() : m_imports{ } { }

Imports::Imports(PIMAGE_OPTIONAL_HEADER optional)
{
	do
	{
		if (optional == nullptr || !optional)
		{
			break;
		}

		auto import_dir = optional->DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT];

		if (!import_dir.Size || !import_dir.VirtualAddress)
		{
			break;
		}

		auto import_descriptor = reinterpret_cast<PIMAGE_IMPORT_DESCRIPTOR>(optional->ImageBase + import_dir.VirtualAddress);

		if (import_descriptor == nullptr || !import_descriptor)
		{
			break;
		}

		while (import_descriptor->Name)
		{
			auto module_name = reinterpret_cast<LPCSTR>(optional->ImageBase + import_descriptor->Name);

			if (Modules::get_module(util::string_to_wstring(module_name).c_str()))
			{
				// import lookup table
				auto original_thunk = reinterpret_cast<PIMAGE_THUNK_DATA>(optional->ImageBase + import_descriptor->OriginalFirstThunk);

				// import address table
				auto first_thunk = reinterpret_cast<PIMAGE_THUNK_DATA>(optional->ImageBase + import_descriptor->FirstThunk);

				while (original_thunk->u1.AddressOfData)
				{
					auto function_name = reinterpret_cast<PIMAGE_IMPORT_BY_NAME>(optional->ImageBase + original_thunk->u1.AddressOfData);

					if (function_name != nullptr)
					{
						m_imports.emplace_back(Import(Address(first_thunk->u1.Function), function_name->Name));
					}

					++original_thunk;
					++first_thunk;
				}
			}

			++import_descriptor;
		}

		return;

	} while (false);

	m_imports = { };
}

Imports::operator bool()
{
	return !m_imports.empty();
}

Import Imports::get(const char* name)
{
	for (auto im : m_imports)
	{
		if (HASH(im.get_name()) == HASH(name))
		{
			return im;
		}
	}

	return Import{ };
}

void Imports::Print()
{
	for (auto im : m_imports)
	{
		if (im && im.get_name())
		{
			printf("[IMPORT] %s\n", im.get_name());
		}
	}
}

PE::PE()
	: m_dos{ nullptr }, m_nt{ nullptr }, m_file{ nullptr }, m_optional{ nullptr } { }

PE::PE(Address addr)
{
	do
	{
		m_dos = addr.as<PIMAGE_DOS_HEADER>();

		if (m_dos == nullptr || !m_dos)
		{
			break;
		}

		m_nt = reinterpret_cast<PIMAGE_NT_HEADERS>(addr.as <uintptr_t>() + m_dos->e_lfanew);

		if (m_nt == nullptr || !m_nt)
		{
			break;
		}

		m_file = &m_nt->FileHeader;
		m_optional = &m_nt->OptionalHeader;

		if (m_file == nullptr || !m_file || m_optional == nullptr || !m_optional)
		{
			break;
		}

		m_exports = Exports(m_optional);

		if (!m_exports)
		{
			break;
		}

		m_imports = Imports(m_optional);

		if (!m_imports)
		{
			break;
		}

		return;

	} while (false);

	m_dos = { nullptr };
	m_nt = { nullptr };
	m_file = { nullptr };
	m_optional = { nullptr };
}

PE::operator bool()
{
	return m_dos != nullptr && m_nt != nullptr && m_file != nullptr && m_optional != nullptr;
}

PIMAGE_DOS_HEADER PE::get_dos()
{
	return m_dos;
}

PIMAGE_NT_HEADERS PE::get_nt()
{
	return m_nt;
}

PIMAGE_FILE_HEADER PE::get_file()
{
	return m_file;
}

PIMAGE_OPTIONAL_HEADER PE::get_optional()
{
	return m_optional;
}

Exports PE::get_exports()
{
	return m_exports;
}

Imports PE::get_imports()
{
	return m_imports;
}