#pragma once

/*
	to do:

	add more hooking methods such as exception and breakpoint hooking
	trampoline very haram try to only use VMT hooking until exception or breakpoints
	are implemented

	Breakpoint hooking idea:
		get the thread context change the dr0 - dr3 registers to cause a software breakpoint 
		then redirect it to our code then go back

	Exception hooking idea:
		create an exception handler for the current thread and cause an exception in the place to hook
		so it will jump to our exception hanlder were we can execute our own code then it will automatically
		go back to the to hook code and continue executionas normal

	both of these methods are good as they dont actually change anything major only cause a pre defined routine to
	go through so would be much harder to detect then simply changing a function to jump to our own then jump back
	like we do in trampoline hooking

*/

enum class HOOK_TYPE
{
	TRAMPOLINE = 0,
};

typedef struct _HOOK
{
	Address addr;
	PVOID hk;
	PVOID orig;
	int len;
}HOOK, * PHOOK;

class Hooking
{
private:

	HOOK m_hook;
	HOOK_TYPE m_type;

public:

	Hooking();
	Hooking(HOOK hk, HOOK_TYPE type);

	operator bool();

	bool trampoline();

	bool hook();
	bool remove();
};