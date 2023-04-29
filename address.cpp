#include "includes.h"

bool Address::get_mbi(MEMORY_BASIC_INFORMATION* mbi_out)
{
	return VirtualQuery((LPCVOID)m_address, mbi_out, sizeof(MEMORY_BASIC_INFORMATION));
}

Address::Address() : m_address{ 0 } { }
Address::Address(uintptr_t address) : m_address{ address } { }
Address::Address(void* address) : m_address{ reinterpret_cast<uintptr_t>(address) } { }

Address::operator bool()
{
	return m_address != 0 && this->valid();
}

bool Address::can_read()
{
	MEMORY_BASIC_INFORMATION mbi = { };

	if (!this->get_mbi(&mbi))
	{
		return false;
	}

	DWORD protection = mbi.Protect & ~(PAGE_GUARD | PAGE_NOCACHE | PAGE_WRITECOMBINE);

	if (protection == PAGE_EXECUTE || protection == PAGE_EXECUTE_READ || protection == PAGE_EXECUTE_READWRITE)
	{
		return true;
	}
}

bool Address::can_write()
{
	MEMORY_BASIC_INFORMATION mbi = { };

	if (!this->get_mbi(&mbi))
	{
		return false;
	}

	DWORD protection = mbi.Protect & ~(PAGE_GUARD | PAGE_NOCACHE | PAGE_WRITECOMBINE);

	if (protection == PAGE_EXECUTE || protection == PAGE_EXECUTE_READWRITE)
	{
		return true;
	}
}

bool Address::valid()
{
	if (!m_address)
	{
		return false;
	}

	MEMORY_BASIC_INFORMATION mbi = { };

	if (!this->get_mbi(&mbi))
	{
		return false;
	}

	if (mbi.State != MEM_COMMIT)
	{
		return false;
	}

	if (mbi.Protect == PAGE_NOACCESS || mbi.Protect == PAGE_GUARD || mbi.Protect == PAGE_EXECUTE)
	{
		return false;
	}

	return true;
}