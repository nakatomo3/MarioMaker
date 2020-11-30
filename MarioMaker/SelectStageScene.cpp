#include "SelectStageScene.h"
#include "StageSelectManager.h"

SelectStageScene::SelectStageScene(string name) : Scene(name) {

}

void SelectStageScene::Start() {
	manager = new GameObject("StageSelectManager");
	manager->AddComponent<StageSelectManager>();
	ObjectManager::Instantiate(manager);
}

void SelectStageScene::Load() {
}

void SelectStageScene::Update() {

}