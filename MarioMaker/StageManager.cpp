#define _CRT_SECURE_NO_WARNINGS
#include "StageManager.h"
#include <direct.h>
#include <Windows.h>
FILE* stageFile;

string StageManager::path;

void StageManager::Start() {
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
}

char StageManager::GetStageObject(int x, int y) {
	return stage[y][x];
}

void StageManager::SaveStage(string path) {
	_mkdir("Stages");
	stageFile = fopen(path.c_str(), "w");
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

	char typeBuf;
	fread(&typeBuf, sizeof(char), 1, file);
	stageType = (StageType)(typeBuf - '0');
	fread(&typeBuf, sizeof(char), 1, file);//改行文字を空読みする
	stageSizeX = 0;
	char sizeBuf = 0;
	fread(&typeBuf, sizeof(char), 1, file);	//この位置に改行コードが入っているので一回空読みする
	while (sizeBuf != '\n') {
		fread(&sizeBuf, sizeof(char), 1, file);
		if (sizeBuf >= '0' && sizeBuf < '9') {
			stageSizeX = stageSizeX * 10 + (sizeBuf - '0');
		}
	}

	for (unsigned int i = 0; i < 14; i++) {
		string line;
		while (true) {
			char outBuf = 0;
			fread(&outBuf, sizeof(char), 1, file);
			if (outBuf == '\n' || outBuf == 0) {
				LogWriter::Log("%s", line.c_str());
				break;
			} else {
				line += outBuf;
			}
		}
	}
}

void StageManager::SetStagePath(string _path) {
	path = _path;
}
