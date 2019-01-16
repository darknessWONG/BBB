#pragma once
#include "stdafx.h"
class AnimationTemplate
{
public:
	AnimationTemplate(int index, 
		D3DXVECTOR3 scale, 
		D3DXVECTOR3 rotation, 
		D3DXVECTOR3 transport, 
		D3DXVECTOR3 revolution, 
		int totalFream);
	~AnimationTemplate();
	/*===========================================
	virtual member
	============================================*/

	/*===========================================
	public function
	============================================*/

	/*===========================================
	public geter / seter
	============================================*/
	//the parts which this animation move
	int getIndex(void);
	//scale of axis x, y, z
	D3DXVECTOR3 getScale(void);
	//angle of rotation on axis x, y, z
	D3DXVECTOR3 getRotation(void);
	//transport distans
	D3DXVECTOR3 getTransport(void);
	//angle ofo revolution on axis x, y, z
	D3DXVECTOR3 getRevolution(void);
	//this animation will cost how many fream to play
	int getTotalFream(void);


private:
	//the parts which this animation move
	int index;

	//scale of axis x, y, z
	D3DXVECTOR3 scale;
	//angle of rotation on axis x, y, z
	D3DXVECTOR3 rotation;
	//transport distans
	D3DXVECTOR3 transport;
	//angle ofo revolution on axis x, y, z
	D3DXVECTOR3 revolution;
	//this animation will cost how many fream to play
	int totalFream;
};

