#pragma once
#include "Scene.h"
#include "StageManager.h"
class PlayScene : public Scene {
public:
	PlayScene(string name);

	void Load();
	void Start();

private:
	GameObject* stageManager;
	StageManager* stageManagerScript;
};