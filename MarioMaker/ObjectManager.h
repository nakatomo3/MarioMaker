#pragma once
using namespace std;
#include "GameObject.h"
#include "Singleton.h"
#include<vector>
class GameObject;
class Camera;
class Scene;
class SceneManager;

class ObjectManager{
	friend class GameObject;
	friend class SceneManager;
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

	static void Load();
	static void UnLoad(Scene* scene);

	//使用禁止、フレームの最後に削除する予定のオブジェクト全てを削除する
	static void Destroy();

private:
	
	//管理対象から外すリストに追加する
	static void AddDestroyList(GameObject* instance);

	static vector<GameObject*> objects;

	static bool isEndUpdate;

	static vector<GameObject*> destroyList;
	
};