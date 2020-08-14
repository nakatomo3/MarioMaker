#include "TitleScelectIcon.h"
#include "DXEngine.h"

void TitleScelectIcon::Start() {
	texture = new Texture("assets/textures/MarioMaker/mario.png");
	image = gameObject->AddComponent<Image>(); 
	image->SetTexture(texture);
	LogWriter::Log("hoge");
}

void TitleScelectIcon::Update() {
	if (abs(Input::GetController(0).Gamepad.sThumbLY) >= 20000) {
		if (abs(beforeInputLY) <= 5000) {
			isPlayMode = !isPlayMode;
		}
	}
	beforeInputLY = Input::GetController(0).Gamepad.sThumbLY;
}

void TitleScelectIcon::OnDestroy() {
}
