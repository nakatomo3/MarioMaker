#include "Title.h"
#include "DXEngine.h"
#include "TitleScelectIcon.h"

Title::Title(string name) : Scene(name){

}

void Title::Load() {
	titleTexture = new Texture("assets/textures/MarioMaker/Title/Title.png");

	createTexture = new Texture("assets/textures/MarioMaker/Title/Create.png");
	playTexture = new Texture("assets/textures/MarioMaker/Title/Play.png");
	modeTexture = new Texture("assets/textures/MarioMaker/Title/Mode.png");

	camera = new GameObject("カメラ");
	camera->AddComponent<Camera>();

	titleBackGround = new GameObject("背景");
	auto backGroundImage = titleBackGround->AddComponent<Image>();
	backGroundImage->SetScale(Vector2(SCREEN_WIDTH, SCREEN_HEIGHT));
	backGroundImage->SetTexture(titleTexture);

	selectIcon = new GameObject("選択アイコン");
	selectIcon->AddComponent<TitleScelectIcon>();

	modeObject = new GameObject();
	auto create = modeObject->AddComponent<Image>();
	create->SetTexture(createTexture);
	create->SetPosition(Vector3(SCREEN_CENTER_X * 0.9f, SCREEN_HEIGHT * 0.6f, 0));
	create->SetScale(Vector2(SCREEN_HEIGHT * 0.21f, SCREEN_HEIGHT * 0.03f));
	auto modeA = modeObject->AddComponent<Image>();
	modeA->SetTexture(modeTexture);
	modeA->SetPosition(Vector3(SCREEN_CENTER_X * 1.2f, SCREEN_HEIGHT * 0.6f, 0));
	modeA->SetScale(Vector2(SCREEN_HEIGHT * 0.15f, SCREEN_HEIGHT * 0.03f));
	auto play = modeObject->AddComponent<Image>();
	play->SetTexture(playTexture);
	play->SetPosition(Vector3(SCREEN_CENTER_X * 0.9f, SCREEN_HEIGHT * 0.7f, 0));
	play->SetScale(Vector2(SCREEN_HEIGHT * 0.43f, SCREEN_HEIGHT * 0.03f));
	auto modeB = modeObject->AddComponent<Image>();
	modeB->SetTexture(modeTexture);
	modeB->SetPosition(Vector3(SCREEN_CENTER_X * 1.2f, SCREEN_HEIGHT * 0.7f, 0));
	modeB->SetScale(Vector2(SCREEN_HEIGHT * 0.15f, SCREEN_HEIGHT * 0.03f));
}

void Title::Start() {
	ObjectManager::Instantiate(titleBackGround);
	ObjectManager::Instantiate(selectIcon);
	ObjectManager::Instantiate(camera);
	ObjectManager::Instantiate(modeObject);
}

void Title::Unload() {
	titleTexture->Release();

	titleBackGround->Destroy();
	selectIcon->Destroy();
	camera->Destroy();
}
