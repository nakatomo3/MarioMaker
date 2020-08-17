#pragma once
#include "ScriptBase.h"
#include "Vector3.h"
#include "Quad.h"
class Player : public ScriptBase {
public:
	void Update();

	void SetQuad(Quad* _quad);

	void KeyboardInput();
	void ControllerInput();

	void OnCollisionStay(Collision* collision);
private:
	float moveSpeed = 1;
	float groundBrekeRate = 0.9f;

	const float gravity = 2;

	bool isStand = false;

	Vector3 velocity;

	Quad* quad;
};