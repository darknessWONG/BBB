#pragma once
#include "Parts.h"
#include "MyMesh.h"
#include "AnimationTemplate.h"
class Animation
{
public:
	Animation(AnimationTemplate* temp, MyMesh* mesh);
	~Animation();
	/*===========================================
	virtual member
	============================================*/

	/*===========================================
	public function
	============================================*/
	bool checkEnd(void);
	void play(void);

	/*===========================================
	public geter / seter
	============================================*/
	//scale of axis x, y, z
	D3DXVECTOR3 getScalePerFream(void);
	//angle of rotation on axis x, y, z
	D3DXVECTOR3 getRotationPerFream(void);
	//transport distans
	D3DXVECTOR3 getTransportPerFream(void);
	//angle ofo revolution on axis x, y, z
	D3DXVECTOR3 getRevolutionPerFream(void);
	//this animation will cost how many fream to play
	int getNowFream(void);

private:
	//AnimationTemplate* temp;
	Parts* target;

	//scale of axis x, y, z
	D3DXVECTOR3 scalePerFream;
	//angle of rotation on axis x, y, z
	D3DXVECTOR3 rotationPerFream;
	//transport distans
	D3DXVECTOR3 transportPerFream;
	//angle ofo revolution on axis x, y, z
	D3DXVECTOR3 revolutionPerFream;
	//this animation will cost how many fream to play
	int totalFream;
	int nowFream;
};

