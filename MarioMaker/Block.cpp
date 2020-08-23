#include "Block.h"
#include "EditScene.h"

void Block::OnCollisionStay(Collision * collision) {
	
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