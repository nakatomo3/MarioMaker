#include "Bullet.h"
#include "Time.h"
#include "Collision.h"
#include "Text.h"
#include "ObjectManager.h"

void Bullet::Update() {
	gameObject->SetPosition(gameObject->GetPosition() + Vector3::Forward() * Time::GetDeltaTime() * 10);

	if (gameObject->GetPosition().GetZ() >= 10) {
		gameObject->Destroy();
	}
}

void Bullet::OnCollisionStay(Collision* collision) {
	if (collision->GetGameObject()->CompareTag(ENEMY)) {
		auto obj = new GameObject();
		auto text = obj->AddComponent<Text>();
		text->SetText("hit!");
		ObjectManager::Instantiate(obj);
		obj->Destroy(0.5f);

		gameObject->Destroy();
		collision->GetGameObject()->Destroy();
	}
}