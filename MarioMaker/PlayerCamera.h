#pragma once
#include "ScriptBase.h"
class PlayerCamera : public ScriptBase {
public:
	void Update();

	void SetPlayer(GameObject* player);
private:
	GameObject* player;
};

