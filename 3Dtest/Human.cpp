#include "stdafx.h"
#include "Human.h"


Human::Human()
{
}


Human::~Human()
{
}

RECTF Human::getBoundingRect(void)
{
	D3DXVECTOR2 lt = { 0, 0 };
	D3DXVECTOR2 rb = { 0, 0 };
	findBoundingRect(parts, lt, rb);
	RECTF rect = { lt.x, rb.x, lt.y, rb.y };
	return rect;
}

D3DXVECTOR2 Human::getBoundingCenter(void)
{
	D3DXVECTOR3 pos = *getVecNowPos();
	return D3DXVECTOR2(pos.x, pos.z);
}

void Human::findBoundingRect(Parts * part, D3DXVECTOR2 & lt, D3DXVECTOR2 & rb)
{
	D3DXVECTOR3 partScale = part->getBaseOffsetS();
	D3DXVECTOR3 partTransport = part->getBaseOffsetT();

	if (partTransport.x - partScale.x / 2 < lt.x)
	{
		lt.x = partTransport.x - partScale.x / 2;
	}
	if (partTransport.x + partScale.x / 2 > rb.x)
	{
		rb.x = partTransport.x + partScale.x / 2;
	}

	if (partTransport.z - partScale.z / 2 > lt.y)
	{
		lt.y = partTransport.z - partScale.z / 2;
	}
	if (partTransport.z - partScale.z / 2 < rb.y)
	{
		rb.y = partTransport.z - partScale.z / 2;
	}

	if (part->getNext() != NULL)
	{
		findBoundingRect(part->getNext(), lt, rb);
	}
	if (part->getChild() != NULL)
	{
		findBoundingRect(part->getChild(), lt, rb);
	}
}
