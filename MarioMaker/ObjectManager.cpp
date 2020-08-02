#include "LogWriter.h"
#include "VisualComponent.h"
#include "ObjectManager.h"
#include <list>
#include "RendererManager.h"
#include "Camera.h"
#include "SceneManager.h"

vector<GameObject*> ObjectManager::objects;

GameObject* ObjectManager::Instantiate(GameObject* instance) {
	objects.emplace_back(instance);
	if (SceneManager::GetNowScene() != nullptr) {
		instance->scene = SceneManager::GetNowScene();
	}
	return instance;
}

void ObjectManager::Destroy(GameObject* instance) {
	for (unsigned int i = 0; i < objects.size(); i++) {
		if (objects[i] == instance) {
			GameObject* removeObject = instance;
			objects[i] = objects[objects.size() - 1];
			objects.pop_back();
			return;
		}
	}
	LogWriter::LogError("オブジェクトマネージャーに登録されていないオブジェクトがDestroyされました");
}

bool ObjectManager::CheckInstance(GameObject* instance) {
	for (unsigned int i = 0; i < objects.size(); i++) {
		if (objects[i] == instance) {
			return true;
		}
	}
	return false;
}

void ObjectManager::Awake() {
	for (unsigned int i = 0; i < objects.size(); i++) {
		if (objects[i]->GetActive() == false) {
			continue;
		}
		for (unsigned int j = 0; j < objects[i]->GetComponentCount(); j++) {
			if (objects[i]->GetComponent(j)->GetActive() == true) {
				objects[i]->GetComponent(j)->Awake();
			}
		}
	}
}

void ObjectManager::Start() {
	for (unsigned int i = 0; i < objects.size(); i++) {
		if (objects[i]->GetActive() == false) {
			continue;
		}
		for (unsigned int j = 0; j < objects[i]->GetComponentCount(); j++) {
			if (objects[i]->GetComponent(j)->GetActive() == true) {
				objects[i]->GetComponent(j)->Start();
			}
		}
	}
}

void ObjectManager::FirstUpdate() {
	for (unsigned int i = 0; i < objects.size(); i++) {
		if (objects[i]->GetActive() == false) {
			continue;
		}
		for (unsigned int j = 0; j < objects[i]->GetComponentCount(); j++) {
			if (objects[i]->GetComponent(j)->GetActive() == true) {
				objects[i]->GetComponent(j)->FirstUpdate();
			}
		}
	}
}

void ObjectManager::Update() {
	for (unsigned int i = 0; i < objects.size(); i++) {
		if (objects[i]->GetActive() == false) {
			continue;
		}
		objects[i]->Update();
	}
}

void ObjectManager::LateUpdate() {
	for (unsigned int i = 0; i < objects.size(); i++) {
		if (objects[i]->GetActive() == false) {
			continue;
		}
		for (unsigned int j = 0; j < objects[i]->GetComponentCount(); j++) {
			if (objects[i]->GetComponent(j)->GetActive() == true) {
				objects[i]->GetComponent(j)->LateUpdate();
			}
		}
	}
}

void ObjectManager::Draw() {
	Camera* camera = nullptr;
	for (int layerCount = 0; layerCount < LAYERLAST; layerCount++) {
		for (unsigned int i = 0; i < objects.size(); i++) {
			if (objects[i]->GetActive() == false) {
				continue;
			}
			for (unsigned int j = 0; j < objects[i]->GetComponentCount(); j++) {
				VisualComponent* cast_c = dynamic_cast<VisualComponent*>(objects[i]->GetComponent(j));
				if (cast_c != NULL && cast_c->GetLayer() == layerCount && objects[i]->GetComponent(j)->GetActive() == true) {
					cast_c->Draw();
				}
				Camera* cast_camera = dynamic_cast<Camera*>(objects[i]->GetComponent(j));
				if (cast_camera != NULL) {
					if (camera == nullptr) {
						camera = cast_camera;
					} else {
						if (camera != cast_camera) {
							LogWriter::LogError("カメラは二つ以上置かないでください");
						}
					}
				}
			}

		}
	}
	if (camera == nullptr) {
		LogWriter::LogError("カメラは一つ以上置いてください");
	}
	
}

void ObjectManager::LateDraw() {
	for (unsigned int i = 0; i < objects.size(); i++) {
		if (objects[i]->GetActive() == false) {
			continue;
		}
		for (unsigned int j = 0; j < objects[i]->GetComponentCount(); j++) {
			VisualComponent* cast_c = dynamic_cast<VisualComponent*>(objects[i]->GetComponent(j));
			if (cast_c != NULL && objects[i]->GetComponent(j)->GetActive() == true) {
				cast_c->LateDraw();
			}
		}
	}
}

void ObjectManager::Init() {
	LogWriter::Log("オブジェクトマネージャーが初期化されました");
}

void ObjectManager::UnLoad(Scene * scene) {
	auto objectCount = objects.size();
	for (unsigned int i = 0; i < objectCount; i++) {
		if (objects[i]->scene == scene && objects[i]->isDestroyOnLoad == true) {
			GameObject* removeObject = objects[i];
			objects[i] = objects[objects.size() - 1];
			objects.pop_back();
			removeObject->Destroy();
		}
	}
}
