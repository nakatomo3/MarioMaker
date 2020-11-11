#pragma once
#include "Scene.h"
class SelectStageScene : public Scene {
public:
	SelectStageScene(string name);

	void Start();
	void Load();
	void Update();

private:
	GameObject* manager;
};

