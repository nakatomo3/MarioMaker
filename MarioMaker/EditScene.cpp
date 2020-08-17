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
	auto blockTexture = new Texture("assets/textures/MarioMaker/groundBlock.png");

	camera = new GameObject("カメラ");
	camera->AddComponent<Camera>();
	camera->SetPosition(Vector3(0,0,-14));

	player = new GameObject("プレイヤー");
	auto playerQuad = player->AddComponent<Quad>();
	playerQuad->SetTexture(playerTexture);
	playerQuad->SetCull(false);
	auto playerScript = player->AddComponent<Player>();
	playerScript->SetQuad(playerQuad);
	player->AddComponent<QuadCollider>();

	int width = 20;
	for (int i = 0; i < width; i++) {
		auto block = new GameObject("ブロック");
		block->SetPosition(Vector3(i - width / 2, -7, 0));
		block->AddComponent<Quad>()->SetTexture(blockTexture);
		block->AddComponent<QuadCollider>();
		ObjectManager::Instantiate(block);
	}

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
