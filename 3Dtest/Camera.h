#pragma once
#include "GameObject.h"
#include <d3dx9.h>

class Camera
	: public GameObject
{
public:
	Camera();
	Camera(D3DXVECTOR3* position, D3DXVECTOR3* watchAt, D3DXVECTOR3* up);
	~Camera();
	/*===========================================
	virtual member
	============================================*/
	virtual void draw(void);

	/*===========================================
	public function
	============================================*/
	void calWatchAt(void);

	/*===========================================
	public geter / seter
	============================================*/
	D3DXVECTOR3* getVecWatchAt(void);
	void setVecWatchAt(D3DXVECTOR3* vecWatchAt);
	float getDistance(void);
	void setDistance(float distance);
private:
	D3DXVECTOR3* vecWatchAt;
	float distance;   //distance form camera to At(bigger than 1)
};

