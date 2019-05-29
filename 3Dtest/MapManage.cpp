#include "stdafx.h"
#include "MapManage.h"
#include "RoundShadowHandler.h"


MapManage::MapManage()
{
}


MapManage::~MapManage()
{
}

void MapManage::addGameObject(GameObject * gameObject)
{
	if (gameObject != NULL)
	{
		gameObjects.push_back(gameObject);
	}
}

void MapManage::addGameObject2D(MeumUI * gameObject2D)
{
	if (gameObject2D != NULL)
	{
		gameObjects2D.push_back(gameObject2D);
	}
}

void MapManage::cleanGameObject(void)
{
	gameObjects.clear();
	gameObjects2D.clear();
}

void MapManage::updateGameObejcts(void)
{
	int gameObjectNum = (int)gameObjects.size();
	for (int i = 0; i < gameObjectNum; i++)
	{
		gameObjects[i]->calBounding();
		gameObjects[i]->dataUpdate();
		if (!gameObjects[i]->getCanMove() || !gameObjects[i]->getMoveThisTurn())
		{
			gameObjects[i]->unlockThisTurn();
			continue;
		}
		if (!gameObjects[i]->getIsDisplay())
		{
			continue;
		}
		//x position update
		gameObjects[i]->positionUpdateX();
		vector<TouchStatus> list = collisionDetectionOvl(gameObjects[i]);
		D3DXVECTOR3 xSpeed = *gameObjects[i]->getVecMoveSpeed();
		while (list.size() != 0)
		{
			int j = 0;
			int listNum = (int)list.size();
			while (j < listNum && list[j].touchType != TouchType::cover)
			{
				j++;
			}
			if (j >= listNum)
			{
				break;
			}
			D3DXVECTOR3 new_point(*(gameObjects[i]->getVecNowPos()));
			float gameObjLength = fabs(gameObjects[i]->getBoundingRect().right - gameObjects[i]->getBoundingRect().left);
			float listObjLength = fabs(list[0].obj->getBoundingRect().right - list[0].obj->getBoundingRect().left);
			//position is the center of the model coordinates, 
			//but it may not be the center of the bounding box
			float gameObjCenterPos = gameObjects[i]->getBoundingCenter().x - new_point.x;
			if (xSpeed.x > 0)
			{
				new_point.x = (list[0].obj->getBoundingCenter().x - ((gameObjLength + listObjLength) / 2.0f) - (float)pow(0.1, FLOAT_BITS) - gameObjCenterPos);
			}
			else
			{
				new_point.x = (list[0].obj->getBoundingCenter().x + ((gameObjLength + listObjLength) / 2.0f) + (float)pow(0.1, FLOAT_BITS) - gameObjCenterPos);
			}
			D3DXVECTOR3 newSpeed = *gameObjects[i]->getVecMoveSpeed();
			newSpeed.x = 0.0f;
			gameObjects[i]->setVecMoveSpeed(&newSpeed);
			gameObjects[i]->setVecNowPos(&new_point);
			gameObjects[i]->calBounding();
			list = collisionDetectionOvl(gameObjects[i]);
		}


		//z position update
		gameObjects[i]->positionUpdateZ();
		list = collisionDetectionOvl(gameObjects[i]);
		D3DXVECTOR3 zSpeed = *gameObjects[i]->getVecMoveSpeed();
		while (list.size() != 0)
		{
			int j = 0;
			int listNum = (int)list.size();
			while (j < listNum && list[j].touchType != TouchType::cover)
			{
				j++;
			}
			if (j >= listNum)
			{
				break;
			}
			D3DXVECTOR3 new_point(*(gameObjects[i]->getVecNowPos()));
			float gameObjWidth = abs(gameObjects[i]->getBoundingRect().top - gameObjects[i]->getBoundingRect().bottom);
			float listObjWidth = abs(list[0].obj->getBoundingRect().top - list[0].obj->getBoundingRect().bottom);
			//position is the center of the model coordinates, 
			//but it may not be the center of the bounding box
			float gameObjCenterPos = gameObjects[i]->getBoundingCenter().y - new_point.z;
			if (zSpeed.z > 0)
			{
				new_point.z = list[0].obj->getBoundingCenter().y - ((gameObjWidth + listObjWidth) / 2.0f) - (float)pow(0.1, FLOAT_BITS) - gameObjCenterPos;
			}
			else
			{
				new_point.z = list[0].obj->getBoundingCenter().y + ((gameObjWidth + listObjWidth) / 2.0f) + (float)pow(0.1, FLOAT_BITS) - gameObjCenterPos;
			}
			D3DXVECTOR3 newSpeed = *gameObjects[i]->getVecMoveSpeed();
			newSpeed.z = 0.0f;
			gameObjects[i]->setVecMoveSpeed(&newSpeed);
			gameObjects[i]->setVecNowPos(&new_point);
			gameObjects[i]->calBounding();
			list = collisionDetectionOvl(gameObjects[i]);
		}

		//y position update
		gameObjects[i]->positionUpdateY();
	}

	gameObjectNum = (int)gameObjects2D.size();
	for (int i = 0; i < gameObjectNum; i++)
	{
		gameObjects2D[i]->dataUpdate();
	}
}

void MapManage::drawGameObjects(LPDIRECT3DDEVICE9 pD3DDevice)
{
	int gameObjectNum = (int)gameObjects.size();
	for (int i = 0; i < gameObjectNum; i++)
	{
		gameObjects[i]->calWorldMatrix();
		gameObjects[i]->draw(pD3DDevice);
	}

	gameObjectNum = (int)gameObjects2D.size();
	for (int i = 0; i < gameObjectNum; i++)
	{
		gameObjects2D[i]->draw(pD3DDevice);
	}

#ifdef ROUNDSHADOWHANDLER
	RoundShadowHandler::draw(pD3DDevice);
#endif
}

void MapManage::gameObjectsBeforeUpdate(void)
{
	int gameObectsNum = (int)gameObjects.size();
	for (int i = 0; i < gameObectsNum; i++)
	{
		gameObjects[i]->beforeUpdate();
	}
}

TouchType MapManage::collisionDetection(GameObject * gameObject1, GameObject * gameObject2)
{
	TouchType is_hitted = TouchType::noTouch;

	D3DXVECTOR2* position1 = Physics::rectToPoints(gameObject1->getBoundingRect());
	D3DXVECTOR2* position2 = Physics::rectToPoints(gameObject2->getBoundingRect());

	is_hitted = Physics::rectTouchRect(position1, position2);
	delete[] position1;
	delete[] position2;

	return is_hitted;

}

vector<TouchStatus> MapManage::collisionDetectionOvl(GameObject * gameObject)
{
	vector<TouchStatus> list;
	D3DXVECTOR2* position = Physics::rectToPoints(gameObject->getBoundingRect());

	int ganmeObjectNum = (int)gameObjects.size();
	for (int i = 0; i < ganmeObjectNum; i++)
	{
		if (0 > gameObject->getOverlapLevel() + gameObjects[i]->getOverlapLevel())
		{
			continue;
		}
		if (!gameObjects[i]->getIsDisplay())
		{
			continue;
		}
		if (gameObjects[i] == gameObject)
		{
			continue;
		}
		D3DXVECTOR2* position2 = Physics::rectToPoints(gameObjects[i]->getBoundingRect());

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

vector<GameObject*> MapManage::calObjectInCycle(Vigilance * cycle)
{
	D3DXVECTOR2 center = cycle->getBoundingCenter();
	Cycle c;
	c.center_x = center.x;
	c.center_y = center.y;
	c.r = cycle->getRadius();

	int gameObjectNum = (int)gameObjects.size();
	vector<GameObject*> list;
	for (int i = 0; i < gameObjectNum; i++)
	{
		if (gameObjects[i] == cycle)
		{
			continue;
		}
		D3DXVECTOR2 objCenter = gameObjects[i]->getBoundingCenter();
		if (Physics::pointInCycle(&c, &objCenter))
		{
			list.push_back(gameObjects[i]);
		}
	}
	return list;
}

vector<GameObject*> MapManage::calObjectInCycle(D3DXVECTOR2 center, float radius)
{
	Cycle c;
	c.center_x = center.x;
	c.center_y = center.y;
	c.r = radius;

	int gameObjectNum = (int)gameObjects.size();
	vector<GameObject*> list;
	for (int i = 0; i < gameObjectNum; i++)
	{
		D3DXVECTOR2 objCenter = gameObjects[i]->getBoundingCenter();
		if (Physics::pointInCycle(&c, &objCenter))
		{
			list.push_back(gameObjects[i]);
		}
	}
	return list;
}

vector<GameObject*> MapManage::calObjectOnSight(GameObject * enemy, GameObject * player) const
{
	line_segment sight = Physics::createLinesegment(enemy->getBoundingCenter(), player->getBoundingCenter());

	vector<GameObject*> list;

	int gameObjNum = (int)gameObjects.size();
	for (int i = 0; i < gameObjNum; i++)
	{
		if (gameObjects[i] == enemy || gameObjects[i] == player || typeid(Vigilance) == typeid(*gameObjects[i]))
		{
			continue;
		}
		RECTF rect = gameObjects[i]->getBoundingRect();
		line_segment diagonal1 = Physics::createLinesegment(D3DXVECTOR2(rect.left, rect.top), D3DXVECTOR2(rect.right, rect.bottom));
		line_segment diagonal2 = Physics::createLinesegment(D3DXVECTOR2(rect.right, rect.top), D3DXVECTOR2(rect.left, rect.bottom));
		if (Physics::linesegmentTouchLinesegment(sight, diagonal1) || Physics::linesegmentTouchLinesegment(sight, diagonal2))
		{
			list.push_back(gameObjects[i]);
		}
	}

	return list;
}


bool MapManage::calObjectOnSight(GameObject * enemy, GameObject * player, vector<GameObject*> &list) const
{
	//check is behind
	D3DXVECTOR2 vec = player->getBoundingCenter() - enemy->getBoundingCenter();
	D3DXVECTOR3 enemyFront = *enemy->getVecFront();
	D3DXVECTOR2 enemyFront2D = { enemyFront.x, enemyFront.z };
	float dot = D3DXVec2Dot(&vec, &enemyFront2D);
	if (dot < 0)
	{
		return false;
	}

	//check is have Obstacle
	line_segment sight = Physics::createLinesegment(enemy->getBoundingCenter(), player->getBoundingCenter());

	int gameObjNum = (int)gameObjects.size();
	for (int i = 0; i < gameObjNum; i++)
	{
		if (gameObjects[i] == enemy || gameObjects[i] == player || typeid(Vigilance) == typeid(*gameObjects[i]))
		{
			continue;
		}
		RECTF rect = gameObjects[i]->getBoundingRect();
		line_segment diagonal1 = Physics::createLinesegment(D3DXVECTOR2(rect.left, rect.top), D3DXVECTOR2(rect.right, rect.bottom));
		line_segment diagonal2 = Physics::createLinesegment(D3DXVECTOR2(rect.right, rect.top), D3DXVECTOR2(rect.left, rect.bottom));
		if (Physics::linesegmentTouchLinesegment(sight, diagonal1) || Physics::linesegmentTouchLinesegment(sight, diagonal2))
		{
			list.push_back(gameObjects[i]);
		}
	}

	if (list.size() > 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}

vector<GameObject*> MapManage::calObjectOnSightOvl(GameObject * active, GameObject * target) const
{
	line_segment sight = Physics::createLinesegment(active->getBoundingCenter(), target->getBoundingCenter());

	vector<GameObject*> list;

	int gameObjNum = (int)gameObjects.size();
	for (int i = 0; i < gameObjNum; i++)
	{
		if (gameObjects[i] == active || gameObjects[i] == target || typeid(Vigilance) == typeid(*gameObjects[i]) 
			|| gameObjects[i]->getOverlapLevel() + active->getOverlapLevel() <= 0)
		{
			continue;
		}
		RECTF rect = gameObjects[i]->getBoundingRect();
		line_segment diagonal1 = Physics::createLinesegment(D3DXVECTOR2(rect.left, rect.top), D3DXVECTOR2(rect.right, rect.bottom));
		line_segment diagonal2 = Physics::createLinesegment(D3DXVECTOR2(rect.right, rect.top), D3DXVECTOR2(rect.left, rect.bottom));
		if (Physics::linesegmentTouchLinesegment(sight, diagonal1) || Physics::linesegmentTouchLinesegment(sight, diagonal2))
		{
			list.push_back(gameObjects[i]);
		}
	}

	return list;
}

vector<TouchStatus> MapManage::collisionDetection(GameObject * gameObject)
{
	vector<TouchStatus> list;
	D3DXVECTOR2* position = Physics::rectToPoints(gameObject->getBoundingRect());

	int ganmeObjectNum = (int)gameObjects.size();
	for (int i = 0; i < ganmeObjectNum; i++)
	{
		if (gameObjects[i] == gameObject)
		{
			continue;
		}
		D3DXVECTOR2* position2 = Physics::rectToPoints(gameObjects[i]->getBoundingRect());

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