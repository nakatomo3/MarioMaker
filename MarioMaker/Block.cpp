#include "Block.h"
#include "EditScene.h"
#include "Player.h"
#include "Time.h"

void Block::OnCollisionStay(Collision * collision) {
	if (collision->GetGameObject()->GetTag() == PLAYER && abs(gameObject->GetPosition().GetX() - collision->GetGameObject()->GetPosition().GetX()) < 0.8f) {
		if (quad == nullptr) {
			quad = gameObject->GetComponent<Quad>();
		}
		if (collider == nullptr) {
			collider = gameObject->GetComponent<QuadCollider>();
		}
		if (collision->GetGameObject()->GetComponent<Player>()->GetPlayerGrowth() >= BIG && collision->GetGameObject()->GetPosition().GetY() - gameObject->GetPosition().GetY() < 1.45f) {
			quad->SetActive(false);
			collider->SetActive(false);
		} else {
			if (collision->GetGameObject()->GetPosition().GetY() - gameObject->GetPosition().GetY() < 0.95f) {
				impactTimer = 0;
				isImpact = true;
			}
		}
	}
}

void Block::Update() {
	if (originPos.GetZ() == -1) {
		originPos = gameObject->GetPosition();
	}
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

	if (isImpact == true) {
		impactTimer += Time::GetDeltaTime();
	}
	if (impactTimer <= returnTimer / 2) {
		gameObject->SetPosition(Vector3(0, impactTimer, 0) + originPos);
	} else if(impactTimer < returnTimer){
		gameObject->SetPosition(Vector3(0, returnTimer / 2 - impactTimer, 0) + originPos);
	} else {
		isImpact = false;
		impactTimer = 0;
	}
}