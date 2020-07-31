#include "Collider.h"
#include "CollisionManager.h"

void Collider::SetTrigger(bool _isTrigger) {
	isTrigger = _isTrigger;
}

bool Collider::GetTrigger() {
	return isTrigger;
}

Collider::Collider() {
	CollisionManager::AddCollider(this);
}
