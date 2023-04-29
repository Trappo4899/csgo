#pragma once

#include "pe.h"

class Module
{
private:

	Address m_address;
	PE m_pe;
	const wchar_t* m_name;

public:

	Module();
	Module(Address addr, const wchar_t* name); 

	Address get_address();

	PE get_pe();

	const wchar_t* get_name();

	Address scan(const char* pattern, const char* mask);
	Address scan(const char* ida_pattern);
};

class Modules
{
private:

	std::vector<Module> m_modules;

public:

	Modules();

	operator bool( );

	static Address get_module(const wchar_t* name);

	void Print();

	Module get(const wchar_t* name);

	std::vector<Module> get_modules();
};