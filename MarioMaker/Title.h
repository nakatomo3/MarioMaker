#pragma once
#include "Scene.h"
#include "Texture.h"
class Title : public Scene {
public:
	Title(string name);

	void Load();

	void Start();

	void Unload();

private:
	Texture* titleTexture;
	Texture* selectIconTexture;

	Texture* createTexture;
	Texture* playTexture;
	Texture* modeTexture;

	GameObject* titleBackGround;
	GameObject* selectIcon;
	GameObject* camera;
	GameObject* modeObject;
};

