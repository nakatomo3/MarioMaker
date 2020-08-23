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

private:

	StageManager* stageManager;

	GameObject* editorObject;
	GameObject* gameObject;
	GameObject* stage;

	//ゲーム部分オブジェクト
	GameObject* player;
	GameObject* camera;

	//編集オブジェクト
	GameObject* editorWindow;
	GameObject* editorCamera;

	EditorManager* editorManager;

	Texture* playerTexture;

	bool isEditMode = true;
	bool beforeInputStart = false;
};