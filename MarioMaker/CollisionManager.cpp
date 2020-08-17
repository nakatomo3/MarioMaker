#include "Collider.h"
#include "CollisionManager.h"
#include "SphereCollider.h"
#include "QuadCollider.h"

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
			//SphereCollider“¯Žm‚ÌÕ“Ë
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
				continue;
			}

			QuadCollider* cast_c = dynamic_cast<QuadCollider*>(colliders[i]);
			QuadCollider* cast_d = dynamic_cast<QuadCollider*>(colliders[j]);
			//QuadCollider“¯Žm‚ÌÕ“ËBŒãXBoxCollider‚Ì‚Ý‚É‚È‚é—\’è
			if (cast_c != NULL && cast_d != NULL) {
				auto distance = (cast_c->GetGameObject()->GetPosition() - cast_d->GetGameObject()->GetPosition()).Magnitude();
				if (cast_c->GetGameObject()->GetScale().Magnitude() + cast_d->GetGameObject()->GetScale().Magnitude() >= distance) {
					if ((cast_c->GetGameObject()->GetPosition().GetX() - cast_c->GetGameObject()->GetScale().GetX() / 2 >= cast_d->GetGameObject()->GetPosition().GetX() - cast_d->GetGameObject()->GetScale().GetX() / 2 && cast_c->GetGameObject()->GetPosition().GetX() - cast_c->GetGameObject()->GetScale().GetX() / 2 <= cast_d->GetGameObject()->GetPosition().GetX() + cast_d->GetGameObject()->GetScale().GetX() / 2) ||
						(cast_c->GetGameObject()->GetPosition().GetX() + cast_c->GetGameObject()->GetScale().GetX() / 2 >= cast_d->GetGameObject()->GetPosition().GetX() - cast_d->GetGameObject()->GetScale().GetX() / 2 && cast_c->GetGameObject()->GetPosition().GetX() + cast_c->GetGameObject()->GetScale().GetX() / 2 <= cast_d->GetGameObject()->GetPosition().GetX() + cast_d->GetGameObject()->GetScale().GetX() / 2)) {
						if ((cast_c->GetGameObject()->GetPosition().GetY() - cast_c->GetGameObject()->GetScale().GetY() / 2 >= cast_d->GetGameObject()->GetPosition().GetY() - cast_d->GetGameObject()->GetScale().GetY() / 2 && cast_c->GetGameObject()->GetPosition().GetY() - cast_c->GetGameObject()->GetScale().GetY() / 2 <= cast_d->GetGameObject()->GetPosition().GetY() + cast_d->GetGameObject()->GetScale().GetY() / 2) ||
							(cast_c->GetGameObject()->GetPosition().GetY() + cast_c->GetGameObject()->GetScale().GetY() / 2 >= cast_d->GetGameObject()->GetPosition().GetY() - cast_d->GetGameObject()->GetScale().GetY() / 2 && cast_c->GetGameObject()->GetPosition().GetY() + cast_c->GetGameObject()->GetScale().GetY() / 2 <= cast_d->GetGameObject()->GetPosition().GetY() + cast_d->GetGameObject()->GetScale().GetY() / 2)) {
							auto colA = new Collision(cast_d, Vector3(0, 0, 0), cast_d->GetGameObject());
							auto colB = new Collision(cast_c, Vector3(0, 0, 0), cast_c->GetGameObject());
							cast_c->GetGameObject()->OnCollisionStay(colA);
							cast_d->GetGameObject()->OnCollisionStay(colB);
							delete colA;
							delete colB;
						}
					}
				}
			}
		}
	}
}