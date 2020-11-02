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

	static void Load();
	static void UnLoad(Scene* scene);

	//�g�p�֎~�A�t���[���̍Ō�ɍ폜����\��̃I�u�W�F�N�g�S�Ă��폜����
	static void Destroy();

private:
	
	//�Ǘ��Ώۂ���O�����X�g�ɒǉ�����
	static void AddDestroyList(GameObject* instance);

	static vector<GameObject*> objects;

	static bool isEndUpdate;

	static vector<GameObject*> destroyList;
	
};