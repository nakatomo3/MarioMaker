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
	GameObject* player;
	GameObject* camera;

	Texture* playerTexture;

	bool isEditMode = false;
	bool beforeInputStart = false;
};