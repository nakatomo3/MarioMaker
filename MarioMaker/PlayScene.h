#pragma once
#include "Scene.h"
#include "StageManager.h"
#include "Player.h"
class PlayScene : public Scene {
public:
	PlayScene(string name);

	void Load();
	void Start();

	static bool isPlayScene();

private:
	GameObject* camera;

	GameObject* player;
	Player* playerScript;
	Texture* playerTexture;

	GameObject* stageManager;
	StageManager* stageManagerScript;

	static bool isPlayMode;
};