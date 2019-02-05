#include "sprite.h"
#include "stdafx.h"
#include "texture.h"
#include "Common.h"
#include <math.h>

#define SCREEN_WIDTH	(Common::screen_width)
#define SCREEN_HEIGHT	(Common::screen_height)


// FVFì‚é
typedef struct Vertex2D_tag {
	D3DXVECTOR4 position;
	D3DCOLOR color;
	D3DXVECTOR2 texcoord;
} Vertex2D;

#define FVF_VERTEX2D    (D3DFVF_XYZRHW)

#define M_PI       (3.14159265358979323846)

float rotatex(float, float, float);
float rotatey(float, float, float);

static D3DCOLOR g_Color = 0xffffffff;

void render_sprite(int texture_index, Vertex2D *v);

void Sprite_Draw(int texture_index, float dx, float dy) {

    float w = (float)Texture_GetWidth(texture_index);
    float h = (float)Texture_GetHeight(texture_index);

    Vertex2D v[] = {
		{ 
			D3DXVECTOR4(dx , dy, 0.0f, 1.0f), 
			g_Color,
			D3DXVECTOR2(0.0f, 0.0f)
		},
		
		{ 
			D3DXVECTOR4(dx + w, dy, 0.0f, 1.0f), 
			g_Color,
			D3DXVECTOR2(1.0f, 0.0f)
		},

		{ 
			D3DXVECTOR4(dx, dy + h, 0.0f, 1.0f), 
			g_Color,
			D3DXVECTOR2(0.0f, 1.0f)
		},

		{ 
			D3DXVECTOR4(dx + w, dy + h, 0.0f, 1.0f), 
			g_Color,
			D3DXVECTOR2(1.0f, 1.0f)
		},
	};

	render_sprite(texture_index, v);

}


void Sprite_Draw(int texture_index, float dx, float dy, int tx, int ty, int tw, int th) {
    
    float w = (float)Texture_GetWidth(texture_index);
    float h = (float)Texture_GetHeight(texture_index);

    float u0 = (float)tx / w;
    float v0 = (float)ty / h;
    float u1 = (float)(tx + tw) / w;
    float v1 = (float)(ty + th) / h;

    Vertex2D v[] = {
		{ 
			D3DXVECTOR4(dx , dy, 0.0f, 1.0f),
			g_Color,
			D3DXVECTOR2(u0, v0)
		},
		
		{ 
			D3DXVECTOR4(dx + tw, dy, 0.0f, 1.0f),
			g_Color,
			D3DXVECTOR2(u1, v0)
		},

		{ 
			D3DXVECTOR4(dx, dy + th, 0.0f, 1.0f),
			g_Color,
			D3DXVECTOR2(u0, v1)
		},

		{ 
			D3DXVECTOR4(dx + tw, dy + th, 0.0f, 1.0f),
			g_Color,
			D3DXVECTOR2(u1, v1)
		},
	};

	render_sprite(texture_index, v);

}


// rotate
void Sprite_Draw(int texture_index, float dx, float dy, int tx, int ty, int tw, int th,float cx, float cy, float sx, float sy ,int radian) {

    float w = (float)Texture_GetWidth(texture_index);
    float h = (float)Texture_GetHeight(texture_index);

    float u0 = (float)tx / w;
    float v0 = (float)ty / h;
    float u1 = (float)(tx + tw) / w;
    float v1 = (float)(ty + th) / h;

    float px[4], py[4];

    px[0] = cx + rotatex(dx - tw/2 ,dy - th/2,radian);
    px[1] = cx + rotatex(dx + tw/2 ,dy - th/2,radian);
    px[2] = cx + rotatex(dx - tw/2 ,dy + th/2,radian);
    px[3] = cx + rotatex(dx + tw/2 ,dy + th/2,radian);

    py[0] = cy + rotatey(dx - tw/2 ,dy - th/2,radian);
    py[1] = cy + rotatey(dx + tw/2 ,dy - th/2,radian);
    py[2] = cy + rotatey(dx - tw/2 ,dy + th/2,radian);
    py[3] = cy + rotatey(dx + tw/2 ,dy + th/2,radian);

    Vertex2D v[] = {
		{ 
			D3DXVECTOR4(px[0], py[0], 0.0f, 1.0f),
			g_Color,
			D3DXVECTOR2(u0, v0)
		},
		
		{ 
			D3DXVECTOR4( px[1], py[1], 0.0f, 1.0f),
			g_Color,
			D3DXVECTOR2(u1, v0)
		},

		{ 
			D3DXVECTOR4( px[2], py[2], 0.0f, 1.0f),
			g_Color,
			D3DXVECTOR2(u0, v1)
		},

		{ 
			D3DXVECTOR4( px[3], py[3], 0.0f, 1.0f),
			g_Color,
			D3DXVECTOR2(u1, v1)
		},
	};

	render_sprite(texture_index, v);

}

// normal background
void Sprite_Draw_Background(int texture_index) {

	Vertex2D v[] = {
		{
			D3DXVECTOR4(0.0f , 0.0f, 0.0f, 1.0f),
			g_Color,
			D3DXVECTOR2(0.0f, 0.0f)
		},

		{
			D3DXVECTOR4(0.0f + SCREEN_WIDTH, 0.0f, 0.0f, 1.0f),
			g_Color,
			D3DXVECTOR2(1.0f, 0.0f)
		},

		{
			D3DXVECTOR4(0.0f, 0.0f + SCREEN_HEIGHT, 0.0f, 1.0f),
			g_Color,
			D3DXVECTOR2(0.0f, 1.0f)
		},

		{
			D3DXVECTOR4(0.0f + SCREEN_WIDTH, 0.0f + SCREEN_HEIGHT, 0.0f, 1.0f),
			g_Color,
			D3DXVECTOR2(1.0f, 1.0f)
		},
	};

	render_sprite(texture_index, v);

}


// draw fullscreen with move
void Sprite_Draw_Background(int texture_index, float moveX, float moveY) {

    Vertex2D v[] = {
		{ 
			D3DXVECTOR4(0.0f , 0.0f, 0.0f, 1.0f),
			g_Color,
			D3DXVECTOR2(0.0f + moveX, 0.0f + moveY)
		},
		
		{ 
			D3DXVECTOR4(0.0f + SCREEN_WIDTH, 0.0f, 0.0f, 1.0f),
			g_Color,
			D3DXVECTOR2(1.0f + moveX, 0.0f + moveY)
		},

		{ 
			D3DXVECTOR4(0.0f, 0.0f + SCREEN_HEIGHT, 0.0f, 1.0f),
			g_Color,
			D3DXVECTOR2(0.0f + moveX, 1.0f + moveY)
		},

		{ 
			D3DXVECTOR4(0.0f + SCREEN_WIDTH, 0.0f + SCREEN_HEIGHT, 0.0f, 1.0f),
			g_Color,
			D3DXVECTOR2(1.0f + moveX, 1.0f + moveY)
		},
	};

	render_sprite(texture_index, v);

}

void Sprite_Draw_Background(int texture_index, int tx, int ty, int tw, int th)
{
	float w = (float)Texture_GetWidth(texture_index);
	float h = (float)Texture_GetHeight(texture_index);

	float u0 = (float)tx / w;
	float v0 = (float)ty / h;
	float u1 = (float)(tx + tw) / w;
	float v1 = (float)(ty + th) / h;

	Vertex2D v[] = {
		{
			D3DXVECTOR4(0.0f , 0.0f, 0.0f, 1.0f),
			g_Color,
			D3DXVECTOR2(u0, v0)
		},

		{
			D3DXVECTOR4(SCREEN_WIDTH, 0.0f, 0.0f, 1.0f),
			g_Color,
			D3DXVECTOR2(u1, v0)
		},

		{
			D3DXVECTOR4(0.0f , SCREEN_HEIGHT, 0.0f, 1.0f),
			g_Color,
			D3DXVECTOR2(u0, v1)
		},

		{
			D3DXVECTOR4(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 1.0f),
			g_Color,
			D3DXVECTOR2(u1, v1)
		},
	};

	render_sprite(texture_index, v);
}

// without color
void Sprite_Draw_Size(int texture_index, float dx, float dy, int sx, int sy) {

	D3DXCOLOR color = 0xffffffff;

	Vertex2D v[] = {
		{
			D3DXVECTOR4(dx - sx / 2 , dy - sy / 2, 0.0f, 1.0f),
			color,
			D3DXVECTOR2(0.0f, 0.0f)
		},

		{
			D3DXVECTOR4(dx + sx / 2 , dy - sy / 2, 0.0f, 1.0f),
			color,
			D3DXVECTOR2(1.0f, 0.0f)
		},

		{
			D3DXVECTOR4(dx - sx / 2 , dy + sy / 2, 0.0f, 1.0f),
			color,
			D3DXVECTOR2(0.0f, 1.0f)
		},

		{
			D3DXVECTOR4(dx + sx / 2 , dy + sy / 2, 0.0f, 1.0f),
			color,
			D3DXVECTOR2(1.0f, 1.0f)
		},
	};

	render_sprite(texture_index, v);
}

// draw with set size and color
void Sprite_Draw_Size(int texture_index, float dx, float dy, int sx, int sy, D3DXCOLOR color) {

    Vertex2D v[] = {
		{ 
			D3DXVECTOR4(dx - sx/2 , dy - sy/2, 0.0f, 1.0f),
			color,
			D3DXVECTOR2(0.0f, 0.0f)
		},
		
		{ 
			D3DXVECTOR4(dx + sx/2 , dy - sy/2, 0.0f, 1.0f),
			color,
			D3DXVECTOR2(1.0f, 0.0f)
		},

		{ 
			D3DXVECTOR4(dx - sx/2 , dy + sy/2, 0.0f, 1.0f),
			color,
			D3DXVECTOR2(0.0f, 1.0f)
		},

		{ 
			D3DXVECTOR4(dx + sx/2 , dy + sy/2, 0.0f, 1.0f),
			color,
			D3DXVECTOR2(1.0f, 1.0f)
		},
	};

	render_sprite(texture_index, v);

}

// draw with set size and cut uv
void Sprite_Draw_Size(int texture_index, float dx, float dy, int sx, int sy, int tx, int ty, int tw, int th) {

    float w = (float)Texture_GetWidth(texture_index);
    float h = (float)Texture_GetHeight(texture_index);

    float u0 = (float)tx / w;
    float v0 = (float)ty / h;
    float u1 = (float)(tx + tw) / w;
    float v1 = (float)(ty + th) / h;

    Vertex2D v[] = {
		{ 
			D3DXVECTOR4(dx - sx/2 , dy - sy/2, 0.0f, 1.0f),
			g_Color,
			D3DXVECTOR2(u0, v0)
		},
		
		{ 
			D3DXVECTOR4(dx + sx/2 , dy - sy/2, 0.0f, 1.0f),
			g_Color,
			D3DXVECTOR2(u1, v0)
		},

		{ 
			D3DXVECTOR4(dx - sx/2 , dy + sy/2, 0.0f, 1.0f),
			g_Color,
			D3DXVECTOR2(u0, v1)
		},

		{ 
			D3DXVECTOR4(dx + sx/2 , dy + sy/2, 0.0f, 1.0f),
			g_Color,
			D3DXVECTOR2(u1, v1)
		},
	};

	render_sprite(texture_index, v);

}

// draw with set size and cut uv and color
void Sprite_Draw_Size(int texture_index, float dx, float dy, int sx, int sy, int tx, int ty, int tw, int th, D3DXCOLOR color) {

	float w = (float)Texture_GetWidth(texture_index);
	float h = (float)Texture_GetHeight(texture_index);

	float u0 = (float)tx / w;
	float v0 = (float)ty / h;
	float u1 = (float)(tx + tw) / w;
	float v1 = (float)(ty + th) / h;

	Vertex2D v[] = {
		{
			D3DXVECTOR4(dx - sx / 2 , dy - sy / 2, 0.0f, 1.0f),
			color,
			D3DXVECTOR2(u0, v0)
		},

		{
			D3DXVECTOR4(dx + sx / 2 , dy - sy / 2, 0.0f, 1.0f),
			color,
			D3DXVECTOR2(u1, v0)
		},

		{
			D3DXVECTOR4(dx - sx / 2 , dy + sy / 2, 0.0f, 1.0f),
			color,
			D3DXVECTOR2(u0, v1)
		},

		{
			D3DXVECTOR4(dx + sx / 2 , dy + sy / 2, 0.0f, 1.0f),
			color,
			D3DXVECTOR2(u1, v1)
		},
	};

	render_sprite(texture_index, v);

}

// set sprite transparent
void Sprite_SetColor(D3DCOLOR color) {
    g_Color = color;
}

void render_sprite(int texture_index, Vertex2D *v) {

	LPDIRECT3DDEVICE9 pDevice = Common::g_pD3DDevice;
	
	IDirect3DStateBlock9* pStateBlock = NULL;
	pDevice->CreateStateBlock(D3DSBT_ALL, &pStateBlock);

	pDevice->SetTexture(0, Texture_GetTexture(texture_index));
	pDevice->SetFVF(FVF_VERTEX2D | D3DFVF_DIFFUSE | D3DFVF_TEX1);

	//pDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DSAMP_BORDERCOLOR);

	//pDevice->SetSamplerState(0, D3DSAMP_BORDERCOLOR, D3DCOLOR_RGBA(0,0,0,255));

	// —LŒø
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	// ”wŒi
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	// ¡‚©‚ç•`‚­ƒ|ƒŠƒSƒ“SRC‚ÌƒuƒŒƒ“ƒhÝ’è
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	
	// Blender Test
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 10);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	// AA
	pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	pDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);

	pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
	pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);

	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(v[0]));

	pStateBlock->Apply();
	pStateBlock->Release();
}

float rotatex(float x, float y, float rad){
	return ((x) * cos(M_PI * rad/180.0f) - (y) * sin(M_PI * rad/180.0f));
}

float rotatey(float x, float y, float rad){
	return ((x) * sin(M_PI * rad/180.0f) + (y) * cos(M_PI * rad/180.0f));
}
