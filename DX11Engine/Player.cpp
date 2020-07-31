#include "Player.h"
#include "input.h"
#include "Bullet.h"
#include "Quad.h"
#include "ObjectManager.h"
#include "SphereCollider.h"
#include "Time.h"

void Player::Update() {
	if (Input::GetKey('A')) {
		gameObject->Move(Vector3::Left() * Time::GetDeltaTime() * speed);
	}
	if (Input::GetKey('D')) {
		gameObject->Move(Vector3::Right() * Time::GetDeltaTime() * speed);
	}
	if (Input::GetKey('W')) {
		gameObject->Move(Vector3::Forward() * Time::GetDeltaTime() * speed);
	}
	if (Input::GetKey('S')) {
		gameObject->Move(Vector3::Back() * Time::GetDeltaTime() * speed);
	}

	if (Input::GetKeyDown(VK_RETURN)) {
		auto bullet = new GameObject();
		bullet->AddComponent<Bullet>();
		auto quad = bullet->AddComponent<Quad>();
		bullet->AddComponent<SphereCollider>();
		bullet->SetScale(Vector3(0.3f, 0.3f, 1));
		bullet->SetPosition(gameObject->GetPosition());
		ObjectManager::Instantiate(bullet);
	}
}