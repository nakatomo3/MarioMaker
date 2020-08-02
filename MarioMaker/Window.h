#pragma once
#include "VisualComponent.h"
#include "Vector3.h"
#include "Vector2.h"
#include <vector>
#include "Texture.h"
#include "GameObject.h"
using namespace std;

//Windowクラス自体は一番上のバー部分とボタン各種のみ
//これ以外の子供オブジェクトをまとめて表示非表示するための親用コンポーネント
class Window : public VisualComponent {
public:
	Window();
	void Init();
	void Draw();
	void Update();
private:
	string windowName;

	ID3D11Buffer* barVertexBuffer = NULL;
	ID3D11Buffer* minButtonVertexBuffer = NULL;

	Texture* textureP = Texture::nullTexture;
	ID3D11ShaderResourceView* texture = NULL;

	Vector2 scale = Vector2(200, 25);

	Criterion criterion = CENTER;
	//Vector3 position;

	D3DXVECTOR4 color = D3DXVECTOR4(0, 0.46f, 0.75f, 1);

	bool wasChange = true;

	Vector2 cursorPositionAtClick = Vector2(0, 0);
	Vector3 windowPositionAtClick = Vector3(0, 0, 0);
	bool isDragging = false;

	float clickTimer = 0;
	float doubleClickInterval = 0.2f;
};