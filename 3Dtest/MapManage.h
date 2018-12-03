#pragma once
#include <vector>
#include "GameObject.h"
#include "Model.h"
#include "Vigilance.h"
#include "Physics.h"
#include "Player.h"
#include "Enemy.h"


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
	void cleanGameObject(void);
	void updateGameObejcts(void);
	void drawGameObjects(LPDIRECT3DDEVICE9 pD3DDevice);

	vector<TouchStatus> collisionDetection(GameObject* gameObject);
	//do collision dectection with overlap level
	vector<TouchStatus> collisionDetectionOvl(GameObject* gameObject);
	TouchType collisionDetection(GameObject* gameObject1, GameObject* gameObject2);
	vector<GameObject*> calObjectInCycle(Vigilance* cycle);
	vector<GameObject*> calObjectOnSight(Enemy* enemy, Player* player);
	/*===========================================
	public geter / seter
	============================================*/

private:
	vector<GameObject*> gameObjects;
};

