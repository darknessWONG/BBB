#include "stdafx.h"
#include "UI.h"
#include "font.h"


UI::UI(D3DXVECTOR2 pos, float width, float height, int tex)
{
	this->position = pos;
	this->width = width;
	this->height = height;
	texture = tex;
	child = NULL;
	next = NULL;
	identity = UIIdentity::UIIdentityMAX;
	index = -1;
	isDisplay = true;
}


UI::~UI()
{
}

D3DXVECTOR2 UI::getPosition(void)
{
	return position;
}

void UI::setPosition(D3DXVECTOR2 position)
{
	this->position = position;
}

float UI::getWidth(void)
{
	return width;
}

void UI::setWidth(float width)
{
	this->width = width;
}

float UI::getHeight(void)
{
	return height;
}

void UI::setHeight(float height)
{
	this->height = height;
}

int UI::getTexture(void)
{
	return texture;
}

void UI::setTexture(int index)
{
	this->texture = index;
}

string UI::getStr(void)
{
	return str;
}

void UI::setStr(string str)
{
	this->str = str;
}

UIIdentity UI::getIdentity(void)
{
	return identity;
}

void UI::setIdentity(UIIdentity identity)
{
	this->identity = identity;
}

int UI::getIndex(void)
{
	return index;
}

void UI::setIndex(int index)
{
	this->index = index;
}

void UI::setIsDisplay(bool isDisplay)
{
	this->isDisplay = isDisplay;
}

void UI::calPoints(D3DXVECTOR2* basePoint)
{
	points[0] = position + *basePoint;
	points[1] = { points[0].x + width, points[0].y };
	points[2] = { points[0].x, points[0].y + height };
	points[3] = { points[0].x + width, points[0].y + height };
}

void UI::calTexPoint(void)
{
	uvPos[0] = { 0, 0 };
	uvPos[1] = { 1, 0 };
	uvPos[2] = { 0, 1 };
	uvPos[3] = { 1, 1 };
}

void UI::draw(LPDIRECT3DDEVICE9 g_pD3DDevice, D3DXVECTOR2 *basePoint)
{
	if (isDisplay)
	{
		calPoints(basePoint);
		calTexPoint();

		Vertex2D *f = new Vertex2D[4];
		for (int i = 0; i < 4; i++)
		{
			f[i].pos = { points[i].x, points[i].y, 0, 1 };
			f[i].pos.x += 0.5;
			f[i].pos.y += 0.5;
			f[i].color = D3DCOLOR_RGBA(255, 255, 255, 255);
			f[i].uv = uvPos[i];
		}
		g_pD3DDevice->SetFVF(FVF_VERTEX2D);
		g_pD3DDevice->SetTexture(0, TextureHandler2D::GetTexture(texture).tex_p);

		g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, f, sizeof(Vertex2D));

		char *tmpStr = new char[str.length() + 1];
		strcpy_s(tmpStr, str.length() + 1, str.c_str());
		Font_Draw(f[0].pos.x, f[0].pos.y, tmpStr);
		delete[] tmpStr;
	}
	if (next != NULL)
	{
		next->setIsDisplay(isDisplay);
		next->draw(g_pD3DDevice, basePoint);
	}

	if (child != NULL)
	{
		child->setIsDisplay(isDisplay);
		child->draw(g_pD3DDevice, points);
	}
}

void UI::addChild(UI * ui)
{
	if (child == NULL)
	{
		child = ui;
	}
	else
	{
		UI* tmp = child;
		while (tmp->next != NULL)
		{
			tmp = tmp->next;
		}
		tmp->next = ui;
	}
}

void UI::addNext(UI * ui)
{
	if (next == NULL)
	{
		next = ui;
	}
	else
	{
		UI* tmp = next;
		while (tmp->next != NULL)
		{
			tmp = tmp->next;
		}
		tmp->next = ui;
	}
}

void UI::releaseChain(void)
{
	if (child != NULL)
	{
		child->releaseChain();
	}
	if (next != NULL)
	{
		next->releaseChain();
	}
	releaseNext();
	releaseChild();
}

void UI::releaseChild(void)
{
	if (child != NULL)
	{
		child = NULL;
	}
}

void UI::releaseNext(void)
{
	if (next != NULL)
	{
		next = NULL;
	}
}
