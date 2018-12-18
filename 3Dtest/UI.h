#pragma once
#include <d3dx9.h>
#include "TextureHandler2D.h"
class UI
{
public:
	UI(D3DXVECTOR2 pos, float width, float height, int tex);
	~UI();

	void draw(LPDIRECT3DDEVICE9 g_pD3DDevice, D3DXVECTOR2 *basePoint);
	void addChild(UI* ui);
	void addNext(UI* ui);
	void releaseChain(void);

	D3DXVECTOR2 getPosition(void);
	void setPosition(D3DXVECTOR2 position);
	float getWidth(void);
	void setWidth(float width);
	float getHeight(void);
	void setHeight(float height);
	int getTexture(void);
	void setTexture(int index);
	string getStr(void);
	void setStr(string str);
	UIIdentity getIdentity(void);
	void setIdentity(UIIdentity identity);
	int getIndex(void);
	void setIndex(int index);



private:
	void calPoints(D3DXVECTOR2* basePoint);
	void calTexPoint(void);

	void releaseChild(void);
	void releaseNext(void);

	D3DXVECTOR2 position;
	D3DXVECTOR2 points[4];
	D3DXVECTOR2 uvPos[4];
	float width;
	float height;
	int texture;
	string str;

	UIIdentity identity;
	//skill index of target index when identity is 	UIIdentityTarget or UIIdentitySkill
	int index;

	UI* child;
	UI* next;
};

