#pragma once
#include "ScriptBase.h"
class Player : public ScriptBase {
public:
	void Update();
private:
	float speed = 2;
};
