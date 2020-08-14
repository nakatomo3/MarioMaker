#include "TitleScelectIcon.h"
#include "DXEngine.h"

void TitleScelectIcon::Start() {
	texture = new Texture("assets/textures/MarioMaker/mario.png");
	image = gameObject->AddComponent<Image>(); 
	image->SetTexture(texture);
	image->SetScale(Vector2(SCREEN_HEIGHT / 18, SCREEN_HEIGHT / 18));
}

void TitleScelectIcon::Update() {
	//“ü—ÍŽü‚è
	Input();

	//•\Ž¦‰ÓŠ‰ñ‚è
	MovePosition();
}

void TitleScelectIcon::OnDestroy() {
	gameObject->RemoveComponent(image);
}

void TitleScelectIcon::Input() {
	if (abs(Input::GetController(0).Gamepad.sThumbLY) >= 10000) {
		if (abs(beforeInputLY) <= 5000) {
			isPlayMode = !isPlayMode;
		}
	}

	if (Input::GetController(0).Gamepad.wButtons & XINPUT_GAMEPAD_B && beforeInputB == false) {
		LogWriter::Log("input");
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
