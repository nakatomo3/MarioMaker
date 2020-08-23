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
	float moveSpeed = 0.5f;
	float groundBrekeRate = 0.9f;

	const float gravity = 1.5f;

	bool isStand = false;

	Vector3 velocity;

	Quad* quad;

	WORD beforeControllerButton;
};