#pragma once
#include "VisualComponent.h"
#include "input.h"
#include <vector>
#include "Texture.h"
#include "Vector3.h"
#include "GameObject.h"

enum ButtonMode {
	INACTIVE,
	MOUSE_OVER,
	CLICKKING
};

class Button : public VisualComponent {
private:
	void OnClick();

	ID3D11Buffer* vertexBuffer = NULL;
	ID3D11Buffer* indexBuffer = NULL;

	Texture* textureP = nullptr;
	ID3D11ShaderResourceView* texture = NULL;

	Vector2 scale = Vector2(200, 200);

	Criterion criterion = CENTER;
	Vector3 position;

	D3DXVECTOR4 color = D3DXVECTOR4(1, 1, 1, 1);

	ButtonMode nowMode = INACTIVE;
	D3DXVECTOR4 colors[3] = {
		D3DXVECTOR4(1,1,1,1),
		D3DXVECTOR4(0.8f,0.8f,0.8f,1),
		D3DXVECTOR4(0.5f,0.5f,0.5f,1)
	};

	//テクスチャサンプル左上座標(0~1)
	float tx, ty;

	//テクスチャサンプルの大きさ(0~1)
	float tw, th;

	bool wasChange = false;

public:
	Button();
	Button(Texture* texture);

	void Init();
	void Uninit();
	void Draw() override;
	void Update();

	void SetTexture(Texture* _texture);
	void SetScale(Vector2 _scale);
	void SetCriterion(Criterion _criterion);
	void SetPosition(Vector3 _position);
	void SetColor(D3DXVECTOR4 _color);

	Texture* GetTexture();
	Vector2 GetScale();
	Criterion GetCriterion();
	Vector3 GetPosition();

	void SetTexturePosition(float _tx, float _ty);
	void SetTextureScale(float _tw, float _th);
};