#pragma once
#include "VisualComponent.h"
#include "Texture.h"
#include "Vector2.h"
#include "Vector3.h"
class Image : public VisualComponent {
public:
	Image();
	Image(Texture* texture);

	void Uninit();
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

private:
	void Init();
	void Init(Texture* texture);
	ID3D11Buffer* vertexBuffer = NULL;

	Texture* textureP = nullptr;
	ID3D11ShaderResourceView* texture = NULL;

	Vector2 scale = Vector2(200, 200);

	Criterion criterion = CENTER;
	Vector3 position;
	Vector3 beforePosition;

	D3DXVECTOR4 color = D3DXVECTOR4(1, 1, 1, 1);

	//テクスチャサンプル左上座標(0~1)
	float tx, ty;

	//テクスチャサンプルの大きさ(0~1)
	float tw, th;

	bool wasChange = false;
};

