#pragma once

class Address
{
private:

	uintptr_t m_address;

private:

	bool get_mbi(MEMORY_BASIC_INFORMATION* mbi_out);

public:

	Address();
	Address(uintptr_t address);
	Address(void* address);

	operator bool();

	template<typename T = Address>
	T as( )
	{
		return m_address ? (T)m_address : T{ };
	}

	template<typename T = Address>
	T as( uintptr_t offset )
	{
		return m_address ? (T)(m_address + offset) : T{ };
	}

	template<typename T = Address>
	T at( )
	{
		return m_address ? *(T*)(m_address) : T{ };
	}

	template<typename T = Address>
	T at( uintptr_t offset )
	{
		return m_address ? *(T*)(m_address + offset) : T{ };
	}

	template<typename T = Address>
	T get(std::vector<uintptr_t> offsets)
	{
		if (m_address)
		{
			T out = { };

			for (auto curr : offsets)
			{
				out = *(T*)(m_address + curr);
			}

			return out;
		}
		
		return T{ };
	}

	bool can_read();
	bool can_write();
	bool valid();
};