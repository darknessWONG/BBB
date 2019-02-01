#pragma once
#include <vector>
#include "GameObject.h"
#include "Model.h"
#include "Vigilance.h"
#include "Physics.h"
#include "Player.h"
#include "Enemy.h"
#include "MeumUI.h"

typedef struct
{
	GameObject* obj;
	TouchType touchType;
}TouchStatus;

class MapManage
{
public:
	MapManage();
	~MapManage();

	/*===========================================
	virtual member
	============================================*/

	/*===========================================
	public function
	============================================*/
	void addGameObject(GameObject* gameObject);
	void addGameObject2D(MeumUI* gameObject2D);
	void cleanGameObject(void);
	void updateGameObejcts(void);
	void drawGameObjects(LPDIRECT3DDEVICE9 pD3DDevice);
	void gameObjectsBeforeUpdate(void);

	TouchType collisionDetection(GameObject* gameObject1, GameObject* gameObject2);
	//do collision dectection without overlap level, can expressed the absolute positional relations
	vector<TouchStatus> collisionDetection(GameObject* gameObject);
	//do collision dectection with overlap level
	vector<TouchStatus> collisionDetectionOvl(GameObject* gameObject);

	vector<GameObject*> calObjectInCycle(Vigilance* cycle);
	vector<GameObject*> calObjectInCycle(D3DXVECTOR2 center, float radius);
	vector<GameObject*> calObjectOnSight(GameObject* enemy, GameObject* player) const;
	//check object on sight or not whth overlap level, it will do overlap test with actve and the object on sight
	vector<GameObject*> calObjectOnSightOvl(GameObject* active, GameObject* target) const;
	/*===========================================
	public geter / seter
	============================================*/

private:
	vector<GameObject*> gameObjects;
	vector<MeumUI*> gameObjects2D;
};

