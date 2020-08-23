#pragma once
#include "ScriptBase.h"
#include "Texture.h"
#include "Quad.h"
class QuestionBlock : public ScriptBase {
private:
	bool isUsed = false;

	Quad* quad;
	Texture* hatenaBlock;
	Texture* usedBlock;
public:
	void OnCollisionStay(Collision* collision);
	void SetUsedBlock(Texture* texture);

	void Update();
};