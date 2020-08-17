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

	velocity *= groundBrekeRate;
	gameObject->Move(velocity);
}

void Player::SetQuad(Quad * _quad) {
	quad = _quad;
}

void Player::KeyboardInput() {
	//ç∂âEà⁄ìÆ
	if (Input::GetKey('A')) {
		velocity += Vector3::Left() * moveSpeed * Time::GetDeltaTime();
	}
	if (Input::GetKey('D')) {
		velocity += Vector3::Right() * moveSpeed * Time::GetDeltaTime();
	}
}

void Player::ControllerInput() {
	velocity += Vector3::Right() * Input::GetController(0).Gamepad.sThumbLX * Time::GetDeltaTime() / 32768 * moveSpeed;
}
