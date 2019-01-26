#include "font.h"
#include "stdafx.h"
#include "Common.h"

#define MAX_FONT (256)

static LPD3DXFONT g_pD3DXFont = NULL;
static int font_size = 18;
static D3DXCOLOR color = D3DCOLOR_RGBA(0, 255, 0, 255);
static char buf[MAX_FONT];

void Font_Initialize(void)
{
	D3DXCreateFont(Common::g_pD3DDevice, font_size, 0, 0, 0, FALSE, SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &g_pD3DXFont);
}

void Font_Finalize(void)
{
	if (g_pD3DXFont) {
		g_pD3DXFont->Release();
		g_pD3DXFont = NULL;
	}
}

int Font_GetSize(void)
{
	return font_size;
}

void Font_SetSize(int size)
{
	if (font_size != size) {
		font_size = size;
		if (g_pD3DXFont) {
			g_pD3DXFont->Release();
			g_pD3DXFont = NULL;
		}
		D3DXCreateFont(Common::g_pD3DDevice, font_size, 0, 0, 0, FALSE, SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &g_pD3DXFont);
	}
}

void Font_SetColor(int r, int g, int b, int a)
{
	color = D3DCOLOR_RGBA((unsigned char)r,(unsigned char)g,(unsigned char)b,(unsigned char)a);
}

void Font_Draw(float x, float y, char * text)
{
#ifdef _DEBUG
	RECT rect = { (LONG)x, (LONG)y, (LONG)Common::screen_width, (LONG)Common::screen_height };
	g_pD3DXFont->DrawText(NULL, text, -1, &rect, DT_LEFT, color);
#endif // _DEBUG
}

void Font_Draw(float x, float y, float width, float height, char * text)
{
	RECT rect = { (LONG)x, (LONG)y, (LONG)width, (LONG)height };
	g_pD3DXFont->DrawText(NULL, text, -1, &rect, DT_LEFT, color);
}
