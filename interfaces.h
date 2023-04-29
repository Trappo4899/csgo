#pragma once

typedef void* (*CreateInterfaceFn)(const char* pName, int* pReturnCode);
typedef void* (*InstantiateInterfaceFn)();

// Used internally to register classes.
class InterfaceReg
{
public:
	InterfaceReg(InstantiateInterfaceFn fn, const char* pName);

public:

	InstantiateInterfaceFn		m_CreateFn;
	const char*					m_pName;
	InterfaceReg*				m_pNext; // For the global list.
};

/*

the exported function CreateInterface calls a function called CreateInterfaceInternal
which loops a global list containing all interfaces 

*/

class Interfaces
{
private:

	std::vector<std::pair<Address, std::string>> m_interfaces;

public:

	Interfaces();
	Interfaces(Modules modules);

	operator bool();

	Address get(const char* name, Module mod = Module());

	void print();
};