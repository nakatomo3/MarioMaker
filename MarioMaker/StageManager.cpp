#include "StageManager.h"

void StageManager::Start() {
	for (int i = 0; i < 14; i++) {
		stage.emplace_back();
		for (int j = 0; j < stageSizeX; j++) {
			stage[i].emplace_back('0');
		}
	}
}

GameObject * StageManager::GetChildGameObject(Vector3 pos) {
	GameObject* obj = nullptr;
	auto childCount = gameObject->GetChildCount();
	for (unsigned int i = 0; i < childCount; i++) {
		if (gameObject->GetChild(i)->GetPosition() == pos) {
			if (gameObject->GetChild(i)->GetTag() != MANAGER) {
				obj = gameObject->GetChild(i);
				break;
			}
		}
	}
	return obj;
}

void StageManager::SetStageSize(unsigned int size) {
	stageSizeX = size;
}

int StageManager::GetStageSize() {
	return stageSizeX;
}

void StageManager::SetObject(int x, int y, char obj) {
	stage[y][x] = obj;
}

char StageManager::GetStageObject(int x, int y) {
	return stage[y][x];
}
