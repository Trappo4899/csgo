#include "includes.h"

LRESULT __stdcall hkWndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	g_input->handle_wndproc(uMsg, wParam);

	return CallWindowProc(g_csgo->m_original_wndproc, hWnd, uMsg, wParam, lParam);
}