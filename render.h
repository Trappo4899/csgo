#pragma once

/* main idea from imgui

	this system works by pushing back to be drawn items into
	a list so they can be rendered where we want them to be
	and how we want them to be this will allow us to have
	multiple draw list classes say for drawing certain things
	ontop or behind another it will also allow us to call a
	render function anywhere in our code and have it eventually
	drawn in whatever hook we want.

	theoretically this can fail in cases such as multi threading
	because if two threads were to try to call one of these functions
	at the same time only one would get pushed back seeming it would
	one of them would get overrwritten.
	
	the way i have gone about fixing this is having a render class
	which will have global variations that are called in the specific
	hooks these render classes will have two DrawList pointers one
	for drawing above and one for below

	this fix could be improved by using atomic objects in the
	drawing functions to be 100% sure that the issue mentioned
	before can arrise

*/

enum FONTFLAGS : int
{
	FONT_CENTERED	= 1,
	FONT_RIGHT		= 2,
};

class DrawList
{
private:

	enum class Shapes
	{
		FILLED_RECT,
		RECT,
		LINE,
		TEXT,
	};

	class RenderItem
	{
	public:

		float x;
		float y;
		float w;
		float h;
		float x0;
		float y0;
		float x1;
		float y1;
		Color col;
		vgui::HFont font;
		std::wstring text;
		int flags;
		Shapes shape;
	};

private:

	std::vector<std::pair<int, RenderItem>> m_drawlist;

private:

	void draw_filled_rect(float x, float y, float w, float h, Color col);
	void draw_rect(float x, float y, float w, float h, Color col);
	void draw_line(float x0, float y0, float x1, float y1, Color col);
	void draw_text(vgui::HFont font, std::wstring text, float x, float y, int flags, Color col);

public:

	void add_filled_rect(float x, float y, float w, float h, Color col, int precedence = 0);
	void add_rect(float x, float y, float w, float h, Color col, int precedence = 0);
	void add_line(float x0, float y0, float x1, float y1, Color col, int precedence = 0);
	void add_text(vgui::HFont font, std::wstring text, float x, float y, int flags, Color col, int precedence = 0);

	friend bool drawlist_comparison(std::pair<int, DrawList::RenderItem> a, std::pair<int, DrawList::RenderItem> b);

public:

	void render();
};

class Renderer
{
private:

	DrawList m_drawlist;

public:

	vgui::HFont m_font_csgo_small;
	vgui::HFont m_font_small_fonts;
	vgui::HFont m_font_menu;

public:

	void filled_rect(float x, float y, float w, float h, Color col, int precedence = 0);
	void rect(float x, float y, float w, float h, Color col, int precedence = 0);
	void line(float x0, float y0, float x1, float y1, Color col, int precedence = 0);
	void text(vgui::HFont font, std::wstring text, float x, float y, int flags, Color col, int precedence = 0);
	void text(vgui::HFont font, std::string text, float x, float y, int flags, Color col, int precedence = 0);

public:

	void csgo_small(const wchar_t* text, float x, float y, int flags, Color col);

public:

	int init_fonts();
	void render();
};

extern std::unique_ptr<Renderer> g_render;