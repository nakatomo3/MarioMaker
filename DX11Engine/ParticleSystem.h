#pragma once
#include "VisualComponent.h"
#include "Vector3.h"
#include "Texture.h"
#include <vector>
using namespace std;

typedef enum EndAction {
	NONE,
	DESTROY,
	DISABLE
};

class ParticleSystem : public VisualComponent {
public:
	void Draw();
	void Update();

protected:
	ID3D11Buffer* vertexBuffer = NULL;

	Texture* textureP = nullptr;
	ID3D11ShaderResourceView* texture = NULL;

	vector<bool> isUse;

	D3DXVECTOR4 color = D3DXVECTOR4(1, 1, 1, 1);

	float duration = 10.0f;
	bool isLoop = false;
	float lifeTime = 10;
	Vector3 startSpeed = Vector3::Up();
	Vector3 startSize = Vector3::One();
	Vector3 startRotation = Vector3::Zero();
	float maxParticle = 1000;
	bool playOnAwake = true;
	/*EndAction endAction = NONE;
	bool isSimulateLocal = false;*/

	virtual void ParticleUpdate();
};