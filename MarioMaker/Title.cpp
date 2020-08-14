#include "Title.h"
#include "DXEngine.h"
#include "TitleScelectIcon.h"

Title::Title(string name) : Scene(name){

}

void Title::Load() {
	titleTexture = new Texture("assets/textures/MarioMaker/Title.png");

	camera = new GameObject("カメラ");
	camera->AddComponent<Camera>();

	titleBackGround = new GameObject("背景");
	auto backGroundImage = titleBackGround->AddComponent<Image>();
	backGroundImage->SetScale(Vector2(SCREEN_WIDTH, SCREEN_HEIGHT));
	backGroundImage->SetTexture(titleTexture);

	selectIcon = new GameObject("選択アイコン");
	selectIcon->AddComponent<TitleScelectIcon>();
}

void Title::Start() {
	ObjectManager::Instantiate(titleBackGround);
	ObjectManager::Instantiate(selectIcon);
	ObjectManager::Instantiate(camera);
}

void Title::Unload() {
	titleTexture->Release();
	selectIconTexture->Release();

	titleBackGround->Destroy();
	selectIcon->Destroy();
}
