#include "StageManager.h"

GameObject * StageManager::GetChildGameObject(Vector3 pos) {
	GameObject* obj = nullptr;
	auto childCount = gameObject->GetChildCount();
	for (int i = 0; i < childCount; i++) {
		if (gameObject->GetChild(i)->GetPosition() == pos) {
			if (gameObject->GetChild(i)->GetTag() != MANAGER) {
				obj = gameObject->GetChild(i);
				break;
			}
		}
	}
	return obj;
}
