#include "PlayScene.h"
#include "Camera.h"
#include "DXEngine.h"
#include "PlayerCamera.h"

bool PlayScene::isPlayMode;

PlayScene::PlayScene(string name) : Scene(name){
}

void PlayScene::Load() {
	stageManager = new GameObject("ステージマネージャー");
	stageManagerScript = stageManager->AddComponent<StageManager>();

	playerTexture = new Texture("assets/textures/MarioMaker/mario.png");

	player = new GameObject("プレイヤー");
	player->SetTag(PLAYER);
	auto playerQuad = player->AddComponent<Quad>();
	playerQuad->SetTexture(playerTexture);
	playerQuad->SetCull(false);
	player->SetPosition(Vector3(10, 3, 0));
	playerScript = player->AddComponent<Player>();
	player->AddComponent<QuadCollider>();

	camera = new GameObject("カメラ");
	camera->AddComponent<Camera>();
	auto cameraScript = camera->AddComponent<PlayerCamera>();
	camera->SetPosition(Vector3(14, 7, -14));

	cameraScript->SetPlayer(player);

	
}

void PlayScene::Start() {
	ObjectManager::Instantiate(stageManager);
	ObjectManager::Instantiate(camera);

	ObjectManager::Instantiate(player);

	isPlayMode = true;
}

bool PlayScene::isPlayScene() {
	return isPlayMode;
}
