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

	GameObject* titleBackGround;
	GameObject* selectIcon;
	GameObject* camera;
};

