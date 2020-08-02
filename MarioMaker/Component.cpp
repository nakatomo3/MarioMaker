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
		LogWriter::LogWorning("�Q�[���I�u�W�F�N�g�ɃA�^�b�`����Ă��Ȃ��R���|�[�l���g��Destroy����܂����B�K�؂ȋ������ǂ����m�F���Ă�������");
		delete this;
	} else {
		LogWriter::Log("�R���|�[�l���g�͐���ɍ폜����܂���");
		Collider* cast_c = dynamic_cast<Collider*>(this);
		if (cast_c != NULL) {
			CollisionManager::RemoveCollider(cast_c);
		}
		delete this;
	}
}
