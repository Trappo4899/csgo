#include "includes.h"

Interfaces::Interfaces()
{
	m_interfaces = { };
}

Interfaces::Interfaces(Modules modules)
{
	for (auto mod : modules.get_modules())
	{
		auto create_interface = mod.get_pe().get_exports().get("CreateInterface").get_address();

		/*
		
.text:0099BCF0                                                                 public CreateInterface
.text:0099BCF0                                                 CreateInterface proc near               ; DATA XREF: .rdata:off_D986A8↓o
.text:0099BCF0 55                                                              push    ebp
.text:0099BCF1 8B EC                                                           mov     ebp, esp
.text:0099BCF3 5D                                                              pop     ebp
.text:0099BCF4 E9 87 FF FF FF                                                  jmp     CreateInterfaceInternal_1D30 - we want to get to this function
.text:0099BCF4                                                 CreateInterface endp
		

		
.text:0099BC80                                                 CreateInterfaceInternal_1D30 proc near  ; CODE XREF: CreateInterface+4↓j
.text:0099BC80
.text:0099BC80                                                 pName           = dword ptr  8
.text:0099BC80                                                 pReturnCode     = dword ptr  0Ch
.text:0099BC80
.text:0099BC80 55                                                              push    ebp
.text:0099BC81 8B EC                                                           mov     ebp, esp
.text:0099BC83 56                                                              push    esi
.text:0099BC84 8B 35 EC CD 24 03                                               mov     esi, Interfaces_324CDEC - we want to get the address of this list
.text:0099BC8A 57                                                              push    edi

		*/

		if (!create_interface)
		{
			continue;
		}

			// the jump is 4 bytes into the exported create interface function
		auto jmp = Address(create_interface.as<uintptr_t>(0x4));

			// verify the jump is actually there in the future maybe scan for it instead as its possible some
			// abstract module doesent have it hardcoded at 4 bytes in
		if (jmp.at<char>() != '\xE9')
		{
			continue;
		}

			// get the jump displacement as the operand to a jump is a relative address
			// to were its jumping to from the address its jumping
		auto displacement = jmp.at(0x1);
			
			// calculate the actual address of were the real create interface is by doing what cpu would do
			// when executing the actual jump instruction (EIP + RVA + size of instruction)
		auto create_interface_internal = Address(jmp.as<uintptr_t>() + displacement.as<uintptr_t>() + 0x5);

		if (!create_interface_internal)
		{
			continue;
		}

			// read were the mov is into the real create interface function
		auto mov = Address(create_interface_internal.as(0x4));

			// read the list ( read it twice because we need to read the operand of the mov first then read the address )
		InterfaceReg* pList = mov.at(0x2).at<InterfaceReg*>();

			// loop the global interface list
		for (InterfaceReg* curr = pList; curr != nullptr; curr = curr->m_pNext)
		{
			std::string name = curr->m_pName;

			name = name.substr(0, name.size() - 3);

			m_interfaces.push_back({ Address(curr->m_CreateFn()), name });
		}
	}
}

Interfaces::operator bool()
{
	return !m_interfaces.empty();
}

	/* Allow the user to specify a module as some interfaces can have the same name but be different */
Address Interfaces::get(const char* name, Module mod)
{
	for (auto curr : m_interfaces)
	{
		if (mod.get_address())
		{
			auto optional = mod.get_pe().get_optional();

			if (optional == nullptr || !optional)
			{
				continue;
			}

			/* if the interfaces address range isnt inside of the module then we dont want to use it */
			if (curr.first.as<uintptr_t>() < optional->ImageBase || curr.first.as<uintptr_t>() > optional->ImageBase + optional->SizeOfImage)
			{
				continue;
			}
		}

		if (HASH(curr.second) == HASH(name))
		{
			return curr.first;
		}
	}

	return Address{ };
}

void Interfaces::print()
{
	for (auto curr : m_interfaces)
	{
		printf("%s		->		0x%llX\n", curr.second.c_str(), curr.first.as<UINT_PTR>());
	}
}