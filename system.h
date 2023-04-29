#pragma once

#undef ShellExecute
#undef GetCurrentTime

class ISystem
{
private:

	enum : int
	{
		SHELLEXECUTE = 3,
		GETFRAMETIME = 4,
		GETCURRENTTIME = 5,
		GETTIMEMILLIS = 6,
		GETCLIPBOARDTEXTCOUNT = 7,
		SETCLIPBOARDTEXT = 8,
		SETCLIPBOARDTEXTW = 9,
		GETCLIPBOARDTEXT = 10,
		GETCLIPBOARDTEXTW = 11,
	};

public:

	void ShellExecute(const char* cmd, const char* file)
	{
		VMT::call<SHELLEXECUTE, void, const char*, const char*>(this, cmd, file);
	}

	long GetTimeMillis()
	{
		return VMT::call<GETTIMEMILLIS, long>(this);
	}

	double GetFrameTime()
	{
		return VMT::call<GETFRAMETIME, double>(this);
	}

	double GetCurrentTime()
	{
		return VMT::call<GETCURRENTTIME, double>(this);
	}

	int GetClipboardTextCount()
	{
		return VMT::call<GETCLIPBOARDTEXTCOUNT, int>(this);
	}

	void SetClipboardText(const char* text, int textLen)
	{
		VMT::call<SETCLIPBOARDTEXT, void, const char*, int>(this, text, textLen);
	}

	void SetClipboardText(const wchar_t* text, int textLen)
	{
		VMT::call<SETCLIPBOARDTEXTW, void, const wchar_t*, int>(this, text, textLen);
	}

	int GetClipboardText(int offset, char* buf, int bufLen)
	{
		return VMT::call<GETCLIPBOARDTEXT, int, int, char*, int>(this, offset, buf, bufLen);
	}

	int GetClipboardText(int offset, wchar_t* buf, int bufLen)
	{
		return VMT::call<GETCLIPBOARDTEXTW, int, int, wchar_t*, int>(this, offset, buf, bufLen);
	}
};