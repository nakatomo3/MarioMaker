#pragma once
#include "ScriptBase.h"
typedef enum {
	NORMAL,
	UNDER_GROUND,
	WATER,
	CASTLE
}StageType;

class StageManager : public ScriptBase {
public:
	void Start();

	GameObject* GetChildGameObject(Vector3 pos);

	void SetStageSize(unsigned int size);
	int GetStageSize();

	void SetObject(int x, int y, char obj);
	char GetStageObject(int x, int y);

	void SaveStage(string path);
	void ReadStage(string path);

private:
	StageType stageType = NORMAL;

	vector<vector<char>> stage;

	int stageSizeX = 100;

};

