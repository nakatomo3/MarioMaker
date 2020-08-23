#include "Player.h"
#include "DXEngine.h"

void Player::Update() {

	KeyboardInput();
	ControllerInput();

	if (velocity.GetX() >= 0) {
		gameObject->SetRotation(Vector3(0, 0, 0));
	} else {
		gameObject->SetRotation(Vector3(0, 3.14f, 0));
	}

	if (isStand == false) {
		velocity += Vector3::Down() * gravity * (float)Time::GetDeltaTime();
	}

	if (gameObject->GetPosition().GetX() < 0 && velocity.GetX() < 0) {
		velocity = Vector3(0, velocity.GetY(), 0);
		gameObject->SetPosition(Vector3(0, gameObject->GetPosition().GetY(), 0));
	}

	velocity *= groundBrekeRate;
	gameObject->Move(velocity);

	isStand = false;
	beforeControllerButton = Input::GetController(0).Gamepad.wButtons;
}

void Player::SetQuad(Quad * _quad) {
	quad = _quad;
}

void Player::KeyboardInput() {
	//左右移動
	if (Input::GetKey('A')) {
		velocity += Vector3::Left() * moveSpeed * (float)Time::GetDeltaTime();
	}
	if (Input::GetKey('D')) {
		velocity += Vector3::Right() * moveSpeed * (float)Time::GetDeltaTime();
	}

	if (isStand == true && Input::GetKeyDown('W')) {
		velocity += Vector3::Up() * 0.7f;
	}
}

void Player::ControllerInput() {
	auto speed = moveSpeed;

	//Bダッシュ
	if (Input::GetController(0).Gamepad.wButtons & XINPUT_GAMEPAD_A || Input::GetController(0).Gamepad.wButtons & XINPUT_GAMEPAD_Y) {
		speed *= 2;
	}
	velocity += Vector3::Right() * Input::GetController(0).Gamepad.sThumbLX * (float)Time::GetDeltaTime() / 32768 * speed;

	if (isStand == true && Input::GetController(0).Gamepad.wButtons & XINPUT_GAMEPAD_B && !(beforeControllerButton & XINPUT_GAMEPAD_B)) {
		velocity += Vector3::Up() * 0.7f;
	}
}

void Player::OnCollisionStay(Collision* collision) {
	if (collision->GetGameObject()->GetTag() == GROUND_BLOCK || collision->GetGameObject()->GetTag() == BLOCK || collision->GetGameObject()->GetTag() == HATENA_BLOCK) {
		if (gameObject->GetPosition().GetY() > collision->GetGameObject()->GetPosition().GetY()) {
			if (abs(gameObject->GetPosition().GetX() - collision->GetGameObject()->GetPosition().GetX()) < 0.8f) {
				gameObject->SetPosition(Vector3(gameObject->GetPosition().GetX(), collision->GetGameObject()->GetPosition().GetY() + 1, 0));
				isStand = true;
				velocity = Vector3(velocity.GetX(), 0, 0);
			}
		} else {
			if (abs(gameObject->GetPosition().GetX() - collision->GetGameObject()->GetPosition().GetX()) < 0.8f) {
				if (collision->GetGameObject()->GetPosition().GetY() - gameObject->GetPosition().GetY() < 0.95f) {
					gameObject->SetPosition(Vector3(gameObject->GetPosition().GetX(), collision->GetGameObject()->GetPosition().GetY() - 1, 0));
					velocity = Vector3(velocity.GetX(), -abs(velocity.GetY()) * 0.5f, 0);
				}

			} else {
				if (gameObject->GetPosition().GetX() > collision->GetGameObject()->GetPosition().GetX()) {
					if (velocity.GetX() < 0) {
						velocity = Vector3(0, velocity.GetY(), 0);
					}
					gameObject->SetPosition(Vector3(collision->GetGameObject()->GetPosition().GetX() + 1, gameObject->GetPosition().GetY(), 0));
				}
				if (gameObject->GetPosition().GetX() < collision->GetGameObject()->GetPosition().GetX()) {
					if (velocity.GetX() > 0) {
						velocity = Vector3(0, velocity.GetY(), 0);
					}
					gameObject->SetPosition(Vector3(collision->GetGameObject()->GetPosition().GetX() - 1, gameObject->GetPosition().GetY(), 0));
				}
			}
		}
	}
}