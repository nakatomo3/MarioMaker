#include "SceneManager.h"
#include "LogWriter.h"

Scene* SceneManager::nowScene;
vector<Scene*> SceneManager::sceneList;
bool SceneManager::wasWorning;

void SceneManager::Init() {
	LogWriter::Log("シーンマネージャーが初期化されました");
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
			MessageBox(NULL, TEXT("なるべくシーン経由でゲームを実行してください"),	TEXT("警告"), MB_OK | MB_ICONWARNING | MB_TOPMOST);
#endif // DEBUG
			LogWriter::LogWorning("なるべくシーン経由でゲームを実行してください");
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
				LogWriter::Log("%sというシーンをアンロードしました", nowScene->name.c_str());
			}
			nowScene = sceneList[i];
			LogWriter::Log("%sというシーンを読み込みました", name.c_str());
			ObjectManager::Awake();
			ObjectManager::Start();
			return;
		}
	}
	LogWriter::LogWorning("%sというシーンは存在しませんでした", name);
}

void SceneManager::LoadScene(unsigned int num) {
	if (sceneList.size() < num) {
		//シーンリストのサイズよりも大きい場合エラー
		LogWriter::LogWorning("%d番目のシーンは存在しませんでした。シーン数は%dです", num, sceneList.size());
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
	LogWriter::LogWorning("%sというシーンは存在しませんでした", name);
	return;
}

void SceneManager::BackLoad(unsigned int num) {
	if (sceneList.size() < num) {
		LogWriter::LogWorning("%d番目のシーンは存在しませんでした。シーン数は%dです", num, sceneList.size());
		return;
	}
	sceneList[num]->Load();
}

void SceneManager::Unload(Scene* scene) {
	scene->Unload();
}

void SceneManager::Unload() {
	if (nowScene == nullptr) {
		LogWriter::LogError("シーンがロードされていない状態でUnloadしようとしました。適切な挙動か確認してください");
	} else {
		nowScene->UnLoad();
		nowScene = nullptr;
	}
}

Scene* SceneManager::GetScene(unsigned int num) {
	if (sceneList.size() < num) {
		LogWriter::LogWorning("%d番目のシーンは存在しませんでした。シーン数は%dです", num, sceneList.size());
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
	LogWriter::LogWorning("%sというシーンは存在しませんでした", name);
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