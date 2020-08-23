#pragma once
#include "ScriptBase.h"
#include "Texture.h"
#include "Quad.h"

typedef enum QuestionBlockType {
	HATENA_COIN,
	HATENA_ITEM,

};

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
};