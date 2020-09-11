#pragma once
#include "ScriptBase.h"
#include "Quad.h"
class CoinEffect : public ScriptBase {
public:
	void Update();
	void Start();

	static Texture* coinTexture;

private:
	Quad* quad;

	float timer = 0;
	float time = 0.8f;
	float speed = 20;
	Vector3 velocity;
};

