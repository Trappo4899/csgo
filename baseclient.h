#pragma once

class IBaseClientDLL
{
private:

	enum
	{
		GETALLCLASSES = 8,
	};

public:

	ClientClass* GetAllClasses()
	{
		return VMT::call<GETALLCLASSES, ClientClass*>(this);
	}
};