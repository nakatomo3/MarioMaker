#include "Block.h"
#include "EditScene.h"

void Block::OnCollisionStay(Collision * collision) {
	if (collision->GetGameObject()->GetTag() == PLAYER && abs(gameObject->GetPosition().GetX() - collision->GetGameObject()->GetPosition().GetX()) < 0.8f && collision->GetGameObject()->GetPosition().GetY() - gameObject->GetPosition().GetY() < 0.95f) {
		if (quad == nullptr) {
			quad = gameObject->GetComponent<Quad>();
		}
		if (collider == nullptr) {
			collider = gameObject->GetComponent<QuadCollider>();
		}
		quad->SetActive(false);
		collider->SetActive(false);
	}
}

void Block::Update() {
	if (quad == nullptr) {
		quad = gameObject->GetComponent<Quad>();
	}
	if (collider == nullptr) {
		collider = gameObject->GetComponent<QuadCollider>();
	}
	if (EditScene::GetIsEditMode() == true) {
		quad->SetActive(true);
		collider->SetActive(true);
	}
}