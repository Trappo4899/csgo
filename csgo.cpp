#include "includes.h"

/* TODO:

 - Re Write Virtual table class to be RAII
 - Think of a clean way to do hooking using new virtual table class

 - Reverse CMatSystemSurface for drawing methods
 - Get PaintTraverse and other hook setup so i can render properly
 - Get a rendering library done with drawlists so i can call drawing functions anywhere and have them drawn

*/

int CSGO::setup()
{
	if (!this->setup_modules())
	{
		return 0x100;
	}

	if (!this->setup_interfaces())
	{
		return 0x200;
	}

	if (!this->setup_patterns())
	{
		return 0x300;
	}

	if (!this->setup_netvars())
	{
		return 0x400;
	}

	if (!this->setup_cvars())
	{
		return 0x500;
	}

	if (!this->setup_variables())
	{
		return 0x600;
	}

	if (!this->setup_hooks())
	{
		return 0x700;
	}

	g_cl->log("Succesfully Setup");

	return 0x0;
}

bool CSGO::setup_modules()
{
	m_modules				= Modules();

	m_client_dll			= m_modules.get(L"client.dll");
	m_engine_dll			= m_modules.get(L"engine.dll");
	m_vstdlib_dll			= m_modules.get(L"vstdlib.dll");
	m_vgui_dll				= m_modules.get(L"vgui2.dll");
	m_vgui_material_dll		= m_modules.get(L"vguimatsurface.dll");

	return m_modules;
}

bool CSGO::setup_interfaces()
{
	m_interfaces		= Interfaces(m_modules);

	m_entity_list		= m_interfaces.get("VClientEntityList").as<IClientEntityList*>();
	m_engine_client		= m_interfaces.get("VEngineClient").as<IVEngineClient*>();
	m_base_client		= m_interfaces.get("VClient").as<IBaseClientDLL*>();
	m_debug_overlay		= m_interfaces.get("VDebugOverlay").as<IVDebugOverlay*>();
	m_surface			= m_interfaces.get("VGUI_Surface", m_vgui_material_dll).as<vgui::ISurface*>();
	m_panel				= m_interfaces.get("VGUI_Panel").as<vgui::IPanel*>();
	m_engine_vgui		= m_interfaces.get("VEngineVGui").as<vgui::IVEngineVgui*>();
	m_system			= m_interfaces.get("VGUI_System").as<ISystem*>();

	if (
			m_entity_list		== nullptr ||
			m_engine_client		== nullptr ||
			m_base_client		== nullptr ||
			m_debug_overlay		== nullptr ||
			m_surface			== nullptr ||
			m_panel				== nullptr ||
			m_engine_vgui		== nullptr ||
			m_system			== nullptr
	   )
	{
		return false;
	}

	return true;
}

bool CSGO::setup_patterns() 
{
	m_cvar				= m_vstdlib_dll.scan("\x8B\x0D\x00\x00\x00\x00\x85\xC9\x74\x26\x8B\x01\x8B\x80\x00\x00\x00\x00\xFF\xD0\x84\xC0", "xx????xxxxxxxx????xxxx").at(0x2).at<CCVar*>();
	m_start_drawing		= m_vgui_material_dll.get_address().as<tStartDrawing>(0xD390); //m_vgui_material_dll.scan("\xE8\x00\x00\x00\x00\x8B\x06\x8B\xCE\xFF\x75\x08\xFF\x50\x5C\x33\xF6\x66\x39\x33\x74\x09\x90", "x????xxxxxxxxxxxxxxxxxx").as<tStartDrawing>(0x1);
	m_end_drawing		= m_vgui_material_dll.get_address().as<tEndDrawing>(0xD570);   //m_vgui_material_dll.scan("\xE8\x00\x00\x00\x00\x8D\x65\xF0\x5F\x5E\x5B\x8B\xE5\x5D\xC2\x08\x00", "x????xxxxxxxxxxxx").as<tEndDrawing>(0x1);

	//printf("[+] StartDrawing	-> 0x%p\n", m_start_drawing);
	//printf("[+] EndDrawing		-> 0x%p\n", m_end_drawing);

	return m_cvar && m_start_drawing && m_end_drawing;
}

bool CSGO::setup_netvars()
{
	m_netvars = NetvarManager(m_base_client->GetAllClasses());

	return m_netvars;
}

bool CSGO::setup_cvars()
{
	m_cvars				= CVarManager(m_cvar);

	m_cv_aspectratio	= m_cvars.get("r_aspectratio");
	m_cv_postprocess	= m_cvars.get("mat_postprocess_enable");

	return m_cvars;
}

bool CSGO::setup_hooks()
{
	m_vmt_panel					= VMT(m_panel);
	m_vmt_engine_vgui			= VMT(m_engine_vgui);

	m_original_paint_traverse	= m_vmt_panel.hook<tPaintTraverse>(hkPaintTraverse, vgui::IPanel::PAINTTRAVERSE);
	m_original_paint			= m_vmt_engine_vgui.hook<tPaint>(hkPaint, vgui::IVEngineVgui::PAINT);

	m_original_wndproc = reinterpret_cast<WNDPROC>(SetWindowLongPtr(m_hwnd, GWLP_WNDPROC, (LONG_PTR)hkWndProc));

	if (
		!m_original_paint_traverse ||
		!m_original_paint
	   )
	{
		return false;
	}

	return true;
}

bool CSGO::setup_variables()
{
	m_hwnd = FindWindowA("Valve001", "Counter-Strike: Global Offensive - Direct3D 9");
	m_screen_size = { };

	return g_render->init_fonts() == 0x0 && m_hwnd;
}

CBasePlayer* CSGO::get_localplayer()
{
	return reinterpret_cast<CBasePlayer*>(this->m_entity_list->GetClientEntity(this->m_engine_client->GetLocalPlayerIdx()));
}