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

private:
	StageManager* stage;

	GameObject* camera;
	GameObject* cursor;

	Texture* cursorTexture;

	int cursorPosX = 0;
	int cursorPosY = 0;

	Vector2 beforeCursorPos;

	SHORT beforeInputLX;
	SHORT beforeInputLY;

	WORD beforeControllerButton;

	NumText* posXText;
	NumText* posYText;
	Image* objectImage;
	Text* nameText;

	float firstTimer = 0;
	float firstInterval = 0.5f;

	float continuousTimer = 0;
	const float continuousInterval = 0.1f;

	int objectNumber;
	const int objectMax = 6;

	EditMode nowMode = DEFAULT_MODE;

	string objectNames[6] = {
		"地形ブロック",
		"ブロック",
		"ハテナブロック",
		"D",
		"E",
		"F"
	};

	Texture* objectTextures[6];

	void TextureLoad();

	void CursorMove();

	void StageEdit();

	void InformationShow();

	void DefaultModeEdit();
};