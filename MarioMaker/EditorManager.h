#pragma once
#include "ScriptBase.h"
#include "Texture.h"
class EditorManager : public ScriptBase {
public:
	void Start();
	void Update();

	void SetCamera(GameObject* _camera);
private:
	GameObject* camera;
	GameObject* cursor;

	Texture* cursorTexture;

	int cursorPosX = 0;
	int cursorPosY = 0;

	SHORT beforeInputLX;
	SHORT beforeInputLY;

	float firstTimer = 0;
	float firstInterval = 0.5f;

	float continuousTimer = 0;
	const float continuousInterval = 0.1f;

	void CursorMove();
};