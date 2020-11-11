#include "EditScene.h"
#include "DXEngine.h"
#include "Player.h"
#include "PlayerCamera.h"
#include "EditorManager.h"
#include "StageManager.h"

bool EditScene::isEditMode;
bool EditScene::isPauseMode;

EditScene::EditScene(string name) : Scene(name){
	isEditMode = true;
}

void EditScene::Start() {
	ObjectManager::Instantiate(player);
	ObjectManager::Instantiate(stage);
	int width = 20;
	for (int i = 0; i < width; i++) {
		stageManager->SetObject(i, 0, 'A');
	}
	beforeControllerInput = Input::GetController(0).Gamepad.wButtons;
	beforeLY = Input::GetController(0).Gamepad.sThumbLY;
	isPauseMode = false;
	pauseCursorPos = 0;
}

void EditScene::Load() {

	playerTexture = new Texture("assets/textures/MarioMaker/mario.png");
	blockTexture = new Texture("assets/textures/MarioMaker/groundBlock.png");

	stage = new GameObject("ステージ");
	stageManager = stage->AddComponent<StageManager>();
	stage->SetTag(MANAGER);

	editorObject = new GameObject("エディタオブジェクト");
	editorObject->SetParent(stage);
	editorObject->SetTag(MANAGER);
	gameObject = new GameObject("ゲーム部分オブジェクト");
	gameObject->SetParent(stage);
	gameObject->SetTag(MANAGER);

	//ゲーム部分オブジェクト
	player = new GameObject("プレイヤー");
	player->SetTag(PLAYER);
	auto playerQuad = player->AddComponent<Quad>();
	playerQuad->SetTexture(playerTexture);
	playerQuad->SetCull(false);
	player->SetPosition(Vector3(10,3,0));
	playerScript = player->AddComponent<Player>();
	player->AddComponent<QuadCollider>();

	camera = new GameObject("カメラ");
	camera->AddComponent<Camera>();
	camera->AddComponent<PlayerCamera>()->SetPlayer(player);
	camera->SetParent(gameObject);

	//編集オブジェクト
	editorManager = editorObject->AddComponent<EditorManager>();
	editorManager->SetStage(stageManager);

	editorCamera = new GameObject("エディタカメラ");
	editorCamera->AddComponent<Camera>();
	editorCamera->SetPosition(Vector3(0, 7, -14));
	editorCamera->SetParent(editorObject);
	editorManager->SetCamera(editorCamera);

	//ポーズオブジェクト
	pauseWindow = new GameObject("ポーズウィンドウ");
	auto pauseWindowImage = pauseWindow->AddComponent<Image>();
	ObjectManager::Instantiate(pauseWindow);
	pauseWindowImage->SetScale(Vector2(SCREEN_WIDTH * 0.4f, SCREEN_HEIGHT * 0.5f));
	pauseWindowTexture = new Texture("assets/textures/MarioMaker/Editor/PauseWindow.png");
	pauseWindowImage->SetTexture(pauseWindowTexture);

	pauseCursor = new GameObject("ポーズカーソル");
	auto pauseCursorImage = pauseCursor->AddComponent<Image>();
	ObjectManager::Instantiate(pauseCursor);
	pauseCursorImage->SetScale(Vector2(SCREEN_WIDTH * 0.03f, SCREEN_WIDTH * 0.03f));
	pauseCursorImage->SetTexture(playerTexture);
	pauseCursor->SetParent(pauseWindow);

	//デフォルトで最低限のブロックを置いておく
	int width = 20;
	for (int i = 0; i < width; i++) {
		auto block = new GameObject("地形ブロック");
		block->SetTag(GROUND_BLOCK);
		block->SetPosition(Vector3((float)i, 0, 0));
		block->AddComponent<Quad>()->SetTexture(blockTexture);
		block->AddComponent<QuadCollider>();
		block->SetParent(stage);
	}
	for (int i = 0; i < width; i++) {
		auto block = new GameObject("地形ブロック");
		block->SetTag(GROUND_BLOCK);
		block->SetPosition(Vector3((float)i, -1, 0));
		block->AddComponent<Quad>()->SetTexture(blockTexture);
		block->AddComponent<QuadCollider>();
		block->SetParent(stage);
	}
}

void EditScene::Unload() {
	playerTexture->Release();
	blockTexture->Release();
	pauseWindowTexture->Release();
}

void EditScene::Update() {
	if (Input::GetController(0).Gamepad.wButtons & XINPUT_GAMEPAD_BACK && !(beforeControllerInput & XINPUT_GAMEPAD_BACK)) {
		isEditMode = !isEditMode;
		isPauseMode = false;
	}
	if (Input::GetController(0).Gamepad.wButtons & XINPUT_GAMEPAD_START && !(beforeControllerInput & XINPUT_GAMEPAD_START) || Input::GetKeyDown(VK_RETURN)) {
		if (isEditMode == false) {
			isEditMode = true;
			isPauseMode = false;
		} else {
			isPauseMode = !isPauseMode;
		}
	}

	if (isEditMode == true) {
		gameObject->SetActive(false);
		editorManager->SetEditMode(true);
		player->SetActive(false);
		if (isPauseMode == true) {
			pauseWindow->SetActive(true);
			PauseAction();
		} else {
			pauseWindow->SetActive(false);
		}
	} else {
		if (player->GetActive() == false) {
			player->SetPosition(editorManager->GetCursorPos());
		}
		player->SetActive(true);
		gameObject->SetActive(true);
		editorManager->SetEditMode(false);
		pauseWindow->SetActive(false);
	}

	beforeControllerInput = Input::GetController(0).Gamepad.wButtons;
	beforeLY = Input::GetController(0).Gamepad.sThumbLY;
}

bool EditScene::GetIsEditMode() {
	return isEditMode;
}

bool EditScene::GetIsPauseMode() {
	return isPauseMode;
}

void EditScene::PauseAction() {
	switch (pauseCursorPos) {
	case 0:
		if (Input::GetController(0).Gamepad.wButtons & XINPUT_GAMEPAD_B) {
			isEditMode = false;
			isPauseMode = false;
		}
		pauseCursor->SetPosition(Vector3(-140,-58,0));
		break;
	case 1:
		pauseCursor->SetPosition(Vector3(-140, -8, 0));
		if (Input::GetController(0).Gamepad.wButtons & XINPUT_GAMEPAD_B && !(beforeControllerInput & XINPUT_GAMEPAD_BACK)) {
			stageManager->SaveStage("Stages/Stage.txt");
		}
		break;
	case 2:
		if (Input::GetController(0).Gamepad.wButtons & XINPUT_GAMEPAD_B || Input::GetKeyDown('P')) {
			SceneManager::LoadScene("タイトル");
		}
		pauseCursor->SetPosition(Vector3(-140, 42, 0));
		break;
	case 3:
		pauseCursor->SetPosition(Vector3(-140, 92, 0));
		break;
	default:
		break;
	}

	if (Input::GetController(0).Gamepad.sThumbLY > 10000 && beforeLY < 5000) {
		pauseCursorPos--;
	}
	if (Input::GetController(0).Gamepad.sThumbLY < -10000 && beforeLY > -5000) {
		pauseCursorPos++;
	}
	pauseCursorPos = (pauseCursorPos + 4) % 4;

	if (Input::GetController(0).Gamepad.wButtons & XINPUT_GAMEPAD_A && !(beforeControllerInput & XINPUT_GAMEPAD_A)) {
		isPauseMode = false;
	}
}
