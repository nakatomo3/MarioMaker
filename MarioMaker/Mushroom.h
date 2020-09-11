#pragma once
#include "ScriptBase.h"
#include "Quad.h"
class Mushroom : public ScriptBase {
public:
	void Start();
	void Update();

	void OnCollisionStay(Collision* collision);

private:
	Quad* quad;
	static Texture* texture;

	Vector3 velocity = Vector3();
	bool isStand = false;

	bool isRight = true;

	const float gravity = 1.5f;
	const float speed = 5;
};