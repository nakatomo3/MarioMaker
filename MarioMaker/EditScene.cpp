#include "EditScene.h"
#include "DXEngine.h"
#include "Player.h"
#include "PlayerCamera.h"
#include "EditorManager.h"

EditScene::EditScene(string name) : Scene(name){

}

void EditScene::Start() {
	ObjectManager::Instantiate(player);
	ObjectManager::Instantiate(gameObject);
	ObjectManager::Instantiate(editorObject);
}

void EditScene::Load() {
	playerTexture = new Texture("assets/textures/MarioMaker/mario.png");
	auto blockTexture = new Texture("assets/textures/MarioMaker/groundBlock.png");

	editorObject = new GameObject("EditorObject");
	gameObject = new GameObject("GameObject");

	//ゲーム部分オブジェクト
	player = new GameObject("Player");
	auto playerQuad = player->AddComponent<Quad>();
	playerQuad->SetTexture(playerTexture);
	playerQuad->SetCull(false);
	auto playerScript = player->AddComponent<Player>();
	playerScript->SetQuad(playerQuad);
	player->AddComponent<QuadCollider>();

	camera = new GameObject("Camera");
	camera->AddComponent<Camera>();
	camera->AddComponent<PlayerCamera>()->SetPlayer(player);
	camera->SetParent(gameObject);

	//編集オブジェクト
	auto editorManager = editorObject->AddComponent<EditorManager>();

	editorCamera = new GameObject("EditorCamera");
	editorCamera->AddComponent<Camera>();
	editorCamera->SetPosition(Vector3(0, 0, -14));
	editorCamera->SetParent(editorObject);
	editorManager->SetCamera(editorCamera);

	//仮作成
	int width = 20;
	for (int i = 0; i < width; i++) {
		auto block = new GameObject("Block");
		block->SetTag(GROUND_BLOCK);
		block->SetPosition(Vector3((float)i, -7, 0));
		block->AddComponent<Quad>()->SetTexture(blockTexture);
		block->AddComponent<QuadCollider>();
		ObjectManager::Instantiate(block);
	}
	{
		auto block = new GameObject("Block");
		block->SetTag(GROUND_BLOCK);
		block->SetPosition(Vector3(3, -6, 0));
		block->AddComponent<Quad>()->SetTexture(blockTexture);
		block->AddComponent<QuadCollider>();
		ObjectManager::Instantiate(block);
	}
	{
		auto block = new GameObject("Block");
		block->SetTag(GROUND_BLOCK);
		block->SetPosition(Vector3(3, -5, 0));
		block->AddComponent<Quad>()->SetTexture(blockTexture);
		block->AddComponent<QuadCollider>();
		ObjectManager::Instantiate(block);
	}
	{
		auto block = new GameObject("Block");
		block->SetTag(GROUND_BLOCK);
		block->SetPosition(Vector3(3, -4, 0));
		block->AddComponent<Quad>()->SetTexture(blockTexture);
		block->AddComponent<QuadCollider>();
		ObjectManager::Instantiate(block);
	}

}

void EditScene::Update() {
	if (Input::GetController(0).Gamepad.wButtons & XINPUT_GAMEPAD_START && beforeInputStart == false || Input::GetKeyDown(VK_RETURN)) {
		isEditMode = !isEditMode;
	}
	if (isEditMode == true) {
		gameObject->SetActive(false);
		editorObject->SetActive(true);
		player->SetActive(false);
	} else {
		gameObject->SetActive(true);
		editorObject->SetActive(false);
		player->SetActive(true);
	}

	beforeInputStart = Input::GetController(0).Gamepad.wButtons & XINPUT_GAMEPAD_START;
}
