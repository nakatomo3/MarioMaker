#pragma once
#include "ScriptBase.h"
#include "Vector3.h"
#include "Quad.h"

typedef enum {
	MINIMUM,
	BIG,
	FIRE
}PlayerGrowth;

class Player : public ScriptBase {
public:
	void Start();

	void Update();

	void KeyboardInput();
	void ControllerInput();

	void OnCollisionStay(Collision* collision);

	PlayerGrowth GetPlayerGrowth();
private:
	float moveSpeed = 0.5f;
	float groundBrekeRate = 0.9f;

	const float gravity = 1.5f;

	bool isStand = false;
	bool isDead = false;

	float deadTimer = 0;
	float deadTime = 1.0f;
	float deadSpeed = 15;

	Vector3 velocity;

	Quad* quad;

	WORD beforeControllerButton;

	PlayerGrowth growth = MINIMUM;

	Texture* textures[4];
};