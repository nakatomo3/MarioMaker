#include "EditScene.h"
#include "DXEngine.h"
#include "Player.h"
#include "PlayerCamera.h"
#include "EditorManager.h"
#include "StageManager.h"

bool EditScene::isEditMode;

EditScene::EditScene(string name) : Scene(name){
	isEditMode = true;
}

void EditScene::Start() {
	ObjectManager::Instantiate(player);
	ObjectManager::Instantiate(stage);
	int width = 20;
	for (int i = 0; i < width; i++) {
		stageManager->SetObject(i, 0, 'A');
	}
}

void EditScene::Load() {

	playerTexture = new Texture("assets/textures/MarioMaker/mario.png");
	blockTexture = new Texture("assets/textures/MarioMaker/groundBlock.png");

	stage = new GameObject("�X�e�[�W");
	stageManager = stage->AddComponent<StageManager>();
	stage->SetTag(MANAGER);

	editorObject = new GameObject("�G�f�B�^�I�u�W�F�N�g");
	editorObject->SetParent(stage);
	editorObject->SetTag(MANAGER);
	gameObject = new GameObject("�Q�[�������I�u�W�F�N�g");
	gameObject->SetParent(stage);
	gameObject->SetTag(MANAGER);

	//�Q�[�������I�u�W�F�N�g
	player = new GameObject("�v���C���[");
	player->SetTag(PLAYER);
	auto playerQuad = player->AddComponent<Quad>();
	playerQuad->SetTexture(playerTexture);
	playerQuad->SetCull(false);
	player->SetPosition(Vector3(10,3,0));
	auto playerScript = player->AddComponent<Player>();
	player->AddComponent<QuadCollider>();

	camera = new GameObject("�J����");
	camera->AddComponent<Camera>();
	camera->AddComponent<PlayerCamera>()->SetPlayer(player);
	camera->SetParent(gameObject);

	//�ҏW�I�u�W�F�N�g
	editorManager = editorObject->AddComponent<EditorManager>();
	editorManager->SetStage(stageManager);

	editorCamera = new GameObject("�G�f�B�^�J����");
	editorCamera->AddComponent<Camera>();
	editorCamera->SetPosition(Vector3(0, 7, -14));
	editorCamera->SetParent(editorObject);
	editorManager->SetCamera(editorCamera);

	//���쐬
	int width = 20;
	for (int i = 0; i < width; i++) {
		auto block = new GameObject("�u���b�NA");
		block->SetTag(GROUND_BLOCK);
		block->SetPosition(Vector3((float)i, 0, 0));
		block->AddComponent<Quad>()->SetTexture(blockTexture);
		block->AddComponent<QuadCollider>();
		block->SetParent(stage);
	}
	for (int i = 0; i < width; i++) {
		auto block = new GameObject("�u���b�NB");
		block->SetTag(GROUND_BLOCK);
		block->SetPosition(Vector3((float)i, -1, 0));
		block->AddComponent<Quad>()->SetTexture(blockTexture);
		block->AddComponent<QuadCollider>();
		block->SetParent(stage);
	}
}

void EditScene::Update() {
	if (Input::GetController(0).Gamepad.wButtons & XINPUT_GAMEPAD_START && beforeInputStart == false || Input::GetKeyDown(VK_RETURN)) {
		isEditMode = !isEditMode;
	}
	if (isEditMode == true) {
		gameObject->SetActive(false);
		editorManager->SetEditMode(true);
		player->SetActive(false);
	} else {
		if (player->GetActive() == false) {
			player->SetPosition(editorManager->GetCursorPos());
		}
		player->SetActive(true);
		gameObject->SetActive(true);
		editorManager->SetEditMode(false);
	}

	beforeInputStart = Input::GetController(0).Gamepad.wButtons & XINPUT_GAMEPAD_START;
}

bool EditScene::GetIsEditMode() {
	return isEditMode;
}
