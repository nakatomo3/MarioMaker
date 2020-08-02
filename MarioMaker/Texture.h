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

	//�e�N�X�`���̃��[�h
	bool LoadTexture(string _path);

	//�e�N�X�`���̃����[�X
	void Release();

	//�e�N�X�`���C���^�[�t�F�[�X�̏K��
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