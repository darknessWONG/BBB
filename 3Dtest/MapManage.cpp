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
		//x position update
		gameObjects[i]->positionUpdateX();
		vector<TouchStatus> list = collision_detection(gameObjects[i]);
		D3DXVECTOR3 xSpeed = *gameObjects[i]->getVecMoveSpeed();
		while (list.size() != 0)
		{
			D3DXVECTOR3 new_point(*(gameObjects[i]->getVecNowPos()));
			//float gameObjLength = Physics::round(fabs(gameObjects[i]->getBoundingRect().right - gameObjects[i]->getBoundingRect().left), FLOATBITS);
			//float listObjLength = Physics::round(fabs(list[0].obj->getBoundingRect().right - list[0].obj->getBoundingRect().left), FLOATBITS);
			////position is the center of the model coordinates, 
			////but it may not be the center of the bounding box
			//float gameObjCenterPos = Physics::round(gameObjects[i]->getBoundingCenter().x - new_point.x, FLOATBITS);
			float gameObjLength = fabs(gameObjects[i]->getBoundingRect().right - gameObjects[i]->getBoundingRect().left);
			float listObjLength = fabs(list[0].obj->getBoundingRect().right - list[0].obj->getBoundingRect().left);
			//position is the center of the model coordinates, 
			//but it may not be the center of the bounding box
			float gameObjCenterPos = gameObjects[i]->getBoundingCenter().x - new_point.x;
			if (xSpeed.x > 0)
			{
				//new_point.x = Physics::round((list[0].obj->getBoundingCenter().x - ((gameObjLength + listObjLength) / 2.0) - gameObjCenterPos), FLOATBITS);
				new_point.x = (list[0].obj->getBoundingCenter().x - ((gameObjLength + listObjLength) / 2.0) - gameObjCenterPos);
			}
			else
			{
				//new_point.x = Physics::round((list[0].obj->getBoundingCenter().x + ((gameObjLength + listObjLength) / 2.0) - gameObjCenterPos), FLOATBITS);

				new_point.x = (list[0].obj->getBoundingCenter().x + ((gameObjLength + listObjLength) / 2.0) - gameObjCenterPos);
			}
			D3DXVECTOR3 newSpeed = *gameObjects[i]->getVecMoveSpeed();
			newSpeed.x = 0.0f;
			gameObjects[i]->setVecMoveSpeed(&newSpeed);
			gameObjects[i]->setVecNowPos(&new_point);
			list = collision_detection(gameObjects[i]);
		}

		//z position update
		gameObjects[i]->positionUpdateZ();
		list = collision_detection(gameObjects[i]);
		D3DXVECTOR3 zSpeed = *gameObjects[i]->getVecMoveSpeed();
		while (list.size() != 0)
		{
			D3DXVECTOR3 new_point(*(gameObjects[i]->getVecNowPos()));
			//float gameObjWidth = Physics::round(abs(gameObjects[i]->getBoundingRect().top - gameObjects[i]->getBoundingRect().bottom), FLOATBITS);
			//float listObjWidth = Physics::round(abs(list[0].obj->getBoundingRect().top - list[0].obj->getBoundingRect().bottom), FLOATBITS);
			////position is the center of the model coordinates, 
			////but it may not be the center of the bounding box
			//float gameObjCenterPos = Physics::round(gameObjects[i]->getBoundingCenter().y - new_point.z, FLOATBITS);
			float gameObjWidth = abs(gameObjects[i]->getBoundingRect().top - gameObjects[i]->getBoundingRect().bottom);
			float listObjWidth = abs(list[0].obj->getBoundingRect().top - list[0].obj->getBoundingRect().bottom);
			//position is the center of the model coordinates, 
			//but it may not be the center of the bounding box
			float gameObjCenterPos = gameObjects[i]->getBoundingCenter().y - new_point.z;
			if (zSpeed.z > 0)
			{
				//new_point.z = Physics::round(list[0].obj->getBoundingCenter().y - ((gameObjWidth + listObjWidth) / 2.0) - gameObjCenterPos, FLOATBITS);

				new_point.z = list[0].obj->getBoundingCenter().y - ((gameObjWidth + listObjWidth) / 2.0) - gameObjCenterPos;
			}
			else
			{
				//new_point.z = Physics::round(list[0].obj->getBoundingCenter().y + ((gameObjWidth + listObjWidth) / 2.0) - gameObjCenterPos, FLOATBITS);

				new_point.z = list[0].obj->getBoundingCenter().y + ((gameObjWidth + listObjWidth) / 2.0) - gameObjCenterPos;
			}
			D3DXVECTOR3 newSpeed = *gameObjects[i]->getVecMoveSpeed();
			newSpeed.z = 0.0f;
			gameObjects[i]->setVecMoveSpeed(&newSpeed);
			gameObjects[i]->setVecNowPos(&new_point);
			list = collision_detection(gameObjects[i]);
		}
	}
}

void MapManage::drawGameObjects(LPDIRECT3DDEVICE9 pD3DDevice)
{
	int gameObjectNum = gameObjects.size();
	for (int i = 0; i < gameObjectNum; i++)
	{
		gameObjects[i]->calWorldMatrix();
		gameObjects[i]->draw(pD3DDevice);
	}
}

TouchType MapManage::collision_detection(GameObject * gameObject1, GameObject * gameObject2)
{
	TouchType is_hitted = TouchType::noTouch;

	RECTF rect1 = gameObject1->getBoundingRect();
	D3DXVECTOR2* position1 = new D3DXVECTOR2[4];
	position1[0] = D3DXVECTOR2(rect1.left, rect1.top);
	position1[1] = D3DXVECTOR2(rect1.right, rect1.top);
	position1[2] = D3DXVECTOR2(rect1.left, rect1.bottom);
	position1[3] = D3DXVECTOR2(rect1.right, rect1.bottom);

	RECTF rect2 = gameObject2->getBoundingRect();
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
	RECTF rect = gameObject->getBoundingRect();
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
		RECTF rect2 = gameObjects[i]->getBoundingRect();
		D3DXVECTOR2* position2 = new D3DXVECTOR2[4];
		position2[0] = D3DXVECTOR2(rect2.left, rect2.top);
		position2[1] = D3DXVECTOR2(rect2.right, rect2.top);
		position2[2] = D3DXVECTOR2(rect2.left, rect2.bottom);
		position2[3] = D3DXVECTOR2(rect2.right, rect2.bottom);

		TouchType ty = Physics::rectTouchRect(position2, position);
		if (ty == TouchType::cover)
		{
			list.push_back(TouchStatus{ gameObjects[i], ty });
		}
		delete[] position2;
	}
	delete[] position;
	return list;
}