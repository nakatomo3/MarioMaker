#include "QuestionBlock.h"
#include "DXEngine.h"
#include "EditScene.h"

void QuestionBlock::OnCollisionStay(Collision * collision) {
	if (collision->GetGameObject()->GetTag() == PLAYER && gameObject->GetPosition().GetY() > collision->GetGameObject()->GetPosition().GetY() + 0.4f && abs(gameObject->GetPosition().GetX() - collision->GetGameObject()->GetPosition().GetX()) < 0.8f) {
		quad = gameObject->GetComponent<Quad>();
		if (hatenaBlock == nullptr) {
			quad->GetTexture();
		}
		quad->SetTexture(usedBlock);
		isUsed = false;
	}
}

void QuestionBlock::SetUsedBlock(Texture * texture) {
	usedBlock = texture;
}

void QuestionBlock::Update() {
	if (quad == nullptr) {
		quad = gameObject->GetComponent<Quad>();
	}
	if (hatenaBlock == nullptr) {
		hatenaBlock = quad->GetTexture();
	}
	if (EditScene::GetIsEditMode() == true) {
		isUsed = false;
		quad->SetTexture(hatenaBlock);
	}
}
