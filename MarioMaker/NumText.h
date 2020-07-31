#pragma once
#include "VisualComponent.h"
#include <vector>
#include "Vector3.h"
using namespace std;
class NumText :	public VisualComponent {
public:
	//実行時間：文字数に比例、10文字で1ms以下
	void Draw();

	void SetPosition(Vector3 newPos);
	Vector3 GetPosition();

	void SetColor(D3DXVECTOR4 newColor);
	D3DXVECTOR4 GetColor();

	void SetText(float number);
	float GetText();

	void SetFontSize(int _size);
	int GetFontSize();

	//有効桁数の設定
	void SetMinDigit(int maxDigit);
	int GetMinDigit();

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

	//テクスチャサンプル左上座標(0~1)
	float tx, ty;

	//テクスチャサンプルの大きさ(0~1)
	float tw, th;

	bool wasChange = false;

	int fontSize = 64;

	float number = 1234.567f;

	unsigned int digit = 5;

	void CreateTexture();

};

