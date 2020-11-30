#define _CRT_SECURE_NO_WARNINGS
#include "ObjectManager.h"
#include "StageManager.h"
#include <direct.h>
#include <Windows.h>
#include "Quad.h"
#include "QuadCollider.h"
#include "GameObject.h"
#include "Block.h"
#include "QuestionBlock.h"
#include "SceneManager.h"

FILE* stageFile;

string StageManager::path;

void StageManager::Start() {
	usedBlockTexture = new Texture("assets/textures/MarioMaker/usedBlock.png");
	objectTextures[0] = new Texture("assets/textures/MarioMaker/groundBlock.png");
	objectTextures[1] = new Texture("assets/textures/MarioMaker/block.png");
	objectTextures[2] = new Texture("assets/textures/MarioMaker/hatenaBlock.png");
	objectTextures[3] = new Texture("assets/textures/MarioMaker/standBlock.png");

	if (path == "") {
		for (int i = 0; i < 14; i++) {
			stage.emplace_back();
			for (int j = 0; j < stageSizeX; j++) {
				stage[i].emplace_back('0');
			}
		}
	} else {
		ReadStage(path);
	}

}

void StageManager::OnDestroy() {
	for (int i = 0; i < 4; i++) {
		objectTextures[i]->Release();
	}
	usedBlockTexture->Release();
}

GameObject * StageManager::GetChildGameObject(Vector3 pos) {
	GameObject* obj = nullptr;
	auto childCount = gameObject->GetChildCount();
	for (unsigned int i = 0; i < childCount; i++) {
		if (gameObject->GetChild(i)->GetPosition() == pos) {
			if (gameObject->GetChild(i)->GetTag() != MANAGER) {
				obj = gameObject->GetChild(i);
				break;
			}
		}
	}
	return obj;
}

void StageManager::SetStageSize(unsigned int size) {
	stageSizeX = size;
}

int StageManager::GetStageSize() {
	return stageSizeX;
}

void StageManager::SetObject(int x, int y, char obj) {
	stage[y][x] = obj;
	if(obj == '0'){
		return;
	}
	auto stageObj = new GameObject();
	stageObj->SetParent(gameObject);
	auto quad = stageObj->AddComponent<Quad>();
	switch (obj) {
	default:
		break;
	case 'A':
		stageObj->SetName("地形ブロック");
		stageObj->SetTag(GROUND_BLOCK);
		stageObj->SetPosition(Vector3((float)x, (float)y, 0));
		stageObj->AddComponent<QuadCollider>();
		quad->SetTexture(objectTextures[0]);

		if (y == 0) {
			auto underStageBlock = new GameObject();
			underStageBlock->SetParent(gameObject);
			auto quad = underStageBlock->AddComponent<Quad>();
			underStageBlock->SetName("地形ブロック");
			underStageBlock->SetTag(GROUND_BLOCK);
			underStageBlock->SetPosition(Vector3((float)x, (float)y - 1, 0));
			underStageBlock->AddComponent<QuadCollider>();
			quad->SetTexture(objectTextures[0]);
			ObjectManager::Instantiate(underStageBlock);
		}
		break;
	case 'B':
		stageObj->SetName("ブロック");
		stageObj->SetTag(BLOCK);
		stageObj->AddComponent<Block>();
		stageObj->SetPosition(Vector3((float)x, (float)y, 0));
		stageObj->AddComponent<QuadCollider>();
		quad->SetTexture(objectTextures[1]);
		break;
	case 'C':
		stageObj->SetName("ハテナブロック");
		stageObj->SetTag(HATENA_BLOCK);
		stageObj->SetPosition(Vector3((float)x, (float)y, 0));
		stageObj->AddComponent<QuadCollider>();
		quad->SetTexture(objectTextures[2]);
		{
			auto hatena = stageObj->AddComponent<QuestionBlock>();
			hatena->SetUsedBlock(usedBlockTexture);
		}
		break;
	case 'D':
		stageObj->SetName("足場ブロック");
		stageObj->SetTag(GROUND_BLOCK);
		stageObj->SetPosition(Vector3((float)x, (float)y, 0));
		stageObj->AddComponent<QuadCollider>();
		quad->SetTexture(objectTextures[3]);
		break;
	}
	ObjectManager::Instantiate(stageObj);
}

char StageManager::GetStageObject(int x, int y) {
	return stage[y][x];
}

void StageManager::SaveStage(string path) {
	_mkdir("Stages");
	stageFile = fopen(path.c_str(), "w");
	fprintf(stageFile, "0\n");
	fprintf(stageFile, "%d\n", stageSizeX);
	for (int y = stage.size() - 1; y >= 0; y--) {
		LogWriter::Log("%d", y);
		for (unsigned int x = 0; x < stage[y].size(); x++) {
			fprintf(stageFile, "%c", (const char *)stage[y][x]);
		}
		fprintf(stageFile, "\n");
	}
	fclose(stageFile);
}

void StageManager::ReadStage(string path) {

	auto file = fopen((path).c_str(), "r");

	//タイプ読み込み
	char typeBuf;
	fread(&typeBuf, sizeof(char), 1, file);
	stageType = (StageType)(typeBuf - '0');
	fread(&typeBuf, sizeof(char), 1, file);//改行文字を空読みする

	//サイズ読み込み
	stageSizeX = 0;
	char sizeBuf = 0;
	while (sizeBuf != '\n') {
		fread(&sizeBuf, sizeof(char), 1, file);
		if (sizeBuf >= '0' && sizeBuf < '9') {
			stageSizeX = stageSizeX * 10 + (sizeBuf - '0');
		}
	}

	for (unsigned int i = 0; i < 14; i++) {
		stage.emplace_back();
		for (unsigned int j = 0; j < stageSizeX; j++) {
			stage[i].emplace_back('0');
		}
	}

	int xPos = 0;
	for (unsigned int i = 0; i < 14; i++) {
		xPos = 0;
		while (true) {
			char outBuf = 0;
			xPos++;
			fread(&outBuf, sizeof(char), 1, file);
			if (outBuf == '\n' || outBuf == 0) {
				break;
			} else {
				SetObject(xPos, 13 - i, outBuf);
			}
		}
	}
}

void StageManager::SetStagePath(string _path) {
	path = _path;
}

Texture * StageManager::GetObjectTexture(int index) {
	return objectTextures[index];
}
