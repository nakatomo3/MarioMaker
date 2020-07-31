#include "Collider.h"
#include "CollisionManager.h"
#include "SphereCollider.h"

vector<Collider*> CollisionManager::colliders;

void CollisionManager::AddCollider(Collider* collider) {
	colliders.emplace_back(collider);
}

void CollisionManager::RemoveCollider(Collider * collider) {
	for (unsigned int i = 0; i < colliders.size(); i++) {
		if (colliders[i] == collider) {
			//³í‚ÉŒ©‚Â‚©‚Á‚½
			Component* cacheComponent = colliders[i];
			colliders[i] = colliders[colliders.size() - 1];
			colliders.pop_back();
			return;
		}
	}
}

void CollisionManager::Update() {
	for (unsigned int i = 0; i < colliders.size(); i++) {
		for (unsigned int j = i + 1; j < colliders.size(); j++) {
			SphereCollider* cast_a = dynamic_cast<SphereCollider*>(colliders[i]);
			SphereCollider* cast_b = dynamic_cast<SphereCollider*>(colliders[j]);
			if (cast_a != NULL && cast_b != NULL) {
				auto distance = (cast_a->GetGameObject()->GetPosition() - cast_b->GetGameObject()->GetPosition()).Magnitude();
				auto radA = cast_a->GetRadius();
				auto radB = cast_b->GetRadius();
				if (distance <= sqrt(radA * radA * radA) + sqrt(radB * radB * radB)) {
					auto colA = new Collision(cast_b, Vector3(0, 0, 0), cast_b->GetGameObject());
					auto colB = new Collision(cast_a, Vector3(0, 0, 0), cast_a->GetGameObject());
					cast_a->GetGameObject()->OnCollisionStay(colA);
					cast_b->GetGameObject()->OnCollisionStay(colB);
					delete colA;
					delete colB;
				}
			}
		}
	}
}