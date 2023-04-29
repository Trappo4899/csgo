#include "includes.h"

bool CVisuals::get_bounding_box(CBaseEntity* entity, Box& box)
{
	Vector3 min = { };
	Vector3 max = { };

	entity->GetRenderBounds(min, max);

	Vector3 points[] = {	Vector3(min[0], min[1], min[2]),	//	back	-	left	-	back
							Vector3(min[0], max[1], min[2]),	//	back	-	right	-	back
							Vector3(max[0], max[1], min[2]),	//	front	-	right	-	back
							Vector3(max[0], min[1], min[2]),	//	front	-	left	-	back
							Vector3(max[0], max[1], max[2]),	//	front	-	right	-	top
							Vector3(min[0], max[1], max[2]),	//	back	-	right	-	top
							Vector3(min[0], min[1], max[2]),	//	back	-	left	-	top
							Vector3(max[0], min[1], max[2])		//	front	-	left	-	top
	};

	Vector3 transformed[8] = { };

	for (int i = 0; i < 8; i++)
	{
		transformed[i] = math::model_to_world(points[i], entity->GetRenderableToWorldTransform());
	}

	Vector3 flb = { };
	Vector3 brt = { };
	Vector3 blb = { };
	Vector3 frt = { };
	Vector3 frb = { };
	Vector3 brb = { };
	Vector3 blt = { };
	Vector3 flt = { };

	if (	!g_csgo->m_debug_overlay->WorldToScreen(transformed[3], flb) || !g_csgo->m_debug_overlay->WorldToScreen(transformed[5], brt)
		||	!g_csgo->m_debug_overlay->WorldToScreen(transformed[0], blb) || !g_csgo->m_debug_overlay->WorldToScreen(transformed[4], frt)
		||	!g_csgo->m_debug_overlay->WorldToScreen(transformed[2], frb) || !g_csgo->m_debug_overlay->WorldToScreen(transformed[1], brb)
		||	!g_csgo->m_debug_overlay->WorldToScreen(transformed[6], blt) || !g_csgo->m_debug_overlay->WorldToScreen(transformed[7], flt))
		return false;

	Vector3 arr[] = { flb, brt, blb, frt, frb, brb, blt, flt };

	float left		= flb[0];	// left
	float top		= flb[1];	// top
	float right		= flb[0];	// right
	float bottom	= flb[1];	// bottom

	for (int i = 1; i < 8; i++)
	{
		if (left > arr[i][0])
		{
			left = arr[i][0];
		}

		if (top < arr[i][1])
		{
			top = arr[i][1];
		}

		if (right < arr[i][0])
		{
			right = arr[i][0];
		}

		if (bottom > arr[i][1])
		{
			bottom = arr[i][1];
		}
	}

	box[2] = right - left;
	box[3] = top - bottom;
	box[0] = left + (box[2] / 8.f);
	box[1] = bottom;

	return true;
}

void CVisuals::draw_box(Box box, Color col)
{
	g_render->rect(box[0] - 1.f, box[1] - 1.f, box[2] + 2.f, box[3] + 2.f, Color(0, 0, 0, col.a()));
	g_render->rect(box[0] + 1.f, box[1] + 1.f, box[2] - 2.f, box[3] - 2.f, Color(0, 0, 0, col.a()));

	g_render->rect(box[0], box[1], box[2], box[3], col);
}

void CVisuals::draw_bar(Box box, float val, float max, Color from, Color to, BOX_POSITION pos)
{
	static const float padding = 8.5f;

	if (val == 0.f || max == 0.f)
	{
		return;
	}

	bool draw_val = val != max;

	if (val > max)
	{
		max = val;
	}

	float percent = val / max;

	if (percent <= 0.f)
	{
		return;
	}

	auto col = math::colour_interpolation(to, from, 0.f, max, val);

	switch (pos)
	{
	case BOX_POSITION::TOP:
		g_render->filled_rect(box[0] - 1, box[1] - m_padding_top[1] - 7, box[2] + 2, 4, Color(0, 0, 0, col.a()));
		g_render->filled_rect(box[0] + box[2] - (box[2] - (box[2] * percent)), box[1] - m_padding_top[1] - 6, -(box[2] * percent), 2, col);

		if (draw_val)
		{
			g_render->text(g_render->m_font_small_fonts, std::to_wstring((int)val), box[0] + box[2] - (box[2] - (box[2] * percent)), box[1] - m_padding_top[1] - 6, FONT_CENTERED, Color(255, 255, 255, col.a()));
		}

		m_padding_top[1] += padding;
		break;
	case BOX_POSITION::BOTTOM:
		g_render->filled_rect(box[0] - 1, box[1] + box[3] + m_padding_bottom[1] + 6, box[2] + 2, 4, Color(0, 0, 0, col.a()));
		g_render->filled_rect(box[0] + box[2] - (box[2] - (box[2] * percent)), box[1] + box[3] + m_padding_bottom[1] + 7, -(box[2] * percent), 2, col);

		if (draw_val)
		{
			g_render->text(g_render->m_font_small_fonts, std::to_wstring((int)val), box[0] - 1, box[1] + box[3] + m_padding_bottom[1] + 6, FONT_CENTERED, Color(255, 255, 255, col.a()));
		}

		m_padding_bottom[1] += padding;
		break;
	case BOX_POSITION::LEFT:
		g_render->filled_rect(box[0] - m_padding_left[0] - 6, box[1] - 1, 4, box[3] + 2, Color(0, 0, 0, col.a()));
		g_render->filled_rect(box[0] - m_padding_left[0] - 5, box[1] + (box[3] - (box[3] * percent)), 2, (box[3] * percent), col);

		if (draw_val)
		{
			g_render->text(g_render->m_font_small_fonts,
				std::to_wstring((int)val),
				(box[0] - m_padding_left[0] - 6) + 
				(g_csgo->m_surface->GetTextSize(g_render->m_font_small_fonts, std::to_wstring((int)val).c_str())[0] / 4),
				box[1] + (box[3] - (box[3] * percent)),
				FONT_CENTERED,
				Color(255, 255, 255, col.a())
			);
		}

		m_padding_left[0] += padding;
		break;
	case BOX_POSITION::RIGHT:
		g_render->filled_rect(box[0] + box[2] + m_padding_right[0] + 3, box[1] - 1, 4, box[3] + 2, Color(0, 0, 0, col.a()));
		g_render->filled_rect(box[0] + box[2] + m_padding_right[0] + 4, box[1] + (box[3] - (box[3] * percent)), 2, (box[3] * percent), col);

		if (draw_val)
		{
			g_render->text(g_render->m_font_small_fonts, std::to_wstring((int)val), box[0] + box[2] + m_padding_right[0] + 3, box[1] - 1, FONT_CENTERED, Color(255, 255, 255, col.a()));
		}

		m_padding_right[0] += padding;
		break;
	}
}

void CVisuals::draw_text(Box box, vgui::HFont font, const wchar_t* text, Color col, int flags, BOX_POSITION pos)
{
	static float padding = 10.5f;

	switch (pos)
	{
	case BOX_POSITION::TOP:

		g_render->text(font, text,
			box[0] + (box[2] / 2) - m_padding_top[0],
			box[1] - m_padding_top[1] - 6.5f, 
			flags,
			col	);

		m_padding_top[1] += padding;
		break;

	case BOX_POSITION::BOTTOM:

		g_render->text(font, text,
			box[0] + (box[2] / 2) - m_padding_bottom[0],
			box[1] + box[3] + m_padding_bottom[1] + 0.75f,
			flags,
			col );

		m_padding_bottom[1] += padding;
		break;

	case BOX_POSITION::RIGHT:

		g_render->text(font, text,
			box[0] + box[2] + m_padding_right[0] + 5.f,
			box[1] + m_padding_right[1] + 1.5f,
			flags,
			col );

		m_padding_right[1] += padding;
		break;

	case BOX_POSITION::LEFT:

		g_render->text(font, text,
			box[0] - m_padding_left[0],
			box[1] + m_padding_left[1] + 1.5f,
			flags,
			col );

		m_padding_left[1] += padding;
		break;
	}
}

void CVisuals::draw_text(Box box, vgui::HFont font, const char* text, Color col, int flags, BOX_POSITION pos)
{
	static float padding = 10.5f;

	switch (pos)
	{
	case BOX_POSITION::TOP:

		g_render->text(font, text,
			box[0] + (box[2] / 2) - m_padding_top[0],
			box[1] - m_padding_top[1] - 6.5f,
			flags,
			col);

		m_padding_top[1] += padding;
		break;

	case BOX_POSITION::BOTTOM:

		g_render->text(font, text,
			box[0] + (box[2] / 2) - m_padding_bottom[0],
			box[1] + box[3] + m_padding_bottom[1] + 4.75f,
			flags,
			col);

		m_padding_bottom[1] += padding;
		break;

	case BOX_POSITION::RIGHT:

		g_render->text(font, text,
			box[0] + box[2] + m_padding_right[0] + 5.f,
			box[1] + m_padding_right[1] + 1.5f,
			flags,
			col);

		m_padding_right[1] += padding;
		break;

	case BOX_POSITION::LEFT:

		g_render->text(font, text,
			box[0] - m_padding_left[0],
			box[1] + m_padding_left[1] + 1.5f,
			flags,
			col);

		m_padding_left[1] += padding;
		break;
	}
}

void CVisuals::reset_padding()
{
	m_padding_top		= { };
	m_padding_bottom	= { };
	m_padding_left		= { };
	m_padding_right		= { };
}

void CVisuals::player(CBasePlayer* player)
{
	Box box						= { };
	player_info_t player_info	= { };

	if ( !this->get_bounding_box(player, box) || 
		 !g_csgo->m_engine_client->GetPlayerInfo(player->EntIndex(), &player_info))
	{
		return;
	}

	/* draw box */
	this->draw_box(box, Color(255, 255, 255, 225));

	/* draw all bars*/
	this->draw_bar(box, player->GetHealth(), player->GetMaxHealth(), Color(137, 245, 3, 225), Color(235, 73, 73, 225), LEFT);

	/* draw all text */
	this->draw_text(box, 5, player_info.name, Color(255, 255, 255, 225), FONT_CENTERED, TOP);

	this->draw_text(box, 
		g_render->m_font_menu,

		std::to_string(int(g_csgo->get_localplayer()->GetAbsOrigin().distance(player->GetAbsOrigin().get()) / 100.f)).c_str(),

		Color(255, 255, 255, 255), 
		FONT_CENTERED, 
		BOTTOM);
}

void CVisuals::weapon(CBaseEntity* weapon)
{
	Box box = { };

	if (!this->get_bounding_box(weapon, box))
	{
		return;
	}

	this->draw_box(box, Color(255, 255, 255, 225));

	this->draw_text(box, 5, L"weapon", Color(255, 255, 255, 225), FONT_CENTERED, TOP);
}

void CVisuals::think()
{
	for (int i = 0; i < g_csgo->m_entity_list->NumberOfEntities(true); i++)
	{
		if (i == g_csgo->m_engine_client->GetLocalPlayerIdx())
		{
			continue;
		}

		auto ent = g_csgo->m_entity_list->GetClientEntity(i);

		if (ent == nullptr)
		{
			continue;
		}

		if (ent->IsPlayer() && ent->IsAlive())
		{
			this->player(reinterpret_cast<CBasePlayer*>(ent));

			this->reset_padding();
		}
	}
}