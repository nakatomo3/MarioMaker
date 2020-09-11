#include "Mushroom.h"
#include "Time.h"
#include "Collision.h"

Texture* Mushroom::texture;

void Mushroom::Start() {
	if (texture == nullptr) {
		texture = new Texture("assets/textures/MarioMaker/kinoko.png");
	}
	quad = gameObject->GetComponent<Quad>();
	quad->SetTexture(texture);

	gameObject->SetTag(MUSHROOM);
}

void Mushroom::Update() {
	if (isStand == false) {
		velocity += Vector3::Down() * gravity * (float)Time::GetDeltaTime();
	}
	if (isRight == true) {
		velocity = Vector3(speed * (float)Time::GetDeltaTime(), velocity.GetY(), velocity.GetZ());
	} else {
		velocity = Vector3(-speed * (float)Time::GetDeltaTime(), velocity.GetY(), velocity.GetZ());
	}

	gameObject->Move(velocity);

	isStand = false;
}

void Mushroom::OnCollisionStay(Collision * collision) {
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
					isRight = true;
					gameObject->SetPosition(Vector3(collision->GetGameObject()->GetPosition().GetX() + 1.1f, gameObject->GetPosition().GetY(), 0));
				}
				if (gameObject->GetPosition().GetX() < collision->GetGameObject()->GetPosition().GetX()) {
					isRight = false;
					gameObject->SetPosition(Vector3(collision->GetGameObject()->GetPosition().GetX() - 1.1f, gameObject->GetPosition().GetY(), 0));
				}
			}
		}
	}
}