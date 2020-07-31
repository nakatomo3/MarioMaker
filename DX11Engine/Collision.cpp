#include "Collision.h"
Collision::Collision(Collider * _collider, Vector3 _contactPoint, GameObject * _gameObject) {
	collider = _collider;
	contactPoint = _contactPoint;
	gameObject = _gameObject;
}

Collider * Collision::GetCollider() {
	return collider;
}

Vector3 Collision::GetContactPoint() {
	return contactPoint;
}

GameObject * Collision::GetGameObject() {
	return gameObject;
}
