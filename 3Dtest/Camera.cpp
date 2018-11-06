#include "stdafx.h"
#include "Camera.h"
#include "Common.h"

Camera::Camera()
{
	vecWatchAt = new D3DXVECTOR3(0, 0, 0);
	distance = 0;
}

Camera::Camera(D3DXVECTOR3* position, D3DXVECTOR3* watchAt, D3DXVECTOR3* up)
{
	setVecNowPos(position);
	setVecWatchAt(watchAt);


	D3DXVECTOR3 vecFront = *watchAt - *position;
	distance = D3DXVec3Length(&vecFront);
	D3DXVec3Normalize(&vecFront, &vecFront);
	seteVecFront(&vecFront);

	D3DXVECTOR3 vecRight;
	D3DXVec3Cross(&vecRight, &vecFront, up);
	D3DXVec3Normalize(&vecRight, &vecRight);
	setVecRight(&vecRight);

	D3DXVec3Cross(up, &vecRight, &vecFront);
	D3DXVec3Normalize(up, up);
	setVecUp(up);
}


Camera::~Camera()
{
	safe_delete<D3DXVECTOR3>(vecWatchAt);
}

void Camera::draw(LPDIRECT3DDEVICE9 pD3DDevice)
{
	D3DXMATRIX mtxView;
	D3DXMatrixIdentity(&mtxView);

	D3DXMatrixLookAtLH(&mtxView, getVecNowPos(), vecWatchAt, getVecUp());

	//projection matirx
	D3DXMATRIX mtxProjection;
	D3DXMatrixIdentity(&mtxProjection);
	//visual angle, Screen ratio, near point, far point
	D3DXMatrixPerspectiveFovLH(&mtxProjection, D3DXToRadian(60), (float)Common::screen_width/ Common::screen_height, 0.1f, 100.0f);

	//set the view matirx to the device
	pD3DDevice->SetTransform(D3DTS_VIEW, &mtxView);
	//set the projection matirx to the device
	pD3DDevice->SetTransform(D3DTS_PROJECTION, &mtxProjection);
}

RECTF Camera::getBoundingRect(void)
{
	RECTF rect = { 0, 0, 0, 0 };
	return rect;
}

D3DXVECTOR2 Camera::getBoundingCenter(void)
{
	return {0, 0};
}

void Camera::calWatchAt(void)
{
	D3DXVECTOR3 watchAt(*getVecNowPos() + *geteVecFront() * distance);
	setVecWatchAt(&watchAt);
}

D3DXVECTOR3* Camera::getVecWatchAt(void)
{
	return vecWatchAt;
}

void Camera::setVecWatchAt(D3DXVECTOR3* vecWatchAt)
{
	safe_delete<D3DXVECTOR3>(this->vecWatchAt);
	this->vecWatchAt = new D3DXVECTOR3(*vecWatchAt);
}

float Camera::getDistance(void)
{
	return distance;
}

void Camera::setDistance(float distance)
{
	this->distance = distance;
}
