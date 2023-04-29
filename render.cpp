#include "includes.h"

void DrawList::draw_filled_rect(float x, float y, float w, float h, Color col)
{
	g_csgo->m_surface->DrawSetColor(col);
	g_csgo->m_surface->DrawFilledRect(x, y, x + w, y + h);
}

void DrawList::draw_rect(float x, float y, float w, float h, Color col)
{
	g_csgo->m_surface->DrawSetColor(col);
	g_csgo->m_surface->DrawOutlineRect(x, y, x + w, y + h);
}

void DrawList::draw_line(float x0, float y0, float x1, float y1, Color col)
{
	g_csgo->m_surface->DrawSetColor(col);
	g_csgo->m_surface->DrawLine(x0, y0, x1, y1);
}

void DrawList::draw_text(vgui::HFont font, std::wstring text, float x, float y, int flags, Color col)
{
	g_csgo->m_surface->DrawSetTextColor(col);
	g_csgo->m_surface->DrawSetTextFont(font);

	auto size = g_csgo->m_surface->GetTextSize(font, text.c_str());

	if (flags & FONT_CENTERED)
	{
		x -= (size[0] / 2.f);
		y -= (size[1] / 2.f);
	}
	else if (flags & FONT_RIGHT)
	{
		x -= size[0];
	}
	else
	{
		
	}

	g_csgo->m_surface->DrawSetTextPos(x, y);
	g_csgo->m_surface->DrawPrintText(text.c_str(), wcslen(text.c_str()));
}

void DrawList::add_filled_rect(float x, float y, float w, float h, Color col, int precedence)
{
	RenderItem item = { };

	item.x = x;
	item.y = y;
	item.w = w;
	item.h = h;
	item.col = col;
	item.shape = Shapes::FILLED_RECT;

	m_drawlist.push_back({ precedence, item });
}

void DrawList::add_rect(float x, float y, float w, float h, Color col, int precedence)
{
	RenderItem item = { };

	item.x = x;
	item.y = y;
	item.w = w;
	item.h = h;
	item.col = col; 
	item.shape = Shapes::RECT;

	m_drawlist.push_back({ precedence, item });
}

void DrawList::add_line(float x0, float y0, float x1, float y1, Color col, int precedence)
{
	RenderItem item = { };

	item.x0 = x0;
	item.y0 = y0;
	item.x1 = x1;
	item.y1 = y1;
	item.col = col;
	item.shape = Shapes::LINE;

	m_drawlist.push_back({ precedence, item });
}

void DrawList::add_text(vgui::HFont font, std::wstring text, float x, float y, int flags, Color col, int precedence)
{
	RenderItem item = { };

	item.font = font;
	item.text = text;
	item.x = x;
	item.y = y;
	item.col = col;
	item.flags = flags;
	item.shape = Shapes::TEXT;

	m_drawlist.push_back({ precedence, item });
}

/* needed for std::sort - used to 
sort all items by precedence level */
bool drawlist_comparison(std::pair<int, DrawList::RenderItem> a, std::pair<int, DrawList::RenderItem> b)
{
	return a.first < b.first;
}

void DrawList::render()
{
	if (!m_drawlist.size())
	{
		return;
	}

	std::sort(m_drawlist.begin(), m_drawlist.end(), drawlist_comparison);

	for (const auto& draw_item : m_drawlist)
	{
		const auto& item = draw_item.second;

		switch (item.shape)
		{
		case Shapes::FILLED_RECT:
			draw_filled_rect(item.x, item.y, item.w, item.h, item.col);
			continue;

		case Shapes::RECT:
			draw_rect(item.x, item.y, item.w, item.h, item.col);
			continue;

		case Shapes::LINE:
			draw_line(item.x0, item.y0, item.x1, item.y1, item.col);
			continue;

		case Shapes::TEXT:
			draw_text(item.font, item.text, item.x, item.y, item.flags, item.col);
			continue;
		}
	}

	m_drawlist.clear();
}

void Renderer::filled_rect(float x, float y, float w, float h, Color col, int precedence)
{
	m_drawlist.add_filled_rect(x, y, w, h, col, precedence);
}

void Renderer::rect(float x, float y, float w, float h, Color col, int precedence)
{
	m_drawlist.add_rect(x, y, w, h, col, precedence);
}

void Renderer::line(float x0, float y0, float x1, float y1, Color col, int precedence)
{
	m_drawlist.add_line(x0, y0, x1, y1, col, precedence);
}

void Renderer::text(vgui::HFont font, std::wstring text, float x, float y, int flags, Color col, int precedence)
{
	m_drawlist.add_text(font, text.c_str(), x, y, flags, col, precedence);
}

void Renderer::text(vgui::HFont font, std::string text, float x, float y, int flags, Color col, int precedence)
{
	auto len =  MultiByteToWideChar(CP_UTF8, 0, text.data(), text.size(), nullptr, 0);

	auto wstr = std::wstring(len, 0);

	MultiByteToWideChar(CP_UTF8, 0, text.data(), text.size(), &wstr[0], len);

	this->text(font, wstr, x, y, flags, col, precedence);
}

void Renderer::csgo_small(const wchar_t* text, float x, float y, int flags, Color col)
{
	m_drawlist.add_text(m_font_csgo_small, text, x, y, flags, col);
}

int Renderer::init_fonts()
{
	m_font_csgo_small	= 5;

	m_font_small_fonts	= g_csgo->m_surface->CreateFont();
	m_font_menu			= g_csgo->m_surface->CreateFont();

	if (!g_csgo->m_surface->SetFontGlyphSet(m_font_small_fonts,		"Small Fonts",	10,	400, 0, 0, vgui::FONTFLAG_OUTLINE) ||
		!g_csgo->m_surface->SetFontGlyphSet(m_font_menu,			"Verdana",		12, 200, 0, 0, vgui::FONTFLAG_OUTLINE))
	{
		return 0x1;
	}

	return 0x0;
}

void Renderer::render()
{
	m_drawlist.render();
}