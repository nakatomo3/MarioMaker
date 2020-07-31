#pragma once
#include "VisualComponent.h"
#include "Texture.h"
#include "Vector2.h"
#include "Vector3.h"

class Quad : public VisualComponent {
protected:
	ID3D11Buffer* vertexBuffer = NULL;

	Texture* textureP = nullptr;
	ID3D11ShaderResourceView* texture = NULL;

	Vector2 scale = Vector2(1, 1);

	Criterion criterion = CENTER;
	Vector3 position;

	D3DXVECTOR4 color = D3DXVECTOR4(1, 1, 1, 1);

	//テクスチャサンプル左上座標(0~1)
	float tx, ty;

	//テクスチャサンプルの大きさ(0~1)
	float tw, th = 1;

	//カリング(裏面を描画しない設定のオンオフ)
	bool isCull = true;

public:
	void Init();
	void OnDestroy() override;
	void Draw() override;

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

	//カリング(裏面を描画しない設定)を変更する
	void SetCull(bool isCull);
	bool GetCull();

	Quad();
};