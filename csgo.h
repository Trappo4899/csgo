#pragma once

typedef void(__thiscall* tPaintTraverse)(void*, int, bool, bool);
typedef void(__thiscall* tPaint)(void*, vgui::PaintMode_t);
typedef void(__thiscall* tStartDrawing)(void*);
typedef void(__thiscall* tEndDrawing)(void*);

void __stdcall hkPaintTraverse(int vpanel, bool popups, bool allowForce);
void __stdcall hkPaint(vgui::PaintMode_t paintMode);
LRESULT __stdcall hkWndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

class CSGO
{
private:

public:

	int setup();

	bool setup_modules();
	bool setup_interfaces();
	bool setup_patterns();
	bool setup_netvars();
	bool setup_cvars();
	bool setup_hooks();
	bool setup_variables();

public:

	CBasePlayer* get_localplayer();

public:

	/* managers */
	Modules					m_modules;
	Interfaces				m_interfaces;
	NetvarManager			m_netvars;
	CVarManager				m_cvars;

public:

	/* modules */
	Module					m_client_dll;
	Module					m_engine_dll;
	Module					m_vstdlib_dll;
	Module					m_vgui_dll;
	Module					m_vgui_material_dll;

public:

	/* interfaces */
	IClientEntityList*		m_entity_list;
	IVEngineClient*			m_engine_client;
	IBaseClientDLL*			m_base_client;
	IVDebugOverlay*			m_debug_overlay;
	vgui::ISurface*			m_surface;
	vgui::IPanel*			m_panel;
	vgui::IVEngineVgui*		m_engine_vgui;
	IConsoleDisplayFunc*	m_console_display;
	ISystem*				m_system;

public:

	/* patterns */
	CCVar*					m_cvar;

	tStartDrawing			m_start_drawing;
	tEndDrawing				m_end_drawing;

public:

	/* netvars */


public:

	/* cvars */
	ConVar*					m_cv_aspectratio;
	ConVar*					m_cv_postprocess;

public:

	/* vmt hooks */
	VMT						m_vmt_panel;
	VMT						m_vmt_engine_vgui;

	/* hook originals */
	tPaintTraverse			m_original_paint_traverse;
	tPaint					m_original_paint;
	WNDPROC					m_original_wndproc;

public: /* variables */

	HWND					m_hwnd;
	Vector2					m_screen_size;
};

extern std::unique_ptr<CSGO> g_csgo;