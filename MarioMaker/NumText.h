#pragma once
#include "VisualComponent.h"
#include <vector>
#include "Vector3.h"
using namespace std;
class NumText :	public VisualComponent {
public:
	//���s���ԁF�������ɔ��A10������1ms�ȉ�
	void Draw();

	void SetPosition(Vector3 newPos);
	Vector3 GetPosition();

	void SetColor(D3DXVECTOR4 newColor);
	D3DXVECTOR4 GetColor();

	void SetText(float number);
	void SetText(int number);
	float GetText();

	void SetFontSize(int _size);
	int GetFontSize();

	//�L�������̐ݒ�
	void SetMinDigit(int maxDigit);
	int GetMinDigit();

	void SetScale(float _scale);
	float GetScale();

	void OnDestroy() override;



private:

	ID3D11Buffer* vertexBuffer = NULL;

	vector<ID3D11ShaderResourceView*> textures;

	vector<LONG> fontX;
	vector<LONG> fontY;

	float scale = 1;

	//Criterion criterion = CENTER;
	Vector3 position = Vector3(0, 0, 0);

	D3DXVECTOR4 color = D3DXVECTOR4(1, 1, 1, 1);

	//�e�N�X�`���T���v��������W(0~1)
	float tx, ty;

	//�e�N�X�`���T���v���̑傫��(0~1)
	float tw, th;

	bool wasChange = false;

	int fontSize = 64;

	float number = 1234.567f;
	int numberInt = 9876;

	unsigned int digit = 5;

	bool isInt = false;

	void CreateTexture();

};

