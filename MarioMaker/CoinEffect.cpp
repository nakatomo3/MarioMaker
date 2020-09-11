#include "CoinEffect.h"
#include "DXEngine.h"

Texture* CoinEffect::coinTexture;

void CoinEffect::Update() {
	timer += Time::GetDeltaTime();
	speed -= Time::GetDeltaTime() * 50;

	if (timer < time / 3) {
		gameObject->Move(Vector3(0, speed * Time::GetDeltaTime(), 0));
	} else if (timer < time) {
		gameObject->Move(Vector3(0, speed * Time::GetDeltaTime(), 0));
	} else {
		gameObject->Destroy();
	}
}

void CoinEffect::Start() {
	if (coinTexture == nullptr) {
		coinTexture = new Texture("assets/textures/MarioMaker/coin.png");
	}
	quad = gameObject->GetComponent<Quad>();
	quad->SetTexture(coinTexture);
}
