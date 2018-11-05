#include "stdafx.h"
#include "MapManage.h"


MapManage::MapManage()
{
}


MapManage::~MapManage()
{
}

void MapManage::addGameObject(GameObject * gameObject)
{
	gameObjects.push_back(gameObject);
}

void MapManage::cleanGameObject(void)
{
	gameObjects.clear();
}

void MapManage::updateGameObejcts(void)
{
	int gameObjectNum = gameObjects.size();
	for (int i = 0; i < gameObjectNum; i++)
	{
		if (!gameObjects[i]->getCanMove())
		{
			continue;
		}
		gameObjects[i]->dataUpdate();
		for (int j = 0; j < gameObjectNum; j++)
		{
			if (i == j)
			{
				continue;
			}
			//x position update
			gameObjects[i]->positionUpdateX();
			vector<TouchStatus> list = collision_detection(gameObjects[i]);
			while (list.size() != 0)
			{
				D3DXVECTOR3 new_point(*(gameObjects[i]->getVecNowPos()));
				float gameObjLength = abs(gameObjects[i]->getBoundingRect().right - gameObjects[i]->getBoundingRect().left);
				float listObjLength = abs(list[0].obj->getBoundingRect().right - list[0].obj->getBoundingRect().left);
				if (gameObjects[i]->getVecMoveSpeed()->x > 0)
				{
					new_point.x = list[0].obj->getVecNowPos()->x - (gameObjLength / 2) - (listObjLength / 2);
				}
				else
				{
					new_point.x = list[0].obj->getVecNowPos()->x + (gameObjLength / 2) + (listObjLength / 2);
				}
				gameObjects[i]->setVecNowPos(&new_point);
				list = collision_detection(gameObjects[i]);
			}

			//z position update
			gameObjects[i]->positionUpdateZ();
			vector<TouchStatus> list = collision_detection(gameObjects[i]);
			while (list.size() != 0)
			{
				D3DXVECTOR3 new_point(*(gameObjects[i]->getVecNowPos()));
				float gameObjWidth = abs(gameObjects[i]->getBoundingRect().top - gameObjects[i]->getBoundingRect().bottom);
				float listObjWidth = abs(list[0].obj->getBoundingRect().top - list[0].obj->getBoundingRect().bottom);
				if (gameObjects[i]->getVecMoveSpeed()->z > 0)
				{
					new_point.x = list[0].obj->getVecNowPos()->z - (gameObjWidth / 2) - (listObjWidth / 2);
				}
				else
				{
					new_point.x = list[0].obj->getVecNowPos()->z + (gameObjWidth / 2) + (listObjWidth / 2);
				}
				gameObjects[i]->setVecNowPos(&new_point);
				list = collision_detection(gameObjects[i]);
			}
		}
	}
}

TouchType MapManage::collision_detection(GameObject * gameObject1, GameObject * gameObject2)
{
	TouchType is_hitted = TouchType::noTouch;

	RECT rect1 = gameObject1->getBoundingRect();
	D3DXVECTOR2* position1 = new D3DXVECTOR2[4];
	position1[0] = D3DXVECTOR2(rect1.left, rect1.top);
	position1[1] = D3DXVECTOR2(rect1.right, rect1.top);
	position1[2] = D3DXVECTOR2(rect1.left, rect1.bottom);
	position1[3] = D3DXVECTOR2(rect1.right, rect1.bottom);

	RECT rect2 = gameObject2->getBoundingRect();
	D3DXVECTOR2* position2 = new D3DXVECTOR2[4];
	position2[0] = D3DXVECTOR2(rect2.left, rect2.top);
	position2[1] = D3DXVECTOR2(rect2.right, rect2.top);
	position2[2] = D3DXVECTOR2(rect2.left, rect2.bottom);
	position2[3] = D3DXVECTOR2(rect2.right, rect2.bottom);

	is_hitted = Physics::rectTouchRect(position1, position2);
	delete[] position1;
	delete[] position2;

	return is_hitted;

}

vector<TouchStatus> MapManage::collision_detection(GameObject * gameObject)
{
	vector<TouchStatus> list;
	RECT rect = gameObject->getBoundingRect();
	D3DXVECTOR2* position = new D3DXVECTOR2[4];
	position[0] = D3DXVECTOR2(rect.left, rect.top);
	position[1] = D3DXVECTOR2(rect.right, rect.top);
	position[2] = D3DXVECTOR2(rect.left, rect.bottom);
	position[3] = D3DXVECTOR2(rect.right, rect.bottom);

	int ganmeObjectNum = gameObjects.size();
	for (int i = 0; i < ganmeObjectNum; i++)
	{
		if (gameObjects[i] == gameObject)
		{
			continue;
		}
		RECT rect2 = gameObjects[i]->getBoundingRect();
		D3DXVECTOR2* position2 = new D3DXVECTOR2[4];
		position2[0] = D3DXVECTOR2(rect2.left, rect2.top);
		position2[1] = D3DXVECTOR2(rect2.right, rect2.top);
		position2[2] = D3DXVECTOR2(rect2.left, rect2.bottom);
		position2[3] = D3DXVECTOR2(rect2.right, rect2.bottom);

		TouchType ty = Physics::rectTouchRect(position2, position);
		if (ty != TouchType::noTouch)
		{
			list.push_back(TouchStatus{ gameObjects[i], ty });
		}
		delete[] position2;
	}
	delete[] position;
	return list;
}