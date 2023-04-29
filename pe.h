#pragma once

class Export
{
private:

	Address m_address;
	const char* m_name;

public:

	Export();
	Export(Address address, const char* name);

	operator bool();

	Address get_address();

	const char* get_name();
};

class Exports
{
private:

	std::vector<Export> m_exports;

public:

	Exports();
	Exports(PIMAGE_OPTIONAL_HEADER optional);

	operator bool();

	Export get(const char* name);

	void Print();
};

class Import
{
private:

	Address m_address;
	const char* m_name;

public:

	Import();
	Import(Address address, const char* name);

	operator bool();

	Address get_address();

	const char* get_name();
};

class Imports
{
private:

	std::vector<Import> m_imports;

public:

	Imports();
	Imports(PIMAGE_OPTIONAL_HEADER optional);

	operator bool();

	Import get(const char* name);

	void Print();
};

class PE
{
private:

	PIMAGE_DOS_HEADER			m_dos;
	PIMAGE_NT_HEADERS			m_nt;
	PIMAGE_FILE_HEADER			m_file;
	PIMAGE_OPTIONAL_HEADER		m_optional;

	Exports m_exports;
	Imports m_imports;

public:

	PE();
	PE(Address addr);

	operator bool();

	PIMAGE_DOS_HEADER get_dos();

	PIMAGE_NT_HEADERS get_nt();

	PIMAGE_FILE_HEADER get_file();

	PIMAGE_OPTIONAL_HEADER get_optional();

	Exports get_exports();

	Imports get_imports();
};