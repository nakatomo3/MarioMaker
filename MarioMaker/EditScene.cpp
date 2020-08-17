#include "EditScene.h"
#include "DXEngine.h"
#include "Player.h"

EditScene::EditScene(string name) : Scene(name){

}

void EditScene::Start() {
	ObjectManager::Instantiate(camera);
	ObjectManager::Instantiate(player);
}

void EditScene::Load() {
	playerTexture = new Texture("assets/textures/MarioMaker/mario.png");

	camera = new GameObject("カメラ");
	camera->AddComponent<Camera>();
	camera->SetPosition(Vector3(0,0,-14));

	player = new GameObject("プレイヤー");
	auto playerQuad = player->AddComponent<Quad>();
	playerQuad->SetTexture(playerTexture);
	playerQuad->SetCull(false);
	auto playerScript = player->AddComponent<Player>();
	playerScript->SetQuad(playerQuad);

}

void EditScene::Update() {
	if (Input::GetController(0).Gamepad.wButtons & XINPUT_GAMEPAD_START && beforeInputStart == false) {
		isEditMode = !isEditMode;
	}
	if (isEditMode == true) {
		player->SetActive(false);
	} else {
		player->SetActive(true);
	}

	beforeInputStart = Input::GetController(0).Gamepad.wButtons & XINPUT_GAMEPAD_START;
}
