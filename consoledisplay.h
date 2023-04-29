#pragma once

class IConsoleDisplayFunc
{
private:

	enum : int
	{
		COLORPRINT = 0,
		PRINT = 1,
		DPRINT = 2,
	};

public:

	virtual void ColorPrint(const Color& clr, const char* pMessage) = 0;
	virtual void Print(const char* pMessage) = 0;
	virtual void DPrint(const char* pMessage) = 0;
};