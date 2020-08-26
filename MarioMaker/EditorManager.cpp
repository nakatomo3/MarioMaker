#include "EditorManager.h"
#include "DXEngine.h"
#include "QuestionBlock.h"
#include "Block.h"

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

	TextureLoad();
}

void EditorManager::Update() {
	CursorMove();

	StageEdit();

	InformationShow();

	camera->SetPosition(Vector3(cursorPosX, 7.0f, -14.0f));

	beforeInputLX = Input::GetController(0).Gamepad.sThumbLX;
	beforeInputLY = Input::GetController(0).Gamepad.sThumbLY;

	beforeControllerButton = Input::GetController(0).Gamepad.wButtons;
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
		DefaultModeEdit();
		break;
	case AREA_MODE:

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

void EditorManager::DefaultModeEdit() {
	if (Input::GetController(0).Gamepad.wButtons & XINPUT_GAMEPAD_A || Input::GetKey('K')) {
		//地形ブロックを置いたとき、一番下層部なら自動的に地面も消す
		if (stage->GetStageObject(cursorPosX, cursorPosY) == objectNumber + 'A' && stage->GetChildGameObject(Vector3((float)cursorPosX, (float)cursorPosY - 1, 0)) != nullptr && cursorPosY == 0) {
			stage->GetChildGameObject(Vector3((float)cursorPosX, (float)cursorPosY - 1, 0))->Destroy();
		}
		if (stage->GetChildGameObject(Vector3((float)cursorPosX, (float)cursorPosY, 0)) != nullptr) {
			stage->GetChildGameObject(Vector3((float)cursorPosX, (float)cursorPosY, 0))->Destroy();
		}
		stage->SetObject(cursorPosX, cursorPosY, '0');
	}
	if (Input::GetController(0).Gamepad.wButtons & XINPUT_GAMEPAD_B || Input::GetKey('L')) {
		if (stage->GetStageObject(cursorPosX, cursorPosY) != objectNumber + 'A') {
			if (stage->GetChildGameObject(Vector3((float)cursorPosX, (float)cursorPosY, 0)) != nullptr) {
				stage->GetChildGameObject(Vector3((float)cursorPosX, (float)cursorPosY, 0))->Destroy();
			}

			auto stageObj = new GameObject();
			stageObj->SetParent(stage->GetGameObject());
			auto quad = stageObj->AddComponent<Quad>();
			ObjectManager::Instantiate(stageObj);
			switch (objectNumber) {
			default:
				break;
			case 0:
				stageObj->SetName("地形ブロック");
				stageObj->SetTag(GROUND_BLOCK);
				stageObj->SetPosition(Vector3((float)cursorPosX, (float)cursorPosY, 0));
				stageObj->AddComponent<QuadCollider>();
				quad->SetTexture(objectTextures[0]);
				stage->SetObject(cursorPosX, cursorPosY, 'A');

				if (cursorPosY == 0) {
					auto underStageBlock = new GameObject();
					underStageBlock->SetParent(stage->GetGameObject());
					auto quad = underStageBlock->AddComponent<Quad>();
					underStageBlock->SetName("地形ブロック");
					underStageBlock->SetTag(GROUND_BLOCK);
					underStageBlock->SetPosition(Vector3((float)cursorPosX, (float)cursorPosY - 1, 0));
					underStageBlock->AddComponent<QuadCollider>();
					quad->SetTexture(objectTextures[0]);
					ObjectManager::Instantiate(underStageBlock);
				}
				break;
			case 1:
				stageObj->SetName("ブロック");
				stageObj->SetTag(BLOCK);
				stageObj->AddComponent<Block>();
				stageObj->SetPosition(Vector3((float)cursorPosX, (float)cursorPosY, 0));
				stageObj->AddComponent<QuadCollider>();
				quad->SetTexture(objectTextures[1]);
				stage->SetObject(cursorPosX, cursorPosY, 'B');
				break;
			case 2:
				stageObj->SetName("ハテナブロック");
				stageObj->SetTag(HATENA_BLOCK);
				stageObj->SetPosition(Vector3((float)cursorPosX, (float)cursorPosY, 0));
				stageObj->AddComponent<QuadCollider>();
				quad->SetTexture(objectTextures[2]);
				stage->SetObject(cursorPosX, cursorPosY, 'C'); 
				{
					auto hatena = stageObj->AddComponent<QuestionBlock>();
					hatena->SetUsedBlock(usedBlockTexture);
				}
				break;
			case 3:
				stageObj->SetName("足場ブロック");
				stageObj->SetTag(GROUND_BLOCK);
				stageObj->SetPosition(Vector3((float)cursorPosX, (float)cursorPosY, 0));
				stageObj->AddComponent<QuadCollider>();
				quad->SetTexture(objectTextures[3]);
				stage->SetObject(cursorPosX, cursorPosY, 'D');
				break;
			}
		}
	}
}