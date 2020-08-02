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

	//�I�u�W�F�N�g�}�l�[�W���[�ɓo�^����B�Ǘ��ΏۂłȂ��Ǝ����I��Start��Update���Ă΂�Ȃ��B
	static GameObject* Instantiate(GameObject* instance);

	//instance���Ǘ��Ώۂɓ����Ă��邩�ǂ����̊m�F
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
	
	//�Ǘ��Ώۂ���O��delete����B
	static void Destroy(GameObject* instance);

	static vector<GameObject*> objects;
	
};