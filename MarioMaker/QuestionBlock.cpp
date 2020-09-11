#include "QuestionBlock.h"
#include "DXEngine.h"
#include "EditScene.h"
#include "CoinEffect.h"
#include "Player.h"
#include "Mushroom.h"

void QuestionBlock::OnCollisionStay(Collision * collision) {
	if (collision->GetGameObject()->GetTag() == PLAYER && gameObject->GetPosition().GetY() > collision->GetGameObject()->GetPosition().GetY() + 0.4f && abs(gameObject->GetPosition().GetX() - collision->GetGameObject()->GetPosition().GetX()) < 0.8f) {
		quad = gameObject->GetComponent<Quad>();
		if (hatenaBlock == nullptr) {
			quad->GetTexture();
		}

		auto generatedObject = new GameObject();
		generatedObject->AddComponent<Quad>();
		switch (type) {
		case HATENA_COIN:
			generatedObject->SetPosition(Vector3(gameObject->GetPosition().GetX(), gameObject->GetPosition().GetY(), gameObject->GetPosition().GetZ() -0.01f));
			generatedObject->AddComponent<CoinEffect>();
			break;
		case HATENA_ITEM:
			generatedObject->AddComponent<QuadCollider>();
			if (collision->GetGameObject()->GetComponent<Player>()->GetPlayerGrowth() == MINIMUM) {
				//キノコを出す
				generatedObject->AddComponent<Mushroom>();
			} else {
				//花を出す
			}
			generatedObject->SetPosition(Vector3(gameObject->GetPosition().GetX(), gameObject->GetPosition().GetY() + 1, gameObject->GetPosition().GetZ() -0.01f));
			break;
		}
		ObjectManager::Instantiate(generatedObject);
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

void QuestionBlock::SetBlockType(QuestionBlockType _type) {
	type = _type;
	if (type > HATENA_COIN) {
		type = HATENA_ITEM;
	}
	if (type < HATENA_ITEM) {
		type = HATENA_COIN;
	}
}

QuestionBlockType QuestionBlock::GetBlockType() {
	return type;
}
