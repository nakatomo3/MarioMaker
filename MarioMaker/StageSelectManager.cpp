#define _CRT_SECURE_NO_WARNINGS
#include "DXEngine.h"
#include "StageSelectManager.h"

void StageSelectManager::Start() {
	cursor = new GameObject("カーソル");
	auto image = cursor->AddComponent<Image>();
	auto texture = new Texture("assets/textures/MarioMaker/mario.png");
	image->SetTexture(texture);
	image->SetScale(Vector2(50, 50));
	ObjectManager::Instantiate(cursor);

	ReadStageFiles();

	SetStageFiles();
}

void StageSelectManager::Update() {
	if (beforeCursorPos != Input::GetCursorPosition()) {
		isMouseMode = true;
	}

	if (Input::GetController(0).Gamepad.sThumbLY != 0) {
		isMouseMode = false;
	}

	if (isMouseMode == true) {
		MouseMode();
	} else {
		ControllerMode();
	}

	cursor->SetPosition(Vector3(-SCREEN_WIDTH * 0.45, (cursorPos - 2.5) * SCREEN_WIDTH / 9.6 + SCREEN_WIDTH * 0.04));

	beforeCursorPos = Input::GetCursorPosition();
	beforeController = Input::GetController(0).Gamepad;
}

void StageSelectManager::ReadStageFiles() {
	fileNames.clear();

	HANDLE hFind;
	WIN32_FIND_DATA win32fd;
	std::string search_name = folderPath + "\\*";

	hFind = FindFirstFile(search_name.c_str(), &win32fd);

	if (hFind == INVALID_HANDLE_VALUE) {
		LogWriter::Log("ファイルが見つかりませんでした");
		return;
	}

	/* 指定のディレクトリ以下のファイル名をファイルがなくなるまで取得する */
	do {
		if (win32fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
			/* ディレクトリの場合は何もしない */
		} else {
			/* ファイルが見つかったらVector配列に保存する */
			fileNames.push_back(win32fd.cFileName);
			//LogWriter::Log("path:%s", win32fd.cFileName);
		}
	} while (FindNextFile(hFind, &win32fd));

	FindClose(hFind);
}

void StageSelectManager::SetStageFiles() {
	for (unsigned int i = 0; i < stageLists.size(); i++) {
		stageLists[i]->Destroy();
	}
	stageLists.clear();

	for (unsigned int i = 0; i < fileNames.size(); i++) {
		if (fileNames[i].find(".stage") == std::string::npos) {
			LogWriter::Log(".stage以外のファイルが見つかりました");
			continue;
		}
		auto stageFile = fopen((folderPath + fileNames[i]).c_str() , "r");

		auto stage = new GameObject(fileNames[i]);

		auto stageWindow = stage->AddComponent<Image>();
		stageWindow->SetScale(Vector2(SCREEN_WIDTH * 0.8, SCREEN_WIDTH * 0.09));
		stageWindow->SetColor(D3DXVECTOR4(0, 0, 0, 1));
		stageWindow->SetPosition(Vector3(SCREEN_CENTER_X * 3 / 4, 0));

		auto text = stage->AddComponent<Text>();
		auto nameLength = fileNames[i].find(".");
		text->SetText(fileNames[i].replace(nameLength, 8, "").c_str());
		stageLists.emplace_back(stage);
		text->SetPosition(Vector3(0, -SCREEN_WIDTH / 30));
		
		StageType type;
		char typeBuf;
		fread(&typeBuf, sizeof(char), 1, stageFile);
		type = (StageType)(typeBuf - '0');
		auto stageTypeText = stage->AddComponent<Text>();
		stageTypeText->SetPosition(Vector3(SCREEN_CENTER_X * 3 / 4, -SCREEN_WIDTH / 60, 0));
		stageTypeText->SetFontSize(SCREEN_WIDTH / 30);

		switch (type) {
		default:
			break;
		case NORMAL:
			stageTypeText->SetText("地上 サイズ：");
			break;
		case UNDER_GROUND:
			stageTypeText->SetText("地下 サイズ：");
			break;
		case WATER:
			stageTypeText->SetText("水中 サイズ：");
			break;
		case CASTLE:
			stageTypeText->SetText("城　 サイズ：");
			break;
		}

		int size = 0;
		char sizeBuf = 0;
		fread(&typeBuf, sizeof(char), 1, stageFile);	//この位置に改行コードが入っているので一回空読みする
		while (sizeBuf != '\n') {
			fread(&sizeBuf, sizeof(char), 1, stageFile);
			if (sizeBuf >= '0' && sizeBuf < '9') {
				size = size * 10 + (sizeBuf - '0');
			}
		}
		auto stageSizeText = stage->AddComponent<NumText>();
		stageSizeText->SetFontSize(SCREEN_WIDTH / 30);
		stageSizeText->SetText(size);
		stageSizeText->SetPosition(Vector3(Vector3(SCREEN_CENTER_X * 1.2, -SCREEN_WIDTH / 60, 0)));
		
		stage->SetPosition(Vector3(SCREEN_CENTER_X / 4.0, i * SCREEN_WIDTH / 9.6 + SCREEN_WIDTH * 0.05));

		fclose(stageFile);
		ObjectManager::Instantiate(stage);
	}
}

void StageSelectManager::MouseMode() {
	dragRange = Input::GetMouseWheel();
	Drag();

	cursorPos = (int)floor(Input::GetCursorPosition().GetY() / (SCREEN_WIDTH / 9.6));
	if (cursorPos < 0) {
		cursorPos = 0;
	}
	if (cursorPos > 4) {
		cursorPos = 4;
	}
	if (cursorPos > fileNames.size() - 2) {
		cursorPos = fileNames.size() - 2;
	}
}

void StageSelectManager::Drag() {
	//if (stageLists.size() > 5) {
		if (dragRange != 0) {
			if (stageLists[0]->GetPosition().GetY() <= SCREEN_WIDTH * 0.14 && dragRange < 0) {
				dragRange = 0;
			}
			if (stageLists[stageLists.size() - 1]->GetPosition().GetY() >= SCREEN_HEIGHT * 0.8 && dragRange > 0) {
				dragRange = 0;
			}
			if (dragRange != 0) {
				dragTimer += Time::GetDeltaTime();
			}
			if (dragTimer > 0.1) {
				dragTimer = 0;
			} else {
				dragRange = 0;
			}
			if (dragRange != 0) {
				for (unsigned int i = 0; i < stageLists.size(); i++) {
					stageLists[i]->Move(Vector3(0, SCREEN_WIDTH / 9.6 * dragRange / abs(dragRange), 0));
				}
			}
		}
	//}
}

void StageSelectManager::ControllerMode() {
	//if (Input::GetController(0).Gamepad.sThumbLY > 0) {
	//	dragRange = 1;
	//}
	//if (Input::GetController(0).Gamepad.sThumbLY < 0) {
	//	dragRange = -1;
	//}
	if (abs(beforeController.sThumbLY) < 5000) {
		if (Input::GetController(0).Gamepad.sThumbLY > 10000) {
			cursorPos--;
		}
		if (Input::GetController(0).Gamepad.sThumbLY < -10000) {
			cursorPos++;
		}
	}
	if (cursorPos < 0) {
		cursorPos = 0;
	}
	if (cursorPos > 4) {
		cursorPos = 4;
	}
	if (cursorPos > fileNames.size() - 2) {
		cursorPos = fileNames.size() - 2;
	}

	if (!(beforeController.wButtons & XINPUT_GAMEPAD_B) && Input::GetController(0).Gamepad.wButtons & XINPUT_GAMEPAD_B){
		StageManager::SetStagePath(folderPath + fileNames[cursorPos] + ".stage");
		SceneManager::LoadScene("プレイシーン");
	}
	//Drag();
}
