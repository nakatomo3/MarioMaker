#include "PlayerCamera.h"

void PlayerCamera::Update() {
	gameObject->SetPosition(Vector3(player->GetPosition().GetX(), 7, -14));
}

void PlayerCamera::SetPlayer(GameObject * _player) {
	player = _player;
}
