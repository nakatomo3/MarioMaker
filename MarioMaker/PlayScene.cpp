#include "PlayScene.h"

PlayScene::PlayScene(string name) : Scene(name){
}

void PlayScene::Load() {
	stageManager = new GameObject("ステージマネージャー");
	stageManagerScript = stageManager->AddComponent<StageManager>();
}

void PlayScene::Start() {
	ObjectManager::Instantiate(stageManager);
}
