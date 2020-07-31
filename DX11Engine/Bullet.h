#pragma once
#include "ScriptBase.h"
class Bullet : public ScriptBase {
	void Update();

	void OnCollisionStay(Collision* collision);
};