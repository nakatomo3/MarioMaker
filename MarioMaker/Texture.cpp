#include "RendererManager.h"
#include "LogWriter.h"
#include "Texture.h"
Texture* Texture::nullTexture = NULL;

void Texture::Init() {
	nullTexture = new Texture("assets/textures/Systems/null.bmp");
}

Texture::Texture(string _path) {
	path = _path;
	LoadTexture(_path);
}


Texture::~Texture() {
}

//0.5ms~(結構重い、1920px:1080pxのpngで100ms)
bool Texture::LoadTexture(string _path) {
	if (path.size() == 0) {
		return false;
	}
	auto hr = D3DX11CreateShaderResourceViewFromFile(RendererManager::GetDevice(), path.c_str(), NULL, NULL, &texture, NULL);
	if (hr != 0) {
		LogWriter::Log("%ld", hr);
	}
	if (texture == NULL) {
		LogWriter::LogError("テクスチャの生成に失敗しました。パス：%s", path.c_str());
	} else {
		LogWriter::Log("テクスチャの生成に成功しました。パス：%s", path.c_str());
	}
	return true;
}

void Texture::Release(void) {
	texture->Release();
	delete this;
}

ID3D11ShaderResourceView* Texture::GetTexture() {
	return texture;
}

void Texture::SetTexture(ID3D11ShaderResourceView* _texture) {
	texture = _texture;
}

string Texture::GetPath() {
	return path;
}
