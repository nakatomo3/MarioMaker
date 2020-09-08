#pragma once
#include "ScriptBase.h"
#include "Texture.h"
#include "Quad.h"

typedef enum {
	HATENA_COIN,
	HATENA_ITEM,
}QuestionBlockType;

class QuestionBlock : public ScriptBase {
private:
	bool isUsed = false;

	Quad* quad;
	Texture* hatenaBlock;
	Texture* usedBlock;

	QuestionBlockType type;
public:
	void OnCollisionStay(Collision* collision);
	void SetUsedBlock(Texture* texture);

	void Update();

	void SetBlockType(QuestionBlockType type);
	QuestionBlockType GetBlockType();
};