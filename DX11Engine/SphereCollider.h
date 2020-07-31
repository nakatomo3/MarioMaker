#pragma once
#include "Collider.h"
class SphereCollider : public Collider {
public:
	float GetRadius();
private:
	float radius = 0.5f;
};