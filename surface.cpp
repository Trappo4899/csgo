#include "includes.h"

void __stdcall hkPaintTraverse(int vpanel, bool popups, bool allowForce)
{
	g_csgo->m_original_paint_traverse(g_csgo->m_panel, vpanel, popups, allowForce);
}

void __stdcall hkPaint(vgui::PaintMode_t paintMode)
{
	g_csgo->m_original_paint(g_csgo->m_engine_vgui, paintMode);

	g_csgo->m_start_drawing(g_csgo->m_surface);

	g_input->update();

	if (paintMode & vgui::PaintMode_t::PAINT_UIPANELS)
	{
		/* renders above everything all the time */
		g_cl->draw_logs();

		g_menu->think();
	}
	else if (paintMode & vgui::PaintMode_t::PAINT_INGAMEPANELS)
	{
		/* only renders in game and below console window */
		g_features->visuals.think();
	}

	g_render->render();

	g_csgo->m_end_drawing(g_csgo->m_surface);
}