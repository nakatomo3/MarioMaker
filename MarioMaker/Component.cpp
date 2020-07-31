#include "Component.h"
#include "LogWriter.h"
#include "GameObject.h"

#include "Collider.h"
#include "CollisionManager.h"

Component::Component() {}


Component::~Component() {}

GameObject* Component::GetGameObject() {
	return gameObject;
}

void Component::SetGameObject(GameObject* _gameObject) {
	gameObject = _gameObject;
}

void Component::SetActive(bool active) {
	if (active == true) {
		if (isActive == false) {
			OnEnabled();
		}
	} else {
		if (isActive == true) {
			OnDisabled();
		}
	}
	isActive = active;
}

void Component::Destroy() {
	this->OnDestroy();
	if (gameObject == nullptr) {
		LogWriter::LogWorning("ゲームオブジェクトにアタッチされていないコンポーネントがDestroyされました。適切な挙動かどうか確認してください");
		delete this;
	} else {
		LogWriter::Log("コンポーネントは正常に削除されました");
		Collider* cast_c = dynamic_cast<Collider*>(this);
		if (cast_c != NULL) {
			CollisionManager::RemoveCollider(cast_c);
		}
		delete this;
	}
}
