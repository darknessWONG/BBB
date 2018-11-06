#pragma once
#include <vector>
#include "GameObject.h"
#include "Model.h"
#include "Physics.h"


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

	vector<TouchStatus> collision_detection(GameObject* gameObject);
	TouchType collision_detection(GameObject* gameObject1, GameObject* gameObject2);
	/*===========================================
	public geter / seter
	============================================*/

private:
	vector<GameObject*> gameObjects;
};

