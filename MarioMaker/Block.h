#pragma once
#include "ScriptBase.h"
#include "Quad.h"
#include "QuadCollider.h"

typedef enum{
	BROKEN,
	BLOCK_COIN,
	BLOCK_ITEM,
	BLOCK_STAR
}BlockType;

class Block : public ScriptBase {
public:
	void OnCollisionStay(Collision* collision);
	void Update();
private:
	Quad* quad;
	QuadCollider* collider;

	BlockType type = BROKEN;

	Vector3 originPos = Vector3(0,0,-1);
	bool isImpact = false;
	float impactTimer = 0;
	const float returnTimer = 0.2f;
};