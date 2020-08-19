#pragma once
#include "VisualComponent.h"
#include "Vector3.h"
#include "Vector2.h"
#include <vector>
#include "Texture.h"
#include "GameObject.h"
using namespace std;

//Window�N���X���͈̂�ԏ�̃o�[�����ƃ{�^���e��̂�
//����ȊO�̎q���I�u�W�F�N�g���܂Ƃ߂ĕ\����\�����邽�߂̐e�p�R���|�[�l���g
class Window : public VisualComponent {
public:
	Window();
	void Init();
	void Draw();
	void Update();

	void SetWidth(float width);
	float GetWidth();
private:
	string windowName;

	ID3D11Buffer* barVertexBuffer = NULL;
	ID3D11Buffer* minButtonVertexBuffer = NULL;

	Texture* textureP = Texture::nullTexture;
	ID3D11ShaderResourceView* texture = NULL;

	Vector2 scale = Vector2(SCREEN_HEIGHT / 2.7f, SCREEN_HEIGHT * 0.05f);

	Criterion criterion = CENTER;

	D3DXVECTOR4 color = D3DXVECTOR4(0, 0.46f, 0.75f, 1);

	bool wasChange = true;

	Vector2 cursorPositionAtClick = Vector2(0, 0);
	Vector3 windowPositionAtClick = Vector3(0, 0, 0);
	bool isDragging = false;

	float clickTimer = 0;
	float doubleClickInterval = 0.2f;
};