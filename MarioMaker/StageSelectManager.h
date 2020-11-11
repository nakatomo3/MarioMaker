#pragma once
#include "ScriptBase.h"
#include "StageManager.h"
#include "Vector2.h"
#include "input.h"

struct StageFormat {
public:
	StageType type;
	unsigned int stageSizeX;
};

class StageSelectManager : public ScriptBase {
public:
	const string folderPath = "Stages/";
	
	void Start();
	void Update();

private:
	std::vector<std::string> fileNames = std::vector<std::string>();

	std::vector<GameObject*> stageLists = std::vector<GameObject*>();

	void ReadStageFiles();

	void SetStageFiles();

	float dragTimer = 0;

	int cursorPos = 0;

	bool isMouseMode = false;
	Vector2 beforeCursorPos;
	GameObject* cursor;

	float dragRange;

	void MouseMode();
	void Drag();

	XINPUT_GAMEPAD beforeController;
	void ControllerMode();
};