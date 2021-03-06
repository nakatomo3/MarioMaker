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
			//正常に見つかった
			Component* cacheComponent = colliders[i];
			colliders[i] = colliders[colliders.size() - 1];
			colliders.pop_back();
			return;
		}
	}
}

void CollisionManager::Update() {
	for (unsigned int i = 0; i < colliders.size(); i++) {
		if (colliders[i]->GetGameObject()->GetActive() == false) {
			continue;
		}
		for (unsigned int j = i + 1; j < colliders.size(); j++) {
			if (colliders[j]->GetGameObject()->GetActive() == false) {
				continue;
			}
			SphereCollider* cast_a = dynamic_cast<SphereCollider*>(colliders[i]);
			SphereCollider* cast_b = dynamic_cast<SphereCollider*>(colliders[j]);
			//SphereCollider同士の衝突
			if (cast_a != NULL && cast_b != NULL && cast_a->GetActive() == true && cast_b->GetActive() == true) {
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
			//QuadCollider同士の衝突。後々BoxColliderのみになる予定
			if (cast_c != NULL && cast_d != NULL && cast_c->GetActive() == true && cast_d->GetActive() == true) {
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