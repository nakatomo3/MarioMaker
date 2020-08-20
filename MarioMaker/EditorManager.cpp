#include "EditorManager.h"
#include "DXEngine.h"

void EditorManager::Start() {
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
	window->SetColor(D3DXVECTOR4(1, 1, 1, 0.51f));
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

	editorWindow->SetPosition(Vector3(SCREEN_WIDTH * 0.85f, 50, 0));
	editorWindow->SetParent(gameObject);

	cursorTexture = new Texture("assets/textures/MarioMaker/Editor/Cursor.png");

	cursor = new GameObject("エディタカーソル");
	auto cursorQuad = cursor->AddComponent<Quad>();
	cursorQuad->SetTexture(cursorTexture);
	cursor->SetParent(gameObject);

	cursorPosX = 10;
}

void EditorManager::Update() {
	CursorMove();

	StageEdit();

	InformationShow();

	camera->SetPosition(Vector3((float)cursorPosX, 0.0f, -14.0f));

	beforeInputLX = Input::GetController(0).Gamepad.sThumbLX;
	beforeInputLY = Input::GetController(0).Gamepad.sThumbLY;

	beforeControllerButton = Input::GetController(0).Gamepad.wButtons;
}

void EditorManager::SetCamera(GameObject * _camera) {
	camera = _camera;
}

void EditorManager::CursorMove() {
	if (Input::GetController(0).Gamepad.sThumbLX >= 10000) {
		if (beforeInputLX < 5000) {
			cursorPosX++;
		}
		firstTimer += (float)Time::GetDeltaTime();
		if (continuousTimer >= continuousInterval) {
			cursorPosX++;
			continuousTimer = 0;
		}
	} else if (Input::GetController(0).Gamepad.sThumbLX <= -10000) {
		if (beforeInputLX > -5000) {
			cursorPosX--;
		}
		firstTimer += (float)Time::GetDeltaTime();
		if (continuousTimer >= continuousInterval) {
			cursorPosX--;
			continuousTimer = 0;
		}
	}else if (Input::GetController(0).Gamepad.sThumbLY >= 10000) {
		if (beforeInputLY < 5000) {
			cursorPosY++;
		}
		firstTimer += (float)Time::GetDeltaTime();
		if (continuousTimer >= continuousInterval) {
			cursorPosY++;
			continuousTimer = 0;
		}
	} else if (Input::GetController(0).Gamepad.sThumbLY <= -10000) {
		if (beforeInputLY > -5000) {
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
	if (cursorPosY < -7) {
		cursorPosY = -7;
	}
	if (cursorPosY > 7) {
		cursorPosY = 7;
	}

	cursor->SetPosition(Vector3((float)cursorPosX, (float)cursorPosY, -0.01f));
}

void EditorManager::StageEdit() {
	if (Input::GetController(0).Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER && !(beforeControllerButton & XINPUT_GAMEPAD_LEFT_SHOULDER)) {
		objectNumber--;
	}
	if (Input::GetController(0).Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER && !(beforeControllerButton & XINPUT_GAMEPAD_RIGHT_SHOULDER)) {
		objectNumber++;
	}
	if (objectNumber > objectMax - 1) {
		objectNumber = 0;
	}
	if (objectNumber < 0) {
		objectNumber = objectMax - 1;
	}

	if (Input::GetController(0).Gamepad.bLeftTrigger > 0x80 || Input::GetController(0).Gamepad.bRightTrigger > 0x80) {
		if (nowMode == DETAIL_MODE) {
			//詳細設定時の終了処理
		}
		nowMode = AREA_MODE;
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

		break;
	case AREA_MODE:

		break;
	case DETAIL_MODE:

		break;
	}
}

void EditorManager::InformationShow() {
	posXText->SetText(cursorPosX);
	posYText->SetText(cursorPosY + 7);
}
