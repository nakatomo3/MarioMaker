#include "SceneManager.h"
#include "LogWriter.h"

Scene* SceneManager::nowScene;
vector<Scene*> SceneManager::sceneList;
bool SceneManager::wasWorning;

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
	scene->Load();
	scene->Start();
	nowScene = scene;
}

void SceneManager::LoadScene(string name) {
	for (unsigned int i = 0; i < sceneList.size(); i++) {
		if (sceneList[i]->name == name) {
			sceneList[i]->Load();
			sceneList[i]->Start();
			if (nowScene != nullptr) {
				nowScene->UnLoad();
				LogWriter::Log("%s�Ƃ����V�[�����A�����[�h���܂���", nowScene->name.c_str());
			}
			nowScene = sceneList[i];
			LogWriter::Log("%s�Ƃ����V�[����ǂݍ��݂܂���", name.c_str());
			ObjectManager::Awake();
			ObjectManager::Start();
			return;
		}
	}
	LogWriter::LogWorning("%s�Ƃ����V�[���͑��݂��܂���ł���", name);
}

void SceneManager::LoadScene(unsigned int num) {
	if (sceneList.size() < num) {
		//�V�[�����X�g�̃T�C�Y�����傫���ꍇ�G���[
		LogWriter::LogWorning("%d�Ԗڂ̃V�[���͑��݂��܂���ł����B�V�[������%d�ł�", num, sceneList.size());
		return;
	}
	sceneList[num]->Load();
	sceneList[num]->Start();
	nowScene = sceneList[num];
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
	LogWriter::LogWorning("%s�Ƃ����V�[���͑��݂��܂���ł���", name);
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
}

void SceneManager::Unload() {
	if (nowScene == nullptr) {
		LogWriter::LogError("�V�[�������[�h����Ă��Ȃ���Ԃ�Unload���悤�Ƃ��܂����B�K�؂ȋ������m�F���Ă�������");
	} else {
		nowScene->UnLoad();
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
	LogWriter::LogWorning("%s�Ƃ����V�[���͑��݂��܂���ł���", name);
	return nullptr;
}

string SceneManager::GetSceneName(Scene * scene) {
	return scene->name;
}

string SceneManager::GetSceneName(unsigned int number) {
	return sceneList[number]->name;
}

void SceneManager::AddScene(Scene * scene) {
	sceneList.push_back(scene);
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