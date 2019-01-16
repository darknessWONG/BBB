#include "stdafx.h"
#include "Animation.h"


Animation::Animation(AnimationTemplate* temp, MyMesh* mesh)
{
	target = mesh->getPartsByIndex(temp->getIndex());

	scalePerFream = temp->getScale() / temp->getTotalFream();
	rotationPerFream = temp->getRotation() / temp->getTotalFream();
	transportPerFream = temp->getTransport() / temp->getTotalFream();
	revolutionPerFream = temp->getRevolution() / temp->getTotalFream();
	totalFream = temp->getTotalFream();

	nowFream = 0;
}


Animation::~Animation()
{
}

bool Animation::checkEnd(void)
{
	return nowFream >= totalFream;
}

void Animation::play(void)
{
	if (nowFream < totalFream)
	{
		target->setOffsetS(target->getOffsetS() - scalePerFream);
		target->setOffsetR(target->getOffsetR() - rotationPerFream);
		target->setOffsetT(target->getOffsetT() - transportPerFream);
		target->setRotation(target->getRotation() - revolutionPerFream);

		nowFream++;
	}
}

D3DXVECTOR3 Animation::getScalePerFream(void)
{
	return scalePerFream;
}

D3DXVECTOR3 Animation::getRotationPerFream(void)
{
	return rotationPerFream;
}

D3DXVECTOR3 Animation::getTransportPerFream(void)
{
	return transportPerFream;
}

D3DXVECTOR3 Animation::getRevolutionPerFream(void)
{
	return revolutionPerFream;
}

int Animation::getNowFream(void)
{
	return nowFream;
}
