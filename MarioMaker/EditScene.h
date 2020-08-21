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

	//ゲーム部分オブジェクト
	GameObject* player;
	GameObject* camera;

	//編集オブジェクト
	GameObject* editorWindow;
	GameObject* editorCamera;

	Texture* playerTexture;

	bool isEditMode = true;
	bool beforeInputStart = false;
};