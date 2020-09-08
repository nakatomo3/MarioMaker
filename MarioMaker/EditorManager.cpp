#include "EditorManager.h"
#include "DXEngine.h"
#include "QuestionBlock.h"
#include "Block.h"
#include "EditScene.h"

void EditorManager::Start() {
	TextureLoad();

	auto editorWindow = new GameObject("EditorWindow");
	editorWindow->AddComponent<Window>();

	auto windowCaption = editorWindow->AddComponent<Text>();
	windowCaption->SetText("カーソル情報");
	windowCaption->SetFontSize((int)(SCREEN_HEIGHT * 0.08f));
	windowCaption->SetScale(0.5f);
	windowCaption->SetPosition(Vector3(SCREEN_HEIGHT * -0.17f, SCREEN_HEIGHT * -0.02f));

	auto windowBackground = new GameObject("EditorWindowBackground");
	auto window = windowBackground->AddComponent<Image>();
	window->SetPosition(Vector3(0, SCREEN_HEIGHT / 5.4f + SCREEN_HEIGHT * 0.025f, 0));
	window->SetColor(D3DXVECTOR4(0.66f, 0.75f, 1, 0.9f));
	window->SetScale(Vector2(SCREEN_HEIGHT / 2.7f, SCREEN_HEIGHT / 2.7f));
	windowBackground->SetParent(editorWindow);

	auto positionText = windowBackground->AddComponent<Text>();
	positionText->SetScale(0.5f);
	positionText->SetPosition(Vector3(SCREEN_HEIGHT * -0.15f, SCREEN_HEIGHT / 5.4f - SCREEN_HEIGHT * 0.15f));
	positionText->SetColor(D3DXVECTOR4(0, 0, 0, 1));
	positionText->SetFontSize((int)(SCREEN_HEIGHT * 0.08f));
	positionText->SetText("座標：\n(　　　,　　　)");

	posXText = windowBackground->AddComponent<NumText>();
	posXText->SetScale(0.5f);
	posXText->SetPosition(Vector3(SCREEN_HEIGHT * -0.1f, SCREEN_HEIGHT / 5.4f - SCREEN_HEIGHT * 0.11f));
	posXText->SetColor(D3DXVECTOR4(0, 0, 0, 1));
	posXText->SetFontSize((int)(SCREEN_HEIGHT * 0.08f));
	posXText->SetMinDigit(3);

	posYText = windowBackground->AddComponent<NumText>();
	posYText->SetScale(0.5f);
	posYText->SetPosition(Vector3(SCREEN_HEIGHT * 0.03f, SCREEN_HEIGHT / 5.4f - SCREEN_HEIGHT * 0.11f));
	posYText->SetColor(D3DXVECTOR4(0, 0, 0, 1));
	posYText->SetFontSize((int)(SCREEN_HEIGHT * 0.08f));
	posYText->SetMinDigit(3);

	nameText = windowBackground->AddComponent<Text>();
	nameText->SetScale(0.5f);
	nameText->SetPosition(Vector3(SCREEN_HEIGHT * -0.15f, SCREEN_HEIGHT / 5.4f - SCREEN_HEIGHT * 0.04f));
	nameText->SetColor(D3DXVECTOR4(0, 0, 0, 1));
	nameText->SetFontSize((int)(SCREEN_HEIGHT * 0.08f));

	editorWindow->SetPosition(Vector3(SCREEN_WIDTH * 0.85f, 50, 0));
	editorWindow->SetParent(gameObject);

	objectImage = windowBackground->AddComponent<Image>();
	objectImage->SetPosition(Vector3(SCREEN_HEIGHT * -0.07f, SCREEN_HEIGHT / 5.4f + SCREEN_HEIGHT * 0.12f, 0));
	objectImage->SetScale(Vector2(SCREEN_HEIGHT * 0.15f, SCREEN_HEIGHT * 0.15f));

	cursorTexture = new Texture("assets/textures/MarioMaker/Editor/Cursor.png");

	cursor = new GameObject("エディタカーソル");
	auto cursorQuad = cursor->AddComponent<Quad>();
	cursorQuad->SetTexture(cursorTexture);
	cursor->SetParent(gameObject);

	editingArea = new GameObject("編集エリア");
	auto areaQuad = editingArea->AddComponent<Quad>();
	areaQuad->SetColor(D3DXVECTOR4(1, 1, 0, 0.51f));
	ObjectManager::Instantiate(editingArea);

	background = new GameObject();
	auto bgQuad = background->AddComponent<Quad>();
	bgQuad->SetColor(D3DXVECTOR4(1, 1, 1, 0.51f));
	backgroundTexture = new Texture("assets/textures/MarioMaker/Editor/backGround.png");
	bgQuad->SetTexture(backgroundTexture);
	int bgScale = 20;
	background->SetScale(Vector3(2 * bgScale, 2 * bgScale, 1));
	bgQuad->SetTextureScale(bgScale, bgScale);
	background->SetPosition(Vector3(-0.5f + 20, 0.5f, 0.1f));
	ObjectManager::Instantiate(background);
}

void EditorManager::Update() {
	if (EditScene::GetIsEditMode() == true) {
		CursorMove();

		StageEdit();

		InformationShow();

		DrawBackground();

		camera->SetPosition(Vector3(cursorPosX, 7.0f, -14.0f));
	}

	beforeInputLX = Input::GetController(0).Gamepad.sThumbLX;
	beforeInputLY = Input::GetController(0).Gamepad.sThumbLY;

	beforeControllerButton = Input::GetController(0).Gamepad.wButtons;
	beforeLTrigger = Input::GetController(0).Gamepad.bLeftTrigger;
	beforeRTrigger = Input::GetController(0).Gamepad.bRightTrigger;
}

void EditorManager::SetCamera(GameObject * _camera) {
	camera = _camera;
}

void EditorManager::SetStage(StageManager * stageManager) {
	stage = stageManager;
}

Vector3 EditorManager::GetCursorPos() {
	return Vector3(cursorPosX, cursorPosY, 0);
}

void EditorManager::SetEditMode(bool isEditMode) {
	editingArea->SetActive(isEditMode);
	background->SetActive(isEditMode);
	cursor->SetActive(isEditMode);
	for (int i = 0; i < gameObject->GetChildCount(); i++) {
		gameObject->GetChild(i)->SetActive(isEditMode);
	}
}

void EditorManager::TextureLoad() {
	usedBlockTexture = new Texture("assets/textures/MarioMaker/usedBlock.png");
	objectTextures[0] = new Texture("assets/textures/MarioMaker/groundBlock.png");
	objectTextures[1] = new Texture("assets/textures/MarioMaker/block.png");
	objectTextures[2] = new Texture("assets/textures/MarioMaker/hatenaBlock.png");
	objectTextures[3] = new Texture("assets/textures/MarioMaker/standBlock.png");
}

void EditorManager::CursorMove() {
	if (Input::GetController(0).Gamepad.sThumbLX >= 10000 || Input::GetKey('D')) {
		if ((beforeInputLX < 5000 && !Input::GetKey('D')) || Input::GetKeyDown('D')) {
			cursorPosX++;
		}
		firstTimer += (float)Time::GetDeltaTime();
		if (continuousTimer >= continuousInterval) {
			cursorPosX++;
			continuousTimer = 0;
		}
	} else if (Input::GetController(0).Gamepad.sThumbLX <= -10000 || Input::GetKey('A')) {
		if ((beforeInputLX > -5000 && !Input::GetKey('A')) || Input::GetKeyDown('A')) {
			cursorPosX--;
		}
		firstTimer += (float)Time::GetDeltaTime();
		if (continuousTimer >= continuousInterval) {
			cursorPosX--;
			continuousTimer = 0;
		}
	}else if (Input::GetController(0).Gamepad.sThumbLY >= 10000 || Input::GetKey('W')) {
		if ((beforeInputLY < 5000 && !Input::GetKey('W')) || Input::GetKeyDown('W')) {
			cursorPosY++;
		}
		firstTimer += (float)Time::GetDeltaTime();
		if (continuousTimer >= continuousInterval) {
			cursorPosY++;
			continuousTimer = 0;
		}
	} else if (Input::GetController(0).Gamepad.sThumbLY <= -10000 || Input::GetKey('S')) {
		if ((beforeInputLY > -5000 && !Input::GetKey('S')) || Input::GetKeyDown('S')) {
			cursorPosY--;
		}
		firstTimer += (float)Time::GetDeltaTime();
		if (continuousTimer >= continuousInterval) {
			cursorPosY--;
			continuousTimer = 0;
		}
	} else {
		firstTimer = 0;
		continuousTimer = 0;
	}
	if (firstTimer >= firstInterval) {
		continuousTimer += (float)Time::GetDeltaTime();
	}

	//範囲制限
	if (cursorPosX < 0) {
		cursorPosX = 0;
	}
	if (cursorPosY < 0) {
		cursorPosY = 0;
	}
	if (cursorPosY > 14) {
		cursorPosY = 14;
	}

	cursor->SetPosition(Vector3((float)cursorPosX, (float)cursorPosY, -0.01f));
}

void EditorManager::StageEdit() {
	if (Input::GetController(0).Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER && !(beforeControllerButton & XINPUT_GAMEPAD_LEFT_SHOULDER) || Input::GetMouseWheel() > 0) {
		objectNumber--;
	}
	if (Input::GetController(0).Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER && !(beforeControllerButton & XINPUT_GAMEPAD_RIGHT_SHOULDER) || Input::GetMouseWheel() < 0) {
		objectNumber++;
	}
	if (objectNumber > objectMax - 1) {
		objectNumber = 0;
	}
	if (objectNumber < 0) {
		objectNumber = objectMax - 1;
	}

	if ((Input::GetController(0).Gamepad.bLeftTrigger > 0x80 && beforeLTrigger < 0x80) || (Input::GetController(0).Gamepad.bRightTrigger > 0x80 && beforeRTrigger < 0x80)) {
		if (nowMode == DETAIL_MODE) {
			//詳細設定時の終了処理
		}
		nowMode = AREA_MODE;
		editingArea->SetPosition(Vector3((float)cursorPosX, (float)cursorPosY, -0.01f));
		editingArea->SetActive(true);
		areaStartPosX = cursorPosX;
		areaStartPosY = cursorPosY;
	}
	if (Input::GetController(0).Gamepad.bLeftTrigger < 0x80 && Input::GetController(0).Gamepad.bRightTrigger < 0x80) {
		if (nowMode == AREA_MODE) {

		}
		nowMode = DEFAULT_MODE;
		editingArea->SetActive(false);
	}
	if (Input::GetController(0).Gamepad.wButtons & XINPUT_GAMEPAD_X) {
		if (nowMode == AREA_MODE) {
			//エリア編集時の終了処理
		}
		nowMode = DETAIL_MODE;
	}

	switch (nowMode) {
	default:
		break;
	case DEFAULT_MODE:
		DefaultModeEdit();
		break;
	case AREA_MODE:
		editingArea->SetPosition(Vector3(((float)cursorPosX + areaStartPosX) / 2, ((float)cursorPosY + areaStartPosY) / 2, -0.01f));
		editingArea->SetScale(Vector3(abs(areaStartPosX - cursorPosX) + 1, abs(areaStartPosY - cursorPosY) + 1, 1));
		AreaModeEdit();
		break;
	case DETAIL_MODE:

		break;
	}
}

void EditorManager::InformationShow() {
	posXText->SetText(cursorPosX);
	posYText->SetText(cursorPosY);
	nameText->SetText(objectNames[objectNumber].c_str());

	if (objectTextures[objectNumber] != nullptr) {
		objectImage->SetTexture(objectTextures[objectNumber]);
	}
}

void EditorManager::DestroyObject(int x, int y) {

	//地形ブロックを置いたとき、一番下層部なら自動的に地面も消す
	if (stage->GetStageObject(x, y) == objectNumber + 'A' && stage->GetChildGameObject(Vector3((float)x, (float)y - 1, 0)) != nullptr && y == 0) {
		stage->GetChildGameObject(Vector3((float)x, (float)y - 1, 0))->Destroy();
	}
	if (stage->GetChildGameObject(Vector3((float)x, (float)y, 0)) != nullptr) {
		stage->GetChildGameObject(Vector3((float)x, (float)y, 0))->Destroy();
	}
	stage->SetObject(x, y, '0');

}

void EditorManager::PlaceObject(int x, int y) {
	auto stageObj = new GameObject();
	stageObj->SetParent(stage->GetGameObject());
	auto quad = stageObj->AddComponent<Quad>();
	switch (objectNumber) {
	default:
		break;
	case 0:
		stageObj->SetName("地形ブロック");
		stageObj->SetTag(GROUND_BLOCK);
		stageObj->SetPosition(Vector3((float)x, (float)y, 0));
		stageObj->AddComponent<QuadCollider>();
		quad->SetTexture(objectTextures[0]);
		stage->SetObject(x, y, 'A');

		if (y == 0) {
			auto underStageBlock = new GameObject();
			underStageBlock->SetParent(stage->GetGameObject());
			auto quad = underStageBlock->AddComponent<Quad>();
			underStageBlock->SetName("地形ブロック");
			underStageBlock->SetTag(GROUND_BLOCK);
			underStageBlock->SetPosition(Vector3((float)x, (float)y - 1, 0));
			underStageBlock->AddComponent<QuadCollider>();
			quad->SetTexture(objectTextures[0]);
			ObjectManager::Instantiate(underStageBlock);
		}
		break;
	case 1:
		stageObj->SetName("ブロック");
		stageObj->SetTag(BLOCK);
		stageObj->AddComponent<Block>();
		stageObj->SetPosition(Vector3((float)x, (float)y, 0));
		stageObj->AddComponent<QuadCollider>();
		quad->SetTexture(objectTextures[1]);
		stage->SetObject(x, y, 'B');
		break;
	case 2:
		stageObj->SetName("ハテナブロック");
		stageObj->SetTag(HATENA_BLOCK);
		stageObj->SetPosition(Vector3((float)x, (float)y, 0));
		stageObj->AddComponent<QuadCollider>();
		quad->SetTexture(objectTextures[2]);
		stage->SetObject(x, y, 'C');
		{
			auto hatena = stageObj->AddComponent<QuestionBlock>();
			hatena->SetUsedBlock(usedBlockTexture);
		}
		break;
	case 3:
		stageObj->SetName("足場ブロック");
		stageObj->SetTag(GROUND_BLOCK);
		stageObj->SetPosition(Vector3((float)x, (float)y, 0));
		stageObj->AddComponent<QuadCollider>();
		quad->SetTexture(objectTextures[3]);
		stage->SetObject(x, y, 'D');
		break;
	}
	ObjectManager::Instantiate(stageObj);
}

void EditorManager::DefaultModeEdit() {
	if (Input::GetController(0).Gamepad.wButtons & XINPUT_GAMEPAD_A || Input::GetKey('K')) {
		DestroyObject(cursorPosX, cursorPosY);
	}

	if (Input::GetController(0).Gamepad.wButtons & XINPUT_GAMEPAD_B || Input::GetKey('L')) {
		if (stage->GetStageObject(cursorPosX, cursorPosY) != objectNumber + 'A') {
			DestroyObject(cursorPosX, cursorPosY);
			PlaceObject(cursorPosX, cursorPosY);
		}
	}
}

void EditorManager::AreaModeEdit() {
	int left = 0;
	int up = 0;

	//左上の座標を求める
	if (cursorPosX >= areaStartPosX) {
		left = areaStartPosX;
	} else {
		left = cursorPosX;
	}
	if (cursorPosY >= areaStartPosY) {
		up = areaStartPosY;
	} else {
		up = cursorPosY;
	}

	//左上から右下まで消す
	if (Input::GetController(0).Gamepad.wButtons & XINPUT_GAMEPAD_A || Input::GetKeyDown('K')) {
		for (int i = 0; i < abs(areaStartPosX - cursorPosX) + 1; i++) {
			for (int j = 0; j < abs(areaStartPosY - cursorPosY) + 1; j++) {
				DestroyObject(i + left, j + up);
			}
		}
	}

	//左上から右下まで消した後に置く
	if (Input::GetController(0).Gamepad.wButtons & XINPUT_GAMEPAD_B || Input::GetKey('L')) {
		for (int i = 0; i < abs(areaStartPosX - cursorPosX) + 1; i++) {
			for (int j = 0; j < abs(areaStartPosY - cursorPosY) + 1; j++) {
				DestroyObject(i + left, j + up);
				PlaceObject(i + left, j + up);
			}
		}
	}
}

void EditorManager::DrawBackground() {
	background->SetPosition(Vector3(-0.5f + 20, 0.5f, 0.1f));
}
