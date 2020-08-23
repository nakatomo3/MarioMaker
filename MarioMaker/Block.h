#pragma once
#include "ScriptBase.h"
#include "Quad.h"
#include "QuadCollider.h"

typedef enum{
	BROKEN,
	COIN
}BlockType;

class Block : public ScriptBase {
public:
	void OnCollisionStay(Collision* collision);
	void Update();
private:
	Quad* quad;
	QuadCollider* collider;

	BlockType type = BROKEN;
};