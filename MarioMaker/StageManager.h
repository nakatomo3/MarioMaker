#pragma once
#include "ScriptBase.h"
class StageManager : public ScriptBase {
public:
	void Start();

	GameObject* GetChildGameObject(Vector3 pos);

	void SetStageSize(unsigned int size);
	int GetStageSize();

	void SetObject(int x, int y, char obj);
	char GetStageObject(int x, int y);
private:
	vector<vector<char>> stage;

	int stageSizeX = 100;
};

