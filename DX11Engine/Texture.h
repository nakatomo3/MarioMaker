#pragma once
#include <d3d9.h>
#include <string>
#include "Setting.h"
using namespace std;

class Texture;

class Texture {
public:
	static void Init();

	static Texture* nullTexture;

	Texture(string _path);

	//テクスチャのロード
	bool LoadTexture(string _path);

	//テクスチャのリリース
	void Release();

	//テクスチャインターフェースの習得
	ID3D11ShaderResourceView* GetTexture();
	void SetTexture(ID3D11ShaderResourceView* _texture);

	string GetPath();

	void Destroy() {
		Release();
		delete this;
	}

private :
	ID3D11ShaderResourceView* texture;

	string path;

	~Texture();
};