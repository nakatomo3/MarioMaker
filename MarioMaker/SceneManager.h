#pragma once
#include "Singleton.h"
#include "Scene.h"
#include <vector>
#include <string>

using namespace std;

class ObjectManager;

class SceneManager{
	friend class Scene;
	friend class ObjectManager;
public :

	static void LoadScene(Scene* scene);
	static void LoadScene(string name);
	static void LoadScene(unsigned int num);

	static void BackLoad(Scene* scene);
	static void BackLoad(string name);
	static void BackLoad(unsigned int num);

	static void Unload(Scene* scene);
	static void Unload();

	static Scene* GetScene(unsigned int num);
	static Scene* GetScene(string name);

	static string GetSceneName(Scene* scene);
	static string GetSceneName(unsigned int number);

	static Scene* GetNowScene();
	static string GetNowSceneName();
	static int GetNowSceneNumber();

	static void Init();
	static void Uninit();

	static void Update();
private:

	static Scene* nowScene;

	static vector<Scene*> sceneList;

	static bool wasWorning;

	static void AddScene(Scene* scene);

	static bool willLoadScene;

	static Scene* loadScene;
	static void Load();
};