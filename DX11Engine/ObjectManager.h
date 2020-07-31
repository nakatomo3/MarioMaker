#pragma once
using namespace std;
#include "GameObject.h"
#include "Singleton.h"
#include<vector>
class GameObject;
class Camera;
class Scene;

class ObjectManager{
	friend class GameObject;
public:

	//オブジェクトマネージャーに登録する。管理対象でないと自動的にStartもUpdateも呼ばれない。
	static GameObject* Instantiate(GameObject* instance);

	//instanceが管理対象に入っているかどうかの確認
	static bool CheckInstance(GameObject* instance);

	static void Awake();
	static void Start();
	static void FirstUpdate();
	static void Update();
	static void LateUpdate();

	static void Draw();
	static void LateDraw();

	static void Init();

	static void UnLoad(Scene* scene);

private:
	
	//管理対象から外しdeleteする。
	static void Destroy(GameObject* instance);

	static vector<GameObject*> objects;
	
};