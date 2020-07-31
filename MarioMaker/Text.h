#pragma once
#include <tchar.h>
#include "VisualComponent.h"
#include "Texture.h"
#include "Vector2.h"
#include "Vector3.h"
#include <vector>
using namespace std;

class Text : public VisualComponent {
public:
	//実行時間：文字数に比例、10文字で1ms以下
	void Draw();

	void SetPosition(Vector3 newPos);
	Vector3 GetPosition();

	void SetColor(D3DXVECTOR4 newColor);
	D3DXVECTOR4 GetColor();

	void SetText(TCHAR* newText);
	void SetText(const char* newText);
	void SetText(string newText);
	TCHAR* GetText();

	void SetFontSize(int _size);
	int GetFontSize();

	void OnDestroy() override;

private:

	ID3D11Buffer* vertexBuffer = NULL;

	vector<ID3D11ShaderResourceView*> textures;

	vector<LONG> fontX;
	vector<LONG> fontY;

	float scale = 1;

	//Criterion criterion = CENTER;
	Vector3 position;

	D3DXVECTOR4 color = D3DXVECTOR4(1, 1, 1, 1);

	//テクスチャサンプル左上座標(0~1)
	float tx, ty;

	//テクスチャサンプルの大きさ(0~1)
	float tw, th;

	bool wasChange = false;

	int fontSize = 64;

	TCHAR* c = (TCHAR*)"";

	//fontのテクスチャを作る。hogeで2ms。結構重い
	void CreateTexture();
};

