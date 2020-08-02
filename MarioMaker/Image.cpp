#include "RendererManager.h"
#include "GameObject.h"
#include "Texture.h"
#include "Image.h"
#include "Time.h"

//0.1ms
void Image::Init() {

	layer = UI;

	scale = Vector2(100, 100);
	position = Vector3(SCREEN_CENTER_X, SCREEN_CENTER_Y);
	tw = 1;
	th = 1;

	//何かあっても分かるように、仮のデータを入れておく

	Vertex vertex[4];

	vertex[0].position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[0].normal = D3DXVECTOR3(0, 0, 0);
	vertex[0].diffuse = D3DXVECTOR4(1, 1, 1, 1);
	vertex[0].texUV = D3DXVECTOR2(0, 0);

	vertex[1].position = D3DXVECTOR3(200.0f, 0.0f, 0.0f);
	vertex[1].normal = D3DXVECTOR3(0, 0, 0);
	vertex[1].diffuse = D3DXVECTOR4(1, 1, 1, 1);
	vertex[1].texUV = D3DXVECTOR2(1, 0);

	vertex[2].position = D3DXVECTOR3(0.0f, 200.0f, 0.0f);
	vertex[2].normal = D3DXVECTOR3(0, 0, 0);
	vertex[2].diffuse = D3DXVECTOR4(1, 1, 1, 1);
	vertex[2].texUV = D3DXVECTOR2(0, 1);

	vertex[3].position = D3DXVECTOR3(200.0f, 200.0f, 0.0f);
	vertex[3].normal = D3DXVECTOR3(0, 0, 0);
	vertex[3].diffuse = D3DXVECTOR4(1, 1, 1, 1);
	vertex[3].texUV = D3DXVECTOR2(1, 1);

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(Vertex) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = vertex;

	RendererManager::GetDevice()->CreateBuffer(&bd, &sd, &vertexBuffer);
	if (textureP == NULL) {
		textureP = Texture::nullTexture;
		texture = textureP->GetTexture();
	}
}

void Image::Init(Texture * tex) {
	textureP = tex;
	texture = textureP->GetTexture();

	Init();
}

void Image::Uninit() {

}

//Imageの描画
//変更有のフレーム：0.3~7ms
//変更なしのフレーム：0.1~0.2ms
void Image::Draw() {
	if (beforePosition != gameObject->GetPosition()) {
		wasChange = true;
	}

	if (wasChange == true) {
		Vector3 pos = Vector3(0, 0, 0);
		if (gameObject == nullptr) {
			LogWriter::Log("スプライトがGameObjectにアタッチされずに使用されました。GameObjectにアタッチしたうえで使用してください");
			return;
		} else {
			pos = gameObject->GetPosition();
		}

		float positionX = pos.GetX() + position.GetX();
		float positionY = pos.GetY() + position.GetY();
		float positionZ = pos.GetZ() + position.GetZ();

		float left = -scale.GetX() / 2;
		float right = scale.GetX() / 2;

		float up = -scale.GetY() / 2;
		float down = scale.GetY() / 2;

		if (criterion & 1) {
			left = 0;
			right = scale.GetX();
		} else if (criterion & 2) {
			left = -scale.GetX();
			right = 0;
		}

		if (criterion & 4) {
			up = 0;
			down = scale.GetY();
		} else if (criterion & 8) {
			up = -scale.GetY();
			down = 0;
		}

		Vertex vertex[4] = {
			{D3DXVECTOR3(positionX + left , positionY + up  , positionZ), D3DXVECTOR3(0,0,0), color, D3DXVECTOR2(tx     , ty)},
			{D3DXVECTOR3(positionX + right, positionY + up  , positionZ), D3DXVECTOR3(0,0,0), color, D3DXVECTOR2(tx + tw, ty)},
			{D3DXVECTOR3(positionX + left , positionY + down, positionZ), D3DXVECTOR3(0,0,0), color, D3DXVECTOR2(tx     , ty + th)},
			{D3DXVECTOR3(positionX + right, positionY + down, positionZ), D3DXVECTOR3(0,0,0), color, D3DXVECTOR2(tx + tw, ty + th)}
		};

		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(Vertex) * 4;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.pSysMem = vertex;

		vertexBuffer->Release();
		RendererManager::GetDevice()->CreateBuffer(&bd, &sd, &vertexBuffer);

		//texture->Release();
		//マトリクス設定
		RendererManager::SetWorldViewProjection2D();

		//頂点バッファ設定
		UINT stride = sizeof(Vertex);
		UINT offset = 0;
		RendererManager::GetDeviceContext()->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);

		//テクスチャ設定
		RendererManager::GetDeviceContext()->PSSetShaderResources(0, 1, &texture);

		//プリミティブトポロジ設定
		RendererManager::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

		//ポリゴン描画
		RendererManager::GetDeviceContext()->Draw(4, 0);

		wasChange = false;

	} else {

		//マトリクス設定
		RendererManager::SetWorldViewProjection2D();

		//頂点バッファ設定
		UINT stride = sizeof(Vertex);
		UINT offset = 0;
		RendererManager::GetDeviceContext()->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);

		//テクスチャ設定
		RendererManager::GetDeviceContext()->PSSetShaderResources(0, 1, &texture);

		//プリミティブトポロジ設定
		RendererManager::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

		//ポリゴン描画
		RendererManager::GetDeviceContext()->Draw(4, 0);

		wasChange = false;

	}
	beforePosition = gameObject->GetPosition();
}

void Image::SetTexture(Texture * _texture) {
	textureP = _texture;
	texture = textureP->GetTexture();
	wasChange = true;
}

void Image::SetScale(Vector2 _scale) {
	scale = _scale;
	wasChange = true;
}

void Image::SetCriterion(Criterion _criterion) {
	criterion = _criterion;
	wasChange = true;
}

void Image::SetPosition(Vector3 _position) {
	position = _position;
	wasChange = true;
}

void Image::SetColor(D3DXVECTOR4 _color) {
	color = _color;
	wasChange = true;
}

Texture * Image::GetTexture() {
	return textureP;
}

Vector2 Image::GetScale() {
	return scale;
}

Criterion Image::GetCriterion() {
	return criterion;
}

Vector3 Image::GetPosition() {
	return position;
}

void Image::SetTexturePosition(float _tx, float _ty) {
	tx = _tx;
	ty = _ty;
	wasChange = true;
}

void Image::SetTextureScale(float _tw, float _th) {
	tw = _tw;
	th = _th;
	wasChange = true;
}

Image::Image() {
	Init();
}

Image::Image(Texture * texture) {
	Init(texture);
}
