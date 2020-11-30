#pragma once
#include "ScriptBase.h"
#include "Texture.h"
typedef enum {
	NORMAL,
	UNDER_GROUND,
	WATER,
	CASTLE
}StageType;

class StageManager : public ScriptBase {
public:
	void Start();
	void OnDestroy();

	GameObject* GetChildGameObject(Vector3 pos);

	void SetStageSize(unsigned int size);
	int GetStageSize();

	void SetObject(int x, int y, char obj);
	char GetStageObject(int x, int y);

	void SaveStage(string path);
	void ReadStage(string path);

	static void SetStagePath(string _path);

	Texture* GetObjectTexture(int index);

private:
	StageType stageType = NORMAL;

	vector<vector<char>> stage;

	int stageSizeX = 100;

	static string path;

	Texture* objectTextures[4];
	Texture* usedBlockTexture;
};

