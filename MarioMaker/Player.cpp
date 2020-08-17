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
		velocity += Vector3::Down() * gravity * Time::GetDeltaTime();
	}

	velocity *= groundBrekeRate;
	gameObject->Move(velocity);

	isStand = false;
}

void Player::SetQuad(Quad * _quad) {
	quad = _quad;
}

void Player::KeyboardInput() {
	//¶‰EˆÚ“®
	if (Input::GetKey('A')) {
		velocity += Vector3::Left() * moveSpeed * Time::GetDeltaTime();
	}
	if (Input::GetKey('D')) {
		velocity += Vector3::Right() * moveSpeed * Time::GetDeltaTime();
	}
}

void Player::ControllerInput() {
	velocity += Vector3::Right() * Input::GetController(0).Gamepad.sThumbLX * Time::GetDeltaTime() / 32768 * moveSpeed;

	if (isStand == true && Input::GetController(0).Gamepad.wButtons & XINPUT_GAMEPAD_B) {
		velocity += Vector3::Up() * 0.7f;
	}
}

void Player::OnCollisionStay(Collision* collision) {
	if (gameObject->GetPosition().GetY() >= collision->GetGameObject()->GetPosition().GetY()) {
		gameObject->SetPosition(Vector3(gameObject->GetPosition().GetX(), collision->GetGameObject()->GetPosition().GetY() + 1, 0));
		isStand = true;
		velocity = Vector3(velocity.GetX(), 0, 0);
	}
}