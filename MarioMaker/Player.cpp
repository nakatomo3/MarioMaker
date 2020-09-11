#include "Player.h"
#include "DXEngine.h"

void Player::Start() {
	quad = gameObject->GetComponent<Quad>();
	textures[0] = quad->GetTexture();
	textures[1] = new Texture("assets/textures/MarioMaker/marioBig.png");
	textures[2] = new Texture("assets/textures/MarioMaker/marioDead.png");
	textures[3] = new Texture("assets/textures/MarioMaker/marioDead.png");
	textures[4] = new Texture("assets/textures/MarioMaker/marioDead.png");
}

void Player::Update() {

	if (isDead == false) {
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

		switch (growth) {
		case MINIMUM:
			gameObject->SetScale(Vector3(1, 1, 1));
			quad->SetTexture(textures[0]);
			break;
		case BIG:
			gameObject->SetScale(Vector3(1, 2, 1));
			quad->SetTexture(textures[1]);
			break;
		case FIRE:
			gameObject->SetScale(Vector3(1, 2, 1));
			quad->SetTexture(textures[2]);
			break;
		}

		velocity *= groundBrekeRate;
		gameObject->Move(velocity);
	} else {
		deadTimer += Time::GetDeltaTime();
		deadSpeed -= Time::GetDeltaTime() * 50;
		velocity = Vector3::Zero();
		gameObject->SetRotation(Vector3(0, 0, 0));
		gameObject->SetScale(Vector3(1, 1, 1));
		if(deadTimer < deadTime){
			gameObject->Move(Vector3(0, deadSpeed * Time::GetDeltaTime(), 0));
		} else {
			isDead = false;
			deadTimer = 0;
			gameObject->SetPosition(Vector3(0, 5, 0));
			growth = MINIMUM;
			deadSpeed = 15;
		}

	}

	if (gameObject->GetPosition().GetY() < 0) {
		quad->SetTexture(textures[4]);
		isDead = true;
	}

	isStand = false;
	beforeControllerButton = Input::GetController(0).Gamepad.wButtons;
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
				gameObject->SetPosition(Vector3(gameObject->GetPosition().GetX(), collision->GetGameObject()->GetPosition().GetY() + 0.5f + gameObject->GetScale().GetY() / 2, 0));
				isStand = true;
				velocity = Vector3(velocity.GetX(), 0, 0);
			}
		} else {
			if (abs(gameObject->GetPosition().GetX() - collision->GetGameObject()->GetPosition().GetX()) < 0.8f) {
				if (collision->GetGameObject()->GetPosition().GetY() - gameObject->GetPosition().GetY() < gameObject->GetScale().GetY() * 0.95f) {
					gameObject->SetPosition(Vector3(gameObject->GetPosition().GetX(), collision->GetGameObject()->GetPosition().GetY() - 0.5f - gameObject->GetScale().GetY() / 2, 0));
					velocity = Vector3(velocity.GetX(), -abs(velocity.GetY()) * 0.1f, 0);
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
	} else if(collision->GetGameObject()->GetTag() == MUSHROOM){
		growth = BIG;
		collision->GetGameObject()->Destroy();
	}
}

PlayerGrowth Player::GetPlayerGrowth() {
	return growth;
}
