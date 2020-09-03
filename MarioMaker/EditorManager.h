#pragma once
#include "ScriptBase.h"
#include "Texture.h"
#include "Text.h"
#include "NumText.h"
#include "Image.h"
#include "StageManager.h"

typedef enum {
	DEFAULT_MODE,
	AREA_MODE,
	DETAIL_MODE
}EditMode;

class EditorManager : public ScriptBase {
public:
	void Start();
	void Update();

	void SetCamera(GameObject* _camera);
	void SetStage(StageManager* stageManager);

	Vector3 GetCursorPos();

private:
	StageManager* stage;

	GameObject* camera;
	GameObject* cursor;

	GameObject* editingArea;

	Texture* cursorTexture;

	int cursorPosX = 10;
	int cursorPosY = 5;

	int areaStartPosX = 0;
	int areaStartPosY = 0;

	Vector2 beforeCursorPos;

	SHORT beforeInputLX;
	SHORT beforeInputLY;

	WORD beforeControllerButton;
	BYTE beforeLTrigger;
	BYTE beforeRTrigger;

	NumText* posXText;
	NumText* posYText;
	Image* objectImage;
	Text* nameText;

	float firstTimer = 0;
	float firstInterval = 0.5f;

	float continuousTimer = 0;
	const float continuousInterval = 0.1f;

	int objectNumber;
	const int objectMax = 4;

	EditMode nowMode = DEFAULT_MODE;

	string objectNames[4] = {
		"地形ブロック",
		"ブロック",
		"ハテナブロック",
		"足場ブロック",
	};

	Texture* objectTextures[4];
	Texture* usedBlockTexture;

	void TextureLoad();

	void CursorMove();

	void StageEdit();

	void InformationShow();

	void DestroyObject(int x, int y);
	void PlaceObject(int x, int y);

	void DefaultModeEdit();
	void AreaModeEdit();
};