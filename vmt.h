#pragma once

#ifdef _WIN64
#define OPCODE_SIZE 0x8
#else
#define OPCODE_SIZE 0x4
#endif

class VMT
{
private:

	struct hook_t
	{
		Address		hook;
		Address		original;
		UINT_PTR	index;
	};

private:

	Address m_vtable;

	std::vector<hook_t> m_hooks;

public:

	VMT()
	{
		m_vtable	= nullptr;
		m_hooks		= { };
	}

	VMT(Address vtable)
	{ 
		m_vtable	= vtable;
		m_hooks		= { };
	}

	~VMT()
	{
		for (auto hk : m_hooks)
		{
			DWORD oProt = { };

			if (!VirtualProtect(hk.hook.as<LPVOID>(), sizeof(PVOID), PAGE_EXECUTE_READWRITE, &oProt))
			{
				return;
			}

			hk.hook.at() = hk.original;

			if (!VirtualProtect(hk.hook.as<LPVOID>(), sizeof(PVOID), oProt, &oProt))
			{
				return;
			}
		}
	}

public:

	template<typename T>
	T hook(PVOID hook, UINT_PTR idx)
	{
		if (!m_vtable)
		{
			return false;
		}

		UINT_PTR vtable = m_vtable.at<UINT_PTR>();

		if (!vtable)
		{
			return false;
		}

		UINT_PTR func = (vtable + (idx * OPCODE_SIZE));

		if (!func)
		{
			return false;
		}

		UINT_PTR orig = *(uintptr_t*)func;

		if (!orig)
		{
			return false;
		}

		DWORD old_protection = { };

		if (!VirtualProtect((LPVOID)func, sizeof(func), PAGE_EXECUTE_READWRITE, &old_protection))
		{
			return false;
		}

		*(uintptr_t*)func = (uintptr_t)hook;

		if (!VirtualProtect((LPVOID)func, sizeof(func), old_protection, &old_protection))
		{
			return false;
		}

		m_hooks.push_back(
			{
				hook,
				orig,
				idx
			}
		);

		return (T)orig;
	}

public:

	/*template<typename R = PVOID, typename T = PVOID>
	static R hook(PVOID virtual_table, int index, T function)
	{
		uintptr_t vtable	= *(uintptr_t*)virtual_table;
		uintptr_t func		=  (vtable + (index * OPCODE_SIZE));
		uintptr_t orig		= *(uintptr_t*)func;

		DWORD old_protection = { };

		if (!VirtualProtect((LPVOID)func, sizeof(func), PAGE_EXECUTE_READWRITE, &old_protection))
		{
			return nullptr;
		}

		*(uintptr_t*)func = (uintptr_t)function;

		if (!VirtualProtect((LPVOID)func, sizeof(func), old_protection, &old_protection))
		{
			return nullptr;
		}

		return (R)orig;
	}*/

	template <const size_t index, class Return, typename ... Arguments>
	static Return call(PVOID virtual_table, Arguments ... args)
	{
		if (virtual_table != nullptr)
		{
			typedef Return(__thiscall* tFn)(void*, decltype(args) ... );
			return (*(tFn**)virtual_table)[index](virtual_table, args ...);
		}
		
		return Return{ };
	}
};