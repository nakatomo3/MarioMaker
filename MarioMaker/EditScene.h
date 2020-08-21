#pragma once
#include "Scene.h"
#include "Texture.h"
class EditScene : public Scene {
public:
	EditScene(string name);

	void Start();
	void Load();

	void Update();

private:

	GameObject* editorObject;
	GameObject* gameObject;
	GameObject* stage;

	//�Q�[�������I�u�W�F�N�g
	GameObject* player;
	GameObject* camera;

	//�ҏW�I�u�W�F�N�g
	GameObject* editorWindow;
	GameObject* editorCamera;

	Texture* playerTexture;

	bool isEditMode = true;
	bool beforeInputStart = false;
};