#pragma once
#include "Vector3.h"
#include "GameObject.h"
class Collider;
class Collision {
public:
	Collision(Collider* collider, Vector3 contactPoint, GameObject* gameObject);

	Collider* GetCollider();
	Vector3 GetContactPoint();
	GameObject* GetGameObject();

private:
	Collider* collider;
	Vector3 contactPoint;
	GameObject* gameObject;
};