#include "includes.h"

Hooking::Hooking()
{
	m_hook = { };
	m_type = { };
}

Hooking::Hooking(HOOK hk, HOOK_TYPE type)
{
	m_hook = hk;
	m_type = type;
}

Hooking::operator bool()
{
	return m_hook.addr;
}

bool Hooking::trampoline()
{
	if (m_hook.len < 5)
	{
		return false;
	}

	/*

before (target_func):

	push ebp
	mov ebp, esp
	sub esp, 35h
	...

	----------------------

after (target_func):

	jmp our_func
	...

	-----------------------

our_func:
	...
	call gateway

	-----------------------

gateway:

	push ebp
	mov ebp, esp
	sub esp, 35h
	jmp target_func

*/

/* first thing we need to do is copy the bytes we are going to overwrite to our own memory so we can run them later */

		// allocate memory for stolen bytes
	PVOID gateway_alloc = VirtualAlloc(nullptr, 4096, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);

	if (gateway_alloc == nullptr || !gateway_alloc)
	{
		return false;
	}

		// copy the bytes we are going to steal to allocated memory
	memcpy(gateway_alloc, m_hook.addr.as<PVOID>(), m_hook.len);

		// calculate relative address for the jmp operand
	uintptr_t relative_gateway_addr = (m_hook.addr.as<uintptr_t>() - reinterpret_cast<uintptr_t>(gateway_alloc)) - 5;

		// write a uncoditional jump to gateway after stolen bytes
	*reinterpret_cast<char*>(reinterpret_cast<uintptr_t>(gateway_alloc) + m_hook.len) = '\xE9';

		// write the operand to the jump
	*reinterpret_cast<uintptr_t*>(reinterpret_cast<uintptr_t>(gateway_alloc) + m_hook.len + 1) = relative_gateway_addr;

/* now we have to do a detour on the target function */

		// calculate the relative address to our replacement function
	uintptr_t relative_hook_addr = (m_hook.addr.as<uintptr_t>() - reinterpret_cast<uintptr_t>(m_hook.hk)) - 5;

	DWORD old_protection = 0;


	if (!VirtualProtect(m_hook.addr.as<LPVOID>(), m_hook.len, PAGE_EXECUTE_READWRITE, &old_protection))
	{
		return false;
	}

		// set all bytes we are overwriting to nop(0x90)
	memset(m_hook.addr.as<PVOID>(), 0x90, m_hook.len); // - sometimes harams

		// write the jump to the start of the function
	*reinterpret_cast<char*>(m_hook.addr.as<uintptr_t>()) = '\xE9';

		// write the operand to the jump
	*reinterpret_cast<uintptr_t*>(m_hook.addr.as<uintptr_t>() + 1) = relative_hook_addr;

	if (!VirtualProtect(m_hook.addr.as<LPVOID>(), m_hook.len, old_protection, &old_protection))
	{
		return false;
	}

	return true;
}

bool Hooking::hook()
{
	switch (m_type)
	{
	case HOOK_TYPE::TRAMPOLINE: {
		return this->trampoline();
	}

	default: {
		return false;
	}
	}

	return false;
}

bool Hooking::remove()
{
	return false;
}

//bool Hooks::add_trampoline(Address addr, PVOID hook, PVOID original, int len)
//{
//	if (hook == nullptr || !hook || original == nullptr || !original)
//	{
//		return false;
//	}
//
//	HOOK hk = { };
//
//	hk.addr		= addr;
//	hk.hk		= hook;
//	hk.orig		= original;
//	hk.len		= len;
//
//	Hooking hook_cl = Hooking(hk, HOOK_TYPE::TRAMPOLINE);
//
//	if (!hook_cl)
//	{
//		return false;
//	}
//
//	m_hooks.push_back(hook_cl);
//
//	return true;
//}
//
//bool Hooks::enable(int idx)
//{
//	return m_hooks.at(idx).hook();
//}
//
//bool Hooks::remove(int idx)
//{
//	return m_hooks.at(idx).remove();
//}
//
//bool Hooks::enable_all()
//{
//	bool bRet = false;
//
//	for (auto hk : m_hooks)
//	{
//		bRet = hk.hook();
//	}
//
//	return bRet;
//}
//
//bool Hooks::remove_all()
//{
//	bool bRet = false;
//
//	for (auto hk : m_hooks)
//	{
//		bRet = hk.remove();
//	}
//
//	return bRet;
//}