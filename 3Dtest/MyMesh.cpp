#include "stdafx.h"
#include "MyMesh.h"


MyMesh::MyMesh()
{
	parts = NULL;
}


MyMesh::~MyMesh()
{
}

void MyMesh::dataUpdate(void)
{
	parts->dataUpdate();
	GameObject::dataUpdate();
}

void MyMesh::draw(LPDIRECT3DDEVICE9 pD3DDevice)
{
	if (getIsDisplay())
	{
		parts->draw(pD3DDevice, *getMtxWorld());
	}
}

RECTF MyMesh::getBoundingRect(void)
{
	D3DXVECTOR2 lt = { 0, 0 };
	D3DXVECTOR2 rb = { 0, 0 };
	findBoundingRect(parts, lt, rb);
	RECTF rect = { lt.x, rb.x, lt.y, rb.y };
	return rect;
}

D3DXVECTOR2 MyMesh::getBoundingCenter(void)
{
	D3DXVECTOR3 pos = *getVecNowPos();
	return D3DXVECTOR2(pos.x, pos.z);
}

void MyMesh::setBoundingCenter(D3DXVECTOR2 center)
{
	D3DXVECTOR3 pos = *getVecNowPos();
	pos = { center.x, pos.y, center.y };
	setVecNowPos(&pos);
}

Parts * MyMesh::getPartsByIndex(int index)
{
	if (parts != NULL)
	{
		index++;
		vector<bool> list;
		while (index != 1)
		{
			int flag = index % 2;
			if (flag == 1)
			{
				list.push_back(true);
			}
			else
			{
				list.push_back(false);
			}
			index /= 2;
		}

		Parts* tmp = parts;
		while (list.size() > 0)
		{
			bool result = list[list.size() - 1];
			if (result)
			{
				if (tmp->getNext() != NULL)
				{
					tmp = tmp->getNext();
				}
				else
				{
					return NULL;
				}
			}
			else
			{
				if (tmp->getChild() != NULL)
				{
					tmp = tmp->getChild();
				}
				else
				{
					return NULL;
				}
			}

			list.pop_back();
		}
		return tmp;
	}
	return NULL;
}

BOOL MyMesh::partsMove(int index, D3DXVECTOR3 * scale, D3DXVECTOR3 * rotation, D3DXVECTOR3 * transport, D3DXVECTOR3 * revolution)
{
	Parts* nowPart = getPartsByIndex(index);
	if (nowPart == NULL)
	{
		return 0;
	}
	if (scale != NULL)
	{
		nowPart->setOffsetS(*scale);
	}
	if (rotation != NULL)
	{
		nowPart->setOffsetR(*rotation);
	}
	if (transport != NULL)
	{
		nowPart->setOffsetT(*transport);
	}
	if (revolution != NULL)
	{
		nowPart->setRotation(*revolution);
	}
	return TRUE;
}

string MyMesh::getModelClass(void)
{
	return modelClass;
}

void MyMesh::setModelClass(string modelClass)
{
	this->modelClass = modelClass;
}

Parts * MyMesh::getParts(void)
{
	return parts;
}

void MyMesh::setParts(Parts * part)
{
	this->parts = part;
}

void MyMesh::findBoundingRect(Parts * part, D3DXVECTOR2 & lt, D3DXVECTOR2 & rb)
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
