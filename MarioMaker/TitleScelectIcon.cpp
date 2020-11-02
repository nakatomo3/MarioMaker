#include "TitleScelectIcon.h"
#include "DXEngine.h"

void TitleScelectIcon::Start() {
	texture = new Texture("assets/textures/MarioMaker/mario.png");
	image = gameObject->AddComponent<Image>(); 
	image->SetTexture(texture);
	image->SetScale(Vector2(SCREEN_HEIGHT / 18, SCREEN_HEIGHT / 18));
	beforeInputB = Input::GetController(0).Gamepad.wButtons & XINPUT_GAMEPAD_B;
}

void TitleScelectIcon::Update() {
	//入力周り
	Input();

	//表示箇所回り
	MovePosition();
}

void TitleScelectIcon::OnDestroy() {
	texture->Release();
}

void TitleScelectIcon::Input() {
	if (Input::GetKeyDown(VK_SPACE)) {
		SceneManager::LoadScene("タイトル");
	}

	if (abs(Input::GetController(0).Gamepad.sThumbLY) >= 10000) {
		if (abs(beforeInputLY) <= 5000) {
			isPlayMode = !isPlayMode;
		}
	}
	if (Input::GetKeyDown('W') || Input::GetKeyDown('S') || Input::GetKeyDown(VK_UP) || Input::GetKeyDown(VK_DOWN)) {
		isPlayMode = !isPlayMode;
	}

	if ((Input::GetController(0).Gamepad.wButtons & XINPUT_GAMEPAD_B || Input::GetKeyDown(VK_RETURN)) && beforeInputB == false) {
		//シーン移動
		if (isPlayMode == true) {
			SceneManager::LoadScene("選択シーン");
		} else {
			SceneManager::LoadScene("編集シーン");
		}
		return;
	}

	if (Input::GetCursorPosition().GetX() > SCREEN_HEIGHT * 0.7f && Input::GetCursorPosition().GetX() < SCREEN_HEIGHT * 0.9f) {
		if (Input::GetCursorPosition().GetY() > SCREEN_HEIGHT * 0.585f && Input::GetCursorPosition().GetY() < SCREEN_HEIGHT * 0.615f) {
			if (Input::GetMouseDown(0)) {
				//シーン移動
				SceneManager::LoadScene("編集シーン");
			}
		}
		if (Input::GetCursorPosition().GetY() > SCREEN_HEIGHT * 0.685f && Input::GetCursorPosition().GetY() < SCREEN_HEIGHT * 0.715f) {
			if (Input::GetMouseDown(0)) {
				//シーン移動
				SceneManager::LoadScene("選択シーン");
			}
		}
	}

	beforeInputB = Input::GetController(0).Gamepad.wButtons & XINPUT_GAMEPAD_B;
	beforeInputLY = Input::GetController(0).Gamepad.sThumbLY;
}

void TitleScelectIcon::MovePosition() {
	if (isPlayMode == false) {
		image->SetPosition(Vector3(SCREEN_WIDTH * 0.35f, SCREEN_HEIGHT * 0.6f, 0));
	} else {
		image->SetPosition(Vector3(SCREEN_WIDTH * 0.35f, SCREEN_HEIGHT * 0.7f, 0));
	}

}
