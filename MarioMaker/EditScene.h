#pragma once
#include "Scene.h"
#include "Texture.h"
#include "EditorManager.h"
#include "StageManager.h"
class EditScene : public Scene {
public:
	EditScene(string name);

	void Start();
	void Load();
	void Unload();

	void Update();
	static bool GetIsEditMode();
	static bool GetIsPauseMode();

private:

	void PauseAction();

	StageManager* stageManager;

	GameObject* editorObject;
	GameObject* gameObject;
	GameObject* stage;

	//ゲーム部分オブジェクト
	GameObject* player;
	GameObject* camera;

	//編集オブジェクト
	GameObject* editorWindow;
	GameObject* editorCamera;

	EditorManager* editorManager;

	//ポーズウィンドウ
	GameObject* pauseWindow;
	GameObject* pauseCursor;
	Texture* pauseWindowTexture;

	Texture* playerTexture;
	Texture* blockTexture;

	static bool isEditMode;
	WORD beforeControllerInput;
	SHORT beforeLY;

	static bool isPauseMode;
	int pauseCursorPos;

};