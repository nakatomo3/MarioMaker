#pragma once
#include "ScriptBase.h"
#include "Texture.h"
#include "Image.h"
class TitleScelectIcon : public ScriptBase {
public:
	void Start();

	void Update();

	void OnDestroy();

private:
	bool isPlayMode = false;

	SHORT beforeInputLY;
	bool beforeInputB;

	Texture* texture;
	Image* image;

	void Input();

	void MovePosition();
};