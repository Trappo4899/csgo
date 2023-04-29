#pragma once

#undef CreateFont

namespace vgui
{
	typedef unsigned long HFont;

	enum FontFeature_t
	{
		FONT_FEATURE_ANTIALIASED_FONTS = 1,
		FONT_FEATURE_DROPSHADOW_FONTS = 2,
		FONT_FEATURE_OUTLINE_FONTS = 6,
	};

	enum FontFlags_t
	{
		FONTFLAG_NONE,
		FONTFLAG_ITALIC = 0x001,
		FONTFLAG_UNDERLINE = 0x002,
		FONTFLAG_STRIKEOUT = 0x004,
		FONTFLAG_SYMBOL = 0x008,
		FONTFLAG_ANTIALIAS = 0x010,
		FONTFLAG_GAUSSIANBLUR = 0x020,
		FONTFLAG_ROTARY = 0x040,
		FONTFLAG_DROPSHADOW = 0x080,
		FONTFLAG_ADDITIVE = 0x100,
		FONTFLAG_OUTLINE = 0x200,
		FONTFLAG_CUSTOM = 0x400,
		FONTFLAG_BITMAP = 0x800,
	};

	enum FontDrawType_t
	{
		FONT_DRAW_DEFAULT = 0,
		FONT_DRAW_NONADDITIVE,
		FONT_DRAW_ADDITIVE,
		FONT_DRAW_TYPE_COUNT = 2,
	};

	enum VGuiPanel_t
	{
		PANEL_ROOT = 0,
		PANEL_GAMEUIDLL,  // the console, game menu
		PANEL_CLIENTDLL,
		PANEL_TOOLS,
		PANEL_INGAMESCREENS,
		PANEL_GAMEDLL,
		PANEL_CLIENTDLL_TOOLS,
		PANEL_GAMEUIBACKGROUND, // the console background, shows under all other stuff in 3d engine view
		PANEL_TRANSITIONEFFECT,
		PANEL_STEAMOVERLAY,
	};

	// In-game panels are cropped to the current engine viewport size
	enum PaintMode_t
	{
		PAINT_UIPANELS = (1 << 0),
		PAINT_INGAMEPANELS = (1 << 1),
	};

	class IPanel
	{
	private:

		enum
		{
			GETNAME = 36,
		};

	public:

		enum
		{
			PAINTTRAVERSE = 41, // - handles all pannel drawing for the game
		};

	public:

		const char* GetName(int vguiPanel)
		{
			return VMT::call<GETNAME, const char*, int>(this, vguiPanel);
		}
	};

	class IVEngineVgui
	{
	private:

		enum
		{

		};

	public:

		enum
		{
			PAINT = 14,
		};

	public:


	};

	class ISurface
	{
	private:
		
		enum
		{
			DRAWSETCOLOR1								= 14,
			DRAWSETCOLOR2								= 15,
			DRAWFILLEDRECT								= 16,
			DRAWOUTLINEDRECT							= 18,
			DRAWLINE									= 19,
			DRAWQUADARRAY								= 20,
			DRAWSETAPPARENTDEPTH						= 21,
			DRAWCLEARAPPARENTDEPTH						= 22,
			DRAWSETTEXTFONT								= 23,
			DRAWSETTEXTCOLOR1							= 24,
			DRAWSETTEXTCOLOR2							= 25,
			DRAWSETTEXTPOS								= 26,
			DRAWGETTEXTPOS								= 27,
			DRAWPRINTTEXT								= 28,
			DRAWUNICODECHAR								= 29,
			DRAWFLUSHTEXT								= 30,
			DRAWSETTEXTURE								= 38,
			CREATEFONT									= 71,
			SETFONTGLYPHSET								= 72,
			ADDCUSTOMFONTFILE							= 73,
			GETFONTTALL									= 74,
			GETCHARABCWIDE								= 77,
			DRAWGETUNICODECHARRENDERINFO				= 111,
			DRAWRENDERCHARFROMINFO						= 112,
			DRAWSETALPHAMULTIPLIER						= 113,
			DRAWGETALPHAMULTIPLIER						= 114,
			DRAWSETTEXTSCALE							= 125,
			ADDBITMAPFONTFILE							= 127,
			DRAWUNICODESTRING							= 132,
			PRECACHEFONTCHARACTER						= 133,
			BEGIN3DPAINT								= 157, 
		};

	public:

		enum
		{
			PAINTTRAVERSEEX = 119,		// - only draws in game
			ONSCREENSIZECHANGED = 116,
		};

	public:

		void DrawSetColor(Color color)
		{
			VMT::call<DRAWSETCOLOR1, void, Color>(this, color);
		}

		void DrawSetColor(int r, int g, int b, int a)
		{
			VMT::call<DRAWSETCOLOR2, void, int, int, int, int>(this, r, g, b, a);
		}

		void DrawOutlineRect(int x0, int y0, int x1, int y1)
		{
			VMT::call<DRAWOUTLINEDRECT, void, int, int, int, int>(this, x0, y0, x1, y1);
		}

		void DrawFilledRect(int x0, int y0, int x1, int y1)
		{
			VMT::call<DRAWFILLEDRECT, void, int, int, int, int>(this, x0, y0, x1, y1);
		}

		void DrawLine(int x0, int y0, int x1, int y1)
		{
			VMT::call<DRAWLINE, void, int, int, int, int>(this, x0, y0, x1, y1);
		}

		void DrawSetApparentDepth(float flDepth)
		{
			VMT::call<DRAWSETAPPARENTDEPTH, void, float>(this, flDepth);
		}

		void ClearApparentDepth()
		{
			VMT::call<DRAWCLEARAPPARENTDEPTH, void>(this);
		}

		void DrawSetTextFont(HFont hFont)
		{
			VMT::call<DRAWSETTEXTFONT, void, HFont>(this, hFont);
		}

		void DrawPrintText(const wchar_t* str, int len, FontDrawType_t drawType = FONT_DRAW_DEFAULT)
		{
			VMT::call<DRAWPRINTTEXT, void, const wchar_t*, int, FontDrawType_t>(this, str, len, drawType);
		}

		void DrawUnicodeString(const wchar_t* str, FontDrawType_t drawType = FONT_DRAW_DEFAULT)
		{
			VMT::call<DRAWUNICODESTRING, void, const wchar_t*, FontDrawType_t>(this, str, drawType);
		}

		void DrawSetTextColor(Color color)
		{
			VMT::call<DRAWSETTEXTCOLOR1, void, Color>(this, color);
		}

		void DrawSetTextColor(int r, int g, int b, int a)
		{
			VMT::call<DRAWSETTEXTCOLOR2, void, int, int, int, int>(this, r, g, b, a);
		}

		void DrawSetTextPos(int x, int y)
		{
			VMT::call<DRAWSETTEXTPOS, void, int, int>(this, x, y);
		}

		void DrawGetTextPos(int& x, int& y)
		{
			VMT::call<DRAWGETTEXTPOS, void, int&, int&>(this, std::ref(x), std::ref(y));
		}

		void DrawUnicodeChar(wchar_t wch, FontDrawType_t drawType = FONT_DRAW_DEFAULT)
		{
			VMT::call<DRAWUNICODECHAR, void, wchar_t, FontDrawType_t>(this, wch, drawType);
		}

		void DrawFlushText()
		{
			VMT::call<DRAWFLUSHTEXT, void>(this);
		}

		void DrawSetTexture(int id)
		{
			VMT::call<DRAWSETTEXTURE, void, int>(this, id);
		}

		HFont CreateFont()
		{
			return VMT::call<CREATEFONT, unsigned long>(this);
		}

		bool SetFontGlyphSet(HFont font, const char* windowsFontName, int tall, int weight, int blur, int scanlines, int flags, int nRangeMin = 0, int nRangeMax = 0)
		{
			return VMT::call<SETFONTGLYPHSET, bool, HFont, const char*, int, int, int, int, int, int, int>(this, font, windowsFontName, tall, weight, blur, scanlines, flags, nRangeMin, nRangeMax);
		}

		bool AddCustomFontFile(const char* fileName)
		{
			return VMT::call<ADDCUSTOMFONTFILE, bool, const char*>(this, fileName);
		}

		int GetFontTall(HFont font)
		{
			return VMT::call<GETFONTTALL, int, HFont>(this, font);
		}

		void GetCharABCwide(HFont font, int ch, int& a, int& b, int& c)
		{
			VMT::call<GETCHARABCWIDE, void, HFont, int, int&, int&, int&>(this, font, ch, a, b, c);
		}

		void DrawSetAlphaMultiplier(float alpha)
		{
			VMT::call<DRAWSETALPHAMULTIPLIER, void, float>(this, alpha);
		}

		float DrawGetAlphaMultiplier()
		{
			return VMT::call<DRAWGETALPHAMULTIPLIER, float>(this);
		}

		void DrawSetTextScale(float sx, float sy)
		{
			VMT::call<DRAWSETTEXTSCALE, float, float>(this, sx, sy);
		}

		void DrawOutlinedCircle(int x, int y, int radius, int segments)
		{
			//VMT::call<DRAWOUTLINEDCIRCLE, void, int, int, int, int>(this, x, y, radius, segments);
		}

	public:

		int GetTextWidth(vgui::HFont font, const wchar_t* text)
		{
			int len = wcslen(text);

			int x = 0;

			this->DrawSetTextFont(font);

			for (int i = 0; i < len; i++)
			{
				int a, b, c;
				this->GetCharABCwide(font, text[i], a, b, c);
				// Ignore a
				if (i != 0)
					x += a;
				x += b;
				if (i != len - 1)
					x += c;
			}

			return x;
		}

		Vector2 GetTextSize(vgui::HFont font, const char* text)
		{
			wchar_t wbuffer[128] = { };

			if (!MultiByteToWideChar(CP_UTF8, 0, text, -1, wbuffer, 128))
			{
				return { };
			}

			return this->GetTextSize(font, wbuffer);
		}

		Vector2 GetTextSize(vgui::HFont font, const wchar_t* text)
		{
			return {
				float(this->GetTextWidth(font, text)),
				float(this->GetFontTall(font)),
			};
		}
	};
}