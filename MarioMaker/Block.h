#pragma once
#include "ScriptBase.h"
#include "Quad.h"
#include "QuadCollider.h"
class Block : public ScriptBase {
public:
	void OnCollisionStay(Collision* collision);
	void Update();
private:
	Quad* quad;
	QuadCollider* collider;
};