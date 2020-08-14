#include "Title.h"
#include "DXEngine.h"
#include "TitleScelectIcon.h"

Title::Title(string name) : Scene(name){

}

void Title::Load() {
	titleTexture = new Texture("assets/textures/MarioMaker/Title.png");

	camera = new GameObject("�J����");
	camera->AddComponent<Camera>();

	titleBackGround = new GameObject("�w�i");
	auto backGroundImage = titleBackGround->AddComponent<Image>();
	backGroundImage->SetScale(Vector2(SCREEN_WIDTH, SCREEN_HEIGHT));
	backGroundImage->SetTexture(titleTexture);

	selectIcon = new GameObject("�I���A�C�R��");
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
