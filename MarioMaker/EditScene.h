#pragma once
#include "Scene.h"
#include "Texture.h"
#include "EditorManager.h"
#include "StageManager.h"
class EditScene : public Scene {
public:
	EditScene(string name);

	void Start();
	void Load();

	void Update();
	static bool GetIsEditMode();

private:

	StageManager* stageManager;

	GameObject* editorObject;
	GameObject* gameObject;
	GameObject* stage;

	//�Q�[�������I�u�W�F�N�g
	GameObject* player;
	GameObject* camera;

	//�ҏW�I�u�W�F�N�g
	GameObject* editorWindow;
	GameObject* editorCamera;

	EditorManager* editorManager;

	Texture* playerTexture;

	static bool isEditMode;
	bool beforeInputStart = false;
};