#include "SceneManager.h"
#include "LogWriter.h"

Scene* SceneManager::nowScene;
vector<Scene*> SceneManager::sceneList;
bool SceneManager::wasWorning;
bool SceneManager::willLoadScene;
Scene* SceneManager::loadScene;

void SceneManager::Init() {
	LogWriter::Log("�V�[���}�l�[�W���[������������܂���");
	wasWorning = false;
}

void SceneManager::Uninit() {

}

void SceneManager::Update() {
	if (nowScene != nullptr) {
		nowScene->Update();
	} else {
		if (wasWorning == false) {
#ifdef _DEBUG
			MessageBox(NULL, TEXT("�Ȃ�ׂ��V�[���o�R�ŃQ�[�������s���Ă�������"),	TEXT("�x��"), MB_OK | MB_ICONWARNING | MB_TOPMOST);
#endif // DEBUG
			LogWriter::LogWorning("�Ȃ�ׂ��V�[���o�R�ŃQ�[�������s���Ă�������");
		}
		wasWorning = true;
	}
}

void SceneManager::LoadScene(Scene* scene) {
	nowScene = scene;
	scene->Load();
	scene->Start();
}

void SceneManager::LoadScene(string name) {
	for (unsigned int i = 0; i < sceneList.size(); i++) {
		if (sceneList[i]->name == name) {
			loadScene = sceneList[i];
			willLoadScene = true;
			ObjectManager::isEndUpdate = true;
			return;
		}
	}
	LogWriter::LogWorning("%s�Ƃ����V�[���͑��݂��܂���ł���", name.c_str());
}

void SceneManager::LoadScene(unsigned int num) {
	if (sceneList.size() < num) {
		//�V�[�����X�g�̃T�C�Y�����傫���ꍇ�G���[
		LogWriter::LogWorning("%d�Ԗڂ̃V�[���͑��݂��܂���ł����B�V�[������%d�ł�", num, sceneList.size());
		return;
	}
	loadScene = sceneList[num];
	willLoadScene = true;
	ObjectManager::isEndUpdate = true;
}

void SceneManager::BackLoad(Scene * scene) {
	scene->Load();
}

void SceneManager::BackLoad(string name) {
	for (unsigned int i = 0; i < sceneList.size(); i++) {
		if (sceneList[i]->name == name) {
			sceneList[i]->Load();
		}
	}
	LogWriter::LogWorning("%s�Ƃ����V�[���͑��݂��܂���ł���", name.c_str());
	return;
}

void SceneManager::BackLoad(unsigned int num) {
	if (sceneList.size() < num) {
		LogWriter::LogWorning("%d�Ԗڂ̃V�[���͑��݂��܂���ł����B�V�[������%d�ł�", num, sceneList.size());
		return;
	}
	sceneList[num]->Load();
}

void SceneManager::Unload(Scene* scene) {
	scene->Unload();
	if (nowScene == scene) {
		nowScene = nullptr;
	}
}

void SceneManager::Unload() {
	if (nowScene == nullptr) {
		LogWriter::LogError("�V�[�������[�h����Ă��Ȃ���Ԃ�Unload���悤�Ƃ��܂����B�K�؂ȋ������m�F���Ă�������");
	} else {
		nowScene->Unload();
		nowScene = nullptr;
	}
}

Scene* SceneManager::GetScene(unsigned int num) {
	if (sceneList.size() < num) {
		LogWriter::LogWorning("%d�Ԗڂ̃V�[���͑��݂��܂���ł����B�V�[������%d�ł�", num, sceneList.size());
		return nullptr;
	}
	return sceneList[num];
}

Scene* SceneManager::GetScene(string name) {
	for (unsigned int i = 0; i < sceneList.size(); i++) {
		if (sceneList[i]->name == name) {
			return sceneList[i];
		}
	}
	LogWriter::LogWorning("%s�Ƃ����V�[���͑��݂��܂���ł���", name.c_str());
	return nullptr;
}

string SceneManager::GetSceneName(Scene * scene) {
	return scene->name;
}

string SceneManager::GetSceneName(unsigned int number) {
	return sceneList[number]->name;
}

void SceneManager::AddScene(Scene * scene) {
	LogWriter::Log("%s�Ƃ����V�[����ǉ����܂���", scene->name.c_str());
	sceneList.push_back(scene);
}

void SceneManager::Load() {
	if (nowScene != nullptr) {
		ObjectManager::UnLoad(nowScene);
		nowScene->Unload();
		LogWriter::Log("%s�Ƃ����V�[�����A�����[�h���܂���", nowScene->name.c_str());
	}
	loadScene->Load();
	loadScene->Start();
	LogWriter::Log("%s�Ƃ����V�[����ǂݍ��݂܂���", loadScene->name.c_str());
	nowScene = loadScene;

	willLoadScene = false;
	loadScene = nullptr;
}

Scene * SceneManager::GetNowScene() {
	return nowScene;
}

string SceneManager::GetNowSceneName() {
	return nowScene->name;
}

int SceneManager::GetNowSceneNumber() {
	return nowScene->sceneNumber;
}