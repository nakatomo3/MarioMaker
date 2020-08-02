#include "RendererManager.h"
#include "Quad.h"
#include "GameObject.h"
#include "LogWriter.h"
#include "Time.h"

//0.05ms~0.1ms
void Quad::Init() {

	th = 1;
	tw = 1;

	Vertex vertex[4];
	D3D11_BUFFER_DESC bd;
	D3D11_SUBRESOURCE_DATA sd;

	vertex[0].position = D3DXVECTOR3(-0.5f, -0.5f, 0.0f);
	vertex[0].normal = D3DXVECTOR3(0, 0, 0);
	vertex[0].diffuse = D3DXVECTOR4(1, 1, 1, 1);
	vertex[0].texUV = D3DXVECTOR2(0, 1);

	vertex[1].position = D3DXVECTOR3(-0.5f, 0.5f, 0.0f);
	vertex[1].normal = D3DXVECTOR3(0, 0, 0);
	vertex[1].diffuse = D3DXVECTOR4(1, 1, 1, 1);
	vertex[1].texUV = D3DXVECTOR2(0, 0);

	vertex[2].position = D3DXVECTOR3(0.5f, -0.5f, 0.0f);
	vertex[2].normal = D3DXVECTOR3(0, 0, 0);
	vertex[2].diffuse = D3DXVECTOR4(1, 1, 1, 1);
	vertex[2].texUV = D3DXVECTOR2(1, 1);

	vertex[3].position = D3DXVECTOR3(0.5f, 0.5f, 0.0f);
	vertex[3].normal = D3DXVECTOR3(0, 0, 0);
	vertex[3].diffuse = D3DXVECTOR4(1, 1, 1, 1);
	vertex[3].texUV = D3DXVECTOR2(1, 0);

	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(Vertex) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = vertex;

	RendererManager::GetDevice()->CreateBuffer(&bd, &sd, &vertexBuffer);
	if (texture == nullptr) {
		textureP = Texture::nullTexture;
		texture = textureP->GetTexture();
	}
}

void Quad::OnDestroy() {
	vertexBuffer->Release();
}

//QuadのDraw
//実行時間目安：0.1~0.2ms
void Quad::Draw() {

	if (isCull == false) {
		RendererManager::SetCullMode(D3D11_CULL_NONE);
	}

	Vector3 pos = Vector3(0, 0, 0);
	if (gameObject == nullptr) {
		LogWriter::Log("スプライトがGameObjectにアタッチされずに使用されました。GameObjectにアタッチしたうえで使用してください");
		return;
	} else {
		pos = gameObject->GetPosition() - gameObject->GetLocalPosition();
	}

	D3DXMATRIX world, mScale, mRot, mTrans, localPos;

	//マトリクス設定
	D3DXMatrixScaling(&mScale, gameObject->GetScale().GetX() * scale.GetX(), gameObject->GetScale().GetY() * scale.GetY(), gameObject->GetScale().GetZ());
	D3DXMatrixRotationYawPitchRoll(&mRot, gameObject->GetRotation().GetY(), gameObject->GetRotation().GetX(), gameObject->GetRotation().GetZ());
	D3DXMatrixTranslation(&mTrans, pos.GetX(), pos.GetY(), pos.GetZ());
	D3DXMatrixTranslation(&localPos, gameObject->GetLocalPosition().GetX(), gameObject->GetLocalPosition().GetY(), gameObject->GetLocalPosition().GetZ());
	world =  localPos * mScale * mRot * mTrans;
	RendererManager::SetWorldMatrix(&world);

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

	if (isCull == false) {
		RendererManager::SetCullMode(D3D11_CULL_BACK);
	}
}

void Quad::SetTexture(Texture * _texture) {
	textureP = _texture;
	texture = textureP->GetTexture();
}

void Quad::SetScale(Vector2 _scale) {
	scale = _scale;
}

void Quad::SetCriterion(Criterion _criterion) {
	criterion = _criterion;
}

void Quad::SetPosition(Vector3 _position) {
	position = _position;
}

void Quad::SetColor(D3DXVECTOR4 _color) {
	color = _color;
}

Texture * Quad::GetTexture() {
	return textureP;
}

Vector2 Quad::GetScale() {
	return scale;
}

Criterion Quad::GetCriterion() {
	return criterion;
}

Vector3 Quad::GetPosition() {
	return position;
}

void Quad::SetTexturePosition(float _tx, float _ty) {
	tx = _tx;
	ty = _ty;
}

void Quad::SetTextureScale(float _tw, float _th) {
	tw = _tw;
	th = _th;
}

void Quad::SetCull(bool _isCull) {
	isCull = _isCull;
}

bool Quad::GetCull() {
	return isCull;
}

Quad::Quad() {
	Init();
}
